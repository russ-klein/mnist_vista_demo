
#include "defines.h"
#include "catapult_memory_master.h"
#include "catapult_conv2d.h"


//#define INDEX_BITS    18
//#define FILTER_BITS    3

// #define PAR_BITS       4
#define PAR_BITS      (PAR_IN + BUS_WIDTH)

#define MAX_AREA (MAX_IMAGE_WIDTH * MAX_IMAGE_HEIGHT)
#define MAX_MARGIN ((MAX_IMAGE_WIDTH * ((MAX_FILTER_HEIGHT - 1) / 2)) + ((MAX_FILTER_WIDTH - 1) / 2))
#define MAX_MARGIN_ROUND_UP ( STRIDE * (((MAX_MARGIN) + (STRIDE - 1)) / (STRIDE)))
#define MAX_TAIL   ((MAX_IMAGE_WIDTH * ((MAX_FILTER_HEIGHT - 1) / 2)) - ((MAX_FILTER_WIDTH - 1) / 2)) + MAX_FILTER_WIDTH + (STRIDE - 1)
#define MAX_TAIL_ROUND_UP  ( STRIDE * (((MAX_TAIL) + (STRIDE - 1)) / (STRIDE)))

#define MAX_SHIFT_REGISTER_SIZE  ((MAX_MARGIN) + (MAX_TAIL_ROUND_UP))

//#define SHIFT_REGISTER_SIZE ((WIDTH * 2) + FILTER_WIDTH + (STRIDE - 1)) + \
//                            (STRIDE * (((((WIDTH * 2) + FILTER_WIDTH + (STRIDE - 1)) - \
//                            (((WIDTH * (FILTER_HEIGHT - 1)/2)) + FILTER_WIDTH + (STRIDE - 1))) + (STRIDE - 1)) / STRIDE))


typedef ac_int<INDEX_BITS, true>        index_type;
typedef ac_int<MAX_FILTER_BITS, false>  filter_index_type;
typedef ac_int<PAR_BITS, false>         p_type;
typedef ac_int<STRIDE, false>           enables_type;

static hw_cat_type relu_fn(hw_cat_type n)
{
    if (n<0) return 0;
    return n;
}


static void perform_relu(bool relu, raw_memory_line *image_out, raw_memory_line *image_in, index_type image_height, index_type image_width)
{   
    hw_cat_type values[STRIDE];
    index_type count;
    index_type i;
    
    static const index_type stride = STRIDE; 
    const index_type l_area = image_height * image_width;
    
   #pragma hls_pipeline_init_interval 1
    for (count = 0; count < l_area; count += stride) {
        copy_to_regs(values, 0, image_in, count, stride);
       #pragma hls_unroll
        for (i=0; i<STRIDE; i++) {
            values[i] = (relu) ? relu_fn(values[i]) : values[i];
        }
        copy_from_regs(image_out, count, values, 0, stride);
    }
}

static void get_shift_in_values(hw_cat_type *values, raw_memory_line *image, index_type n, index_type num_words, index_type area)
{
    hw_cat_type line[STRIDE];
    index_type size;
    p_type p;

    // static const index_type area = AREA;
    static const bool chatty = false;

    size = num_words;

    if (n < 0) {
        size = n + size;
        if (size > 0) {
            copy_to_regs(line, -n, image, 0, size);
        }
    } else {
        if ((n + size) > area) size = area - n;
        if (size > 0) {
            copy_to_regs(line, 0, image, n, size);
        }
    }

   #pragma hls_unroll
    for (p=0; p<STRIDE; p++) {
        values[p] = (((n + p) < 0) || ((n + p) >= area)) ? 0.0 : line[p];
    }
    if (chatty) {
        printf("shift in values: ");
        for (int i=0; i<STRIDE; i++) printf("%5.3f ", values[i].to_double());
        printf("\n");
    }
}


