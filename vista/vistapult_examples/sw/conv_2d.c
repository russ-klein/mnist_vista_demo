#include <stdio.h>

#ifndef CLASS_PREFIX
#define CLASS_PREFIX
#endif

#include "defines.h"
#include "cat_access.h"
#include "conv_2d.h"

#ifdef VISTA
#include "hce_cpu_pv.h"
#endif

#ifndef HOST
#include "console.h"
#define printf console_out
#endif


int CLASS_PREFIX in_bounds(
              int r,
              int c,
              int height,
              int width)
{
    if (r < 0)        return 0;
    if (r >= height)  return 0;
    if (c < 0)        return 0;
    if (c >= width)   return 0;
    return 1;
}


int CLASS_PREFIX offset(int row, int col, int image, int height, int width, int images)
{
    int start_of_array = image * height * width;
    int pixel_offset = (row * width) + col;
     
    return start_of_array + pixel_offset;
}


#define OFFSET(ROW, COL, IMAGE) offset(ROW, COL, IMAGE, height, width, num_input_images)

int CLASS_PREFIX weight_offset(int row, int col, int input_image, int output_image, int height, int width, int num_input_images, int num_output_images)
{
    return output_image * height * width * num_input_images + input_image * height * width + row * width + col;
}


#define WEIGHT_OFFSET(ROW, COL, IN_IMAGE, OUT_IMAGE) weight_offset(ROW, COL, IN_IMAGE, OUT_IMAGE, filter_height, filter_width, num_input_images, num_output_images)

void CLASS_PREFIX conv2d_sw(
               float *image,
               float *weights,
               float *biases,
               float *output_image,
               int num_input_images,
               int num_output_images,
               int height,
               int width,
               int filter_height,
               int filter_width,
               int maxpool,
               int relu,
               int bias)
{
    int  o, i, fr, fc, r, c, rr, cc, r1, c1;
    float sum;
    float max;
    float n;
    float image_value;
    float weight_value;
    float bias_value;
    int image_index;
    int weight_index;
    int output_index;
    int input_index;

    const int stride = 2;
    const int chatty = 0;
    
    for (o=0; o<num_output_images; o++) {
        for (i=0; i<num_input_images; i++) {
            for (r=0; r<height; r++) {
                for (c=0; c<width; c++) {
                    sum = 0.0;
                    for (fr=0; fr<filter_height; fr++) {
                        for (fc=0; fc<filter_width; fc++) {

                            rr = r + fr - (filter_height -1)/2;
                            cc = c + fc - (filter_width -1)/2;

                            if (in_bounds(rr, cc, height, width)) {

                                image_index = OFFSET(rr, cc, i);
                                weight_index = WEIGHT_OFFSET(fr, fc, i, o);
                                image_value = image[image_index];
                                weight_value = weights[weight_index];
    
                                if (chatty) printf("SW image_index: %d weight_index: %d image_value[%d][%d]: %5.3f weight_value: %5.3f = %5.3f \n",
                                                       image_index, weight_index, r+fr, c+fc, image_value, weight_value, image_value * weight_value);
                                sum += image_value * weight_value;
                            }
                        }
                    }
                    output_index = OFFSET(r, c, o);
                    if (i==0) n = sum; else n = sum + output_image[output_index];
                    output_image[output_index] = n;
                    if (chatty) printf("output[%d] = %5.3f \n", output_index, output_image[output_index]);
                }
            }
        }
        if (bias) {  
            for (r=0; r<height; r++) {
                for (c=0; c<width; c++) {
                    output_index = OFFSET(r, c, o);
                    image_value = output_image[output_index];
                    bias_value = biases[o];
                    output_image[output_index] = image_value + bias_value;
                }
            }
        }
        if (relu) {
            for (r=0; r<height; r++) {
                for (c=0; c<width; c++) {
                    output_index = OFFSET(r, c, o);
                    n = output_image[output_index];
                    if (n<0) output_image[output_index] = 0.0;
                }
            }
        }
        if (maxpool) {
            for (r=0; r<height/stride; r++) {
                for (c=0; c<width/stride; c++) {

                    input_index = offset(r*stride, c*stride, o, height, width, num_output_images);
                    output_index = offset(r, c, o, height/stride, width/stride, num_output_images);

                    max = output_image[input_index];
                    for (r1=0; r1<stride; r1++) {
                        for (c1=0; c1<stride; c1++) {
                            input_index = offset(r*stride + r1, c*stride + c1, o, height, width, num_output_images);

                            n = output_image[input_index];
                            if (n > max) {
                                max = n;
                            }
                        }
                    }
                    output_image[output_index] = max;
                }
            }
        }
    }
}