static void shift_by_stride(hw_cat_type *shift_register, hw_cat_type *input_image, index_type shift_register_size)
{
    index_type sr;

    static const bool chatty = false;

    if (chatty) {
        printf("address of shift register: %08lx \n", (unsigned long) shift_register);
        printf("shift_register_size: %d \n", shift_register_size.to_int());
        printf("Shifting in: ");
        for (int i=0; i<STRIDE; i++) printf("%5.3f ", input_image[i].to_double());
        printf("\n");
    }

   #pragma hls_unroll
    for (sr=0; sr<shift_register_size-STRIDE; sr++) {
        shift_register[sr] = shift_register[sr+STRIDE];
    }

   #pragma hls_unroll
    for (sr=0; sr<STRIDE; sr++) {
        shift_register[shift_register_size-STRIDE+sr] = input_image[sr];
    }
}

static void compute_row_col(index_type n, index_type &r, index_type &c, index_type width)
{
    // static const index_type width = IMAGE_WIDTH;

    r = n / width;
    c = n % width;
    if (c<0) {
        c += width;
        r--;
    }
}

static bool hw_in_bounds(
                  index_type r,
                  index_type c,
                  index_type height,
                  index_type width)
{
    if (r < 0)        return false;
    if (r >= height)  return false;
    if (c < 0)        return false;
    if (c >= width)   return false;
    return true;
}


static void perform_convolution(
                         raw_memory_line   *input_image,
                         raw_memory_line   *filter,
                         raw_memory_line   *output_image,
                         index_type         input_image_number,
                         hw_cat_type        bias,
                         index_type         image_height,
                         index_type         image_width,
                         index_type         filter_height,
                         index_type         filter_width)
{
    hw_cat_type partial_sum_buffer[STRIDE];
    hw_cat_type products[STRIDE][MAX_FILTER_HEIGHT * MAX_FILTER_WIDTH];
    hw_cat_type sums;
    hw_cat_type feature_load[STRIDE];
    //static hw_cat_type shift_register[FILTER_SIZE];
    static hw_cat_type shift_register[MAX_SHIFT_REGISTER_SIZE];

    // registers for computations
    hw_cat_type filter_regs[MAX_FILTER_SIZE];
    hw_cat_type image_regs[MAX_FILTER_SIZE];
    hw_cat_type product_array[MAX_FILTER_SIZE];
    hw_cat_type output_array[500];

    hw_cat_type input_regs[STRIDE];
    hw_cat_type output_regs[STRIDE];

    filter_index_type fr;
    filter_index_type fc;
    index_type output_index;
    index_type loop_entry;
    index_type image_index;
    index_type target_pixel;
    index_type tail_pixel;
    index_type lead_pixel;
    index_type shift_offset;
    index_type p_lead_pixel;
    index_type p_image_index;
    index_type p_target_pixel;
    index_type f_index;
    index_type p_index;
    index_type num;
    index_type row;
    index_type col;
    index_type pr;
    index_type pc;
    index_type rr;
    index_type cc;
    p_type p;

    // index_type image_offset;
    // index_type out_index;
    // index_type i;
    // index_type c;
    // index_type r;

    // static const index_type tail_round_up = TAIL_ROUND_UP - STRIDE;
    // static const index_type margin_round_up = MARGIN_ROUND_UP;
    // static const index_type area = AREA;
    // static const index_type mid_point_height = (FILTER_HEIGHT - 1) / 2;
    // static const index_type mid_point_width  = (FILTER_WIDTH - 1) / 2;
    // static const index_type stride = STRIDE;
    // static const index_type pixels_to_shift = AREA + SHIFT_REGISTER_SIZE;
    static const bool chatty = false;
    // static const index_type out_values = (IMAGE_HEIGHT - FILTER_HEIGHT + 1);

    // lead_pixel = the number of the pixel at the start of the shift_register
    // target_pixel = the number of the pixel at the center of the convolution kernel (lead_pixel + margin)
    // tail_pixel = the last pixel in the shift register (lead_pixel + shift_register_size)
    // total pixels needed to be shifted through is AREA + SHIFT_REGISTER_SIZE - (STRIDE -1)

    // static const index_type filter_width      = (FILTER_WIDTH);
    // static const index_type filter_height     = (FILTER_HEIGHT);
    static const index_type filter_size       = filter_height * filter_width; // (MAX_FILTER_SIZE);
    // static const index_type image_width       = (IMAGE_WIDTH);

    // variables for mixed size accelerator
     
    const index_type tail                    = ((image_width * ((filter_height - 1) / 2)) - ((filter_width - 1) / 2)) + filter_width + (STRIDE - 1);
    const index_type tail_round_up           = ( STRIDE * (((tail) + (STRIDE - 1)) / (STRIDE))) - STRIDE;
    const index_type margin                  = ((image_width * ((filter_height - 1) / 2)) + ((filter_width - 1) / 2));
    const index_type margin_round_up         = ( STRIDE * (((margin) + (STRIDE - 1)) / (STRIDE)));
    const index_type shift_register_size     = margin + tail_round_up + STRIDE;
    const index_type pixels_to_shift         = image_height * image_width + shift_register_size;
    const index_type area                    = image_height * image_width;
    const index_type mid_point_width         = (filter_width - 1)/2;
    const index_type mid_point_height        = (filter_height -1)/2;
    const index_type stride                  = STRIDE;


    copy_to_regs(filter_regs, 0, filter, 0, filter_size);

   #pragma hls_pipeline_init_interval 1

main_convolve_loop:
    for (tail_pixel = 0; tail_pixel < pixels_to_shift; tail_pixel += stride) {
        target_pixel = tail_pixel - margin_round_up;
        lead_pixel = target_pixel - tail_round_up;

        get_shift_in_values(feature_load, input_image, target_pixel, stride, area);

        shift_by_stride(shift_register, feature_load, shift_register_size);
        if ((lead_pixel  < 0) || (lead_pixel > area) || (input_image_number == 0)) {
           #pragma hls_unroll
            for (p=0; p<stride; p++) {
                partial_sum_buffer[p] = bias; // 0.0;
            }
        } else {
            copy_to_regs(partial_sum_buffer, 0, output_image, lead_pixel, stride);
        }
       #pragma hls_unroll
        for (p=0; p<STRIDE; p++) {
            p_target_pixel = target_pixel + p;
            p_lead_pixel = lead_pixel + p;
            compute_row_col(p_lead_pixel, pr, pc, image_width);

            sums = 0;

            if ((0 <= p_lead_pixel) && (p_lead_pixel < area)) {

               #pragma hls_unroll
            conv_outer_loop:
                for (fr=0; fr<filter_height; fr++) {

                   #pragma hls_unroll
                conv_inner_loop:
                    for (fc=0; fc<filter_width; fc++) {

                        rr = pr + fr - mid_point_height;
                        cc = pc + fc - mid_point_width;
                        shift_offset = fr * image_width + fc + p;
                        f_index = fr * filter_width + fc;

                        products[p][f_index] = (hw_in_bounds(rr, cc, image_height, image_width)) ? filter_regs[f_index] * shift_register[shift_offset] : 0.0;

                        if (chatty) {
                            if (hw_in_bounds(rr, cc, image_height, image_width)) {
                                printf("image_value[%d][%d]: %5.3f weight_value: %5.3f \n", rr.to_int(), cc.to_int(), shift_register[shift_offset].to_double(), filter_regs[f_index].to_double());
                            }
                        }

                        sums += products[p][f_index];
                    }
                }

                if (chatty) printf("sum[%d][%d] = %5.3f prior sum: %5.3f \n", pr.to_int(), pc.to_int(), sums.to_double(), partial_sum_buffer[p].to_double());

                partial_sum_buffer[p] += sums;
                if (chatty) {
                    if ((output_index % image_width)==0) printf("\n");
                    if (sums <0.001) printf("  -   ");
                    else printf("%5.2f ", sums.to_double());
                }
            }
        }
        if ((0 <= lead_pixel) && (lead_pixel < area)) {
            num = stride;
            if ((area - lead_pixel) < stride) {
               num = area - lead_pixel;
            }
            copy_from_regs(output_image, lead_pixel, partial_sum_buffer, 0, num);
            if (chatty) for (int q=0; q<num; q++) { printf("output_image[%d] = %f partial_sum_buffer[%d] = %f \n", lead_pixel.to_int()+q, output_image[lead_pixel+q].to_double(), q, partial_sum_buffer[q].to_double()); }
        }
    }
}