#ifdef HOST
#ifdef ALGORITHMIC_VERSION

void CLASS_PREFIX conv2d_hw(
               cat_memory_type *memory,
               int image,
               int weights,
               int biases,
               int output_image,
               int num_input_images,
               int num_output_images,
               int height,
               int width,
               int filter_height,
               int filter_width,
               int max_pool,
               int relu,
               int bias)
{
    int  o, i, fr, fc, r, c, rr, cc, r1, c1;
    hw_cat_type sum;
    hw_cat_type max;
    hw_cat_type n;
    hw_cat_type image_value;
    hw_cat_type weight_value;
    hw_cat_type bias_value;
    int image_index;
    int weight_index;
    int output_index;
    int input_index;

    const int chatty = 0;
    

    for (o=0; o<num_output_images; o++) {
        for (i=0; i<num_input_images; i++) {
            for (r=0; r<height; r++) {
                for (c=0; c<width; c++) {
                    sum = 0.0;
                    for (fr=0; fr<filter_height; fr++) {
                        for (fc=0; fc<filter_width; fc++) {

                            rr = r + fr - (filter_height -1)/2;
                            cc = c + fc - (filter_width -1)/2;

                            if (in_bounds(rr, cc, height, width)) {

                                image_index = OFFSET(rr, cc, i);
                                weight_index = WEIGHT_OFFSET(fr, fc, i, o);

                                image_value = get_cat_value(memory, image + image_index);
                                weight_value = get_cat_value(memory, weights + weight_index);

                                if (chatty) printf("SW image_index: %d weight_index: %d image_value[%d][%d]: %5.3f weight_value: %5.3f = %5.3f \n",
                                                   image_index, weight_index, r+fr, c+fc, image_value.to_double(), 
                                                   weight_value.to_double(), image_value.to_double() * weight_value.to_double());

                                sum += image_value * weight_value;
                            }
                        }
                    }
                    output_index = OFFSET(r, c, o);
                    if (i==0) n = sum; else n = sum + get_cat_value(memory, output_image + output_index);
                    set_cat_value(memory, output_image + output_index, n);
                    if (chatty) printf("output[%d] = %5.3f \n", output_index, n.to_double());
                }
            }
        }
        if (bias) {  
            for (r=0; r<height; r++) {
                for (c=0; c<width; c++) {
                    output_index = OFFSET(r, c, o);
                    image_value = get_cat_value(memory, output_image + output_index);
                    bias_value = get_cat_value(memory, biases + o);
                    set_cat_value(memory, output_image + output_index, image_value + bias_value);
                }
            }
        }
        if (relu) {
            for (r=0; r<height; r++) {
                for (c=0; c<width; c++) {
                    output_index = OFFSET(r, c, o);
                    n = get_cat_value(memory, output_image + output_index);
                    if (n<0) set_cat_value(memory, output_image + output_index, 0.0);
                }
            }
        }
        if (maxpool) {
            for (r=0; r<height/stride; r++) {
                for (c=0; c<width/stride; c++) {

                    input_index = offset(r*stride, c*stride, o, height, width, num_output_images);
                    output_index = offset(r, c, o, height/stride, width/stride, num_output_images);

                    max = get_cat_value(memory, output_image + input_index); // output_image[input_index];
                    for (r1=0; r1<stride; r1++) {
                        for (c1=0; c1<stride; c1++) {
                            input_index = offset(r*stride + r1, c*stride + c1, o, height, width, num_output_images);

                            n = get_cat_value(memory, output_image + input_index); // output_image[input_index];
                            if (n > max) {
                                max = n;
                            }
                        }
                    }
                    set_cat_value(memory, output_image + output_index, max); // output_image[output_index] = max;
                }
            }
        }
    }
}

#endif  // not ALGORITHMIC_VERSION

#ifdef ARCHITECTURAL_VERSION
#include "catapult_conv2d.h"