#pragma hls_design top
void catapult_conv2d(
                 cat_memory_type &debug_signal,
                 ac_channel<bool> &go,
                 ac_channel<bool> &done,
                 bool use_bias,
                 bool relu,
                 raw_bus_type memory    [0x100000],
                 index_type image_offset,
                 index_type weight_offset,
                 index_type bias_offset,
                 index_type output_offset,
                 index_type num_input_images,
                 index_type num_output_images,
                 index_type image_height,
                 index_type image_width,
                 index_type filter_height,
                 index_type filter_width
              )
{
    index_type   i;
    index_type   o;
    index_type   image_pointer;
    index_type   weight_pointer;
    index_type   output_pointer;

    raw_memory_line output_image_pr_mem[((MAX_IMAGE_SIZE) + (STRIDE - 1))/STRIDE];
    raw_memory_line output_image_mem[((MAX_IMAGE_SIZE) + (STRIDE - 1))/STRIDE];
    raw_memory_line input_image_mem[1][((MAX_IMAGE_SIZE) + (STRIDE - 1))/STRIDE];
    raw_memory_line filter_mem[((MAX_FILTER_SIZE) + (STRIDE - 1))/STRIDE];

    hw_cat_type  bias_values[500];
    hw_cat_type  bias_value;

    // static const index_type image_height = IMAGE_HEIGHT;
    // static const index_type image_width  = IMAGE_WIDTH;
           const index_type filter_size = filter_height * filter_width;
           const index_type image_size  = image_height * image_width;
    static const index_type stride = STRIDE;

    go.read();

    // read in all images for the layer
    image_pointer = image_offset;
    for (i=0; i<num_input_images; i++) {
        // load feature map from external memory into internal memory
        load_from_system_memory(memory, image_pointer, image_size, input_image_mem[i], 0);
        image_pointer += (image_size);
        //printf("convolution input image: %d \n", i);
        //print_image(input_image_mem[i], image_height, image_width);
    }

    // if (use_bias) load_from_system_memory(memory, bias_offset, num_output_images, bias_values, 0);
    // todo: write efficient load from bus to hw_cat_type array

    // read in all the bias values (usually small)
    if (use_bias) for (i=0; i<num_output_images; i++) bias_values[i] = read_from_system_memory(memory, bias_offset + i);

    output_pointer = output_offset;
    weight_pointer = weight_offset;

    for (o=0; o<num_output_images; o++) {
        for (i=0; i<num_input_images; i++) {
            // load filter from external memory into internal memory
            load_from_system_memory(memory, weight_pointer, filter_size, filter_mem, 0);
            if (use_bias) bias_value = bias_values[o]; else bias_value = 0.0;
            perform_convolution(input_image_mem[i], filter_mem, output_image_pr_mem, i, bias_value, image_height, image_width, filter_height, filter_width);
            weight_pointer += filter_size;
        }
        perform_relu(relu, output_image_mem, output_image_pr_mem, image_height, image_width);
        store_into_system_memory(output_image_mem, 0, image_height * image_width, memory, output_pointer);
        output_pointer += (image_height * image_width); // output_pointer++;
    }

    done.write(1);
}