void CLASS_PREFIX conv2d_hw(
               cat_memory_type *memory,
               int image,
               int weights,
               int biases,
               int output_image,
               int num_input_images,
               int num_output_images,
               int height,
               int width,
               int filter_height,
               int filter_width,
               int relu,
               int bias)
{
    ac_channel<bool> go;
    ac_channel<bool> done;

    cat_memory_type debug_signal;

    raw_bus_type *memory_base = memory;

    go.write(1);

    catapult_conv2d(
               debug_signal,
               go,
               done,
               bias,
               relu,
               memory_base,
               image,
               weights,
               biases,
               output_image,
               num_input_images,
               num_output_images);

    done.read();
}

#endif // not ALGORITHMIC_VERSION

#ifdef VISTA

void CLASS_PREFIX vista_master_write(unsigned int addr, unsigned int data)
{
   printf("writing %08x to address %08x \n", data, addr);
   cpu_master_write(addr, data);
}

unsigned int CLASS_PREFIX vista_master_read(unsigned int addr)
{
   unsigned int data;

   cpu_master_read(addr, data); // fucking idiots!!
// printf("read  %08x from address %08x \n", data, addr);
   return(data);   
}

#define CONV2D_BASE    ((unsigned int) 0x70000000)

#define TB_WRITE(ADDR, DATA)          vista_master_write(ADDR, DATA); 
#define TB_READ(ADDR, DATA)           DATA = vista_master_read(ADDR);

#define C2D_GO(X)                     TB_WRITE(CONV2D_BASE +  0 * sizeof(unsigned int), X)  
#define C2D_GO_READY(X)               TB_READ (CONV2D_BASE +  1 * sizeof(unsigned int), X)
#define C2D_DONE(X)                   TB_WRITE(CONV2D_BASE +  2 * sizeof(unsigned int), X)
#define C2D_DONE_VALID(X)             TB_READ (CONV2D_BASE +  3 * sizeof(unsigned int), X)
#define C2D_IMAGE_OFFSET(X)           TB_WRITE(CONV2D_BASE +  4 * sizeof(unsigned int), X)
#define C2D_WEIGHT_OFFSET(X)          TB_WRITE(CONV2D_BASE +  5 * sizeof(unsigned int), X)
#define C2D_BIAS_OFFSET(X)            TB_WRITE(CONV2D_BASE +  6 * sizeof(unsigned int), X)
#define C2D_OUTPUT_OFFSET(X)          TB_WRITE(CONV2D_BASE +  7 * sizeof(unsigned int), X)
#define C2D_NUM_INPUT_IMAGES(X)       TB_WRITE(CONV2D_BASE +  8 * sizeof(unsigned int), X)
#define C2D_NUM_OUTPUT_IMAGES(X)      TB_WRITE(CONV2D_BASE +  9 * sizeof(unsigned int), X)
#define C2D_HEIGHT(X)                 TB_WRITE(CONV2D_BASE + 10 * sizeof(unsigned int), X)
#define C2D_WIDTH(X)                  TB_WRITE(CONV2D_BASE + 11 * sizeof(unsigned int), X)
#define C2D_FILTER_HEIGHT(X)          TB_WRITE(CONV2D_BASE + 12 * sizeof(unsigned int), X)
#define C2D_FILTER_WIDTH(X)           TB_WRITE(CONV2D_BASE + 13 * sizeof(unsigned int), X)
#define C2D_MAXPOOL(X)                TB_WRITE(CONV2D_BASE + 14 * sizeof(unsigned int), X)
#define C2D_RELU(X)                   TB_WRITE(CONV2D_BASE + 15 * sizeof(unsigned int), X)
#define C2D_BIAS(X)                   TB_WRITE(CONV2D_BASE + 16 * sizeof(unsigned int), X)

void CLASS_PREFIX conv2d_hw(
               cat_memory_type *memory,
               int image,
               int weights,
               int biases,
               int output_image,
               int num_input_images,
               int num_output_images,
               int height,
               int width,
               int filter_height,
               int filter_width,
               int maxpool,
               int relu,
               int bias)
{
  int ready;
  int done;

  C2D_IMAGE_OFFSET        (image);
  C2D_WEIGHT_OFFSET       (weights);
  C2D_BIAS_OFFSET         (biases);
  C2D_OUTPUT_OFFSET       (output_image);
  C2D_NUM_INPUT_IMAGES    (num_input_images);
  C2D_NUM_OUTPUT_IMAGES   (num_output_images);
  C2D_HEIGHT              (height);
  C2D_WIDTH               (width);
  C2D_FILTER_HEIGHT       (filter_height);
  C2D_FILTER_WIDTH        (filter_width);
  C2D_MAXPOOL             (maxpool);
  C2D_RELU                (relu);
  C2D_BIAS                (bias);

  C2D_GO_READY(ready);
  while (!ready) C2D_GO_READY(ready);

  C2D_GO(1);

  C2D_DONE_VALID(done);
printf("================ sw: side go =========================\n");
  while (!done) C2D_DONE_VALID(done);

  C2D_DONE(1);

printf("================ sw: side done =======================\n");
  return;
}

#endif
#else // not HOST i.e. embedded version


#define CONV2D_BASE    ((volatile unsigned int *) 0x70000000)

#define TB_WRITE(ADDR, DATA)          *(ADDR) = (DATA); 
#define TB_READ(ADDR, DATA)           DATA = *(ADDR);

#define C2D_GO(X)                     TB_WRITE(CONV2D_BASE +  0 , X)  
#define C2D_GO_READY(X)               TB_READ (CONV2D_BASE +  1 , X)
#define C2D_DONE(X)                   TB_WRITE(CONV2D_BASE +  2 , X)
#define C2D_DONE_VALID(X)             TB_READ (CONV2D_BASE +  3 , X)
#define C2D_IMAGE_OFFSET(X)           TB_WRITE(CONV2D_BASE +  4 , X)
#define C2D_WEIGHT_OFFSET(X)          TB_WRITE(CONV2D_BASE +  5 , X)
#define C2D_BIAS_OFFSET(X)            TB_WRITE(CONV2D_BASE +  6 , X)
#define C2D_OUTPUT_OFFSET(X)          TB_WRITE(CONV2D_BASE +  7 , X)
#define C2D_NUM_INPUT_IMAGES(X)       TB_WRITE(CONV2D_BASE +  8 , X)
#define C2D_NUM_OUTPUT_IMAGES(X)      TB_WRITE(CONV2D_BASE +  9 , X)
#define C2D_HEIGHT(X)                 TB_WRITE(CONV2D_BASE + 10 , X)
#define C2D_WIDTH(X)                  TB_WRITE(CONV2D_BASE + 11 , X)
#define C2D_FILTER_HEIGHT(X)          TB_WRITE(CONV2D_BASE + 12 , X)
#define C2D_FILTER_WIDTH(X)           TB_WRITE(CONV2D_BASE + 13 , X)
#define C2D_MAXPOOL(X)                TB_WRITE(CONV2D_BASE + 14 , X)
#define C2D_RELU(X)                   TB_WRITE(CONV2D_BASE + 15 , X)
#define C2D_BIAS(X)                   TB_WRITE(CONV2D_BASE + 16 , X)

void CLASS_PREFIX conv2d_hw(
               cat_memory_type *memory,
               int image,
               int weights,
               int biases,
               int output_image,
               int num_input_images,
               int num_output_images,
               int height,
               int width,
               int filter_height,
               int filter_width,
               int maxpool,
               int relu,
               int bias)
{
  int ready;
  int done;

  C2D_IMAGE_OFFSET        (image);
  C2D_WEIGHT_OFFSET       (weights);
  C2D_BIAS_OFFSET         (biases);
  C2D_OUTPUT_OFFSET       (output_image);
  C2D_NUM_INPUT_IMAGES    (num_input_images);
  C2D_NUM_OUTPUT_IMAGES   (num_output_images);
  C2D_HEIGHT              (height);
  C2D_WIDTH               (width);
  C2D_FILTER_HEIGHT       (filter_height);
  C2D_FILTER_WIDTH        (filter_width);
  C2D_MAXPOOL             (maxpool);
  C2D_RELU                (relu);
  C2D_BIAS                (bias);

  C2D_GO_READY(ready);
  while (!ready) C2D_GO_READY(ready);

  C2D_GO(1);

  C2D_DONE_VALID(done);
printf("================ sw: side go =========================\n");
  while (!done) C2D_DONE_VALID(done);

  C2D_DONE(1);

printf("================ sw: side done =======================\n");
  return;
}

#endif // not HOST


