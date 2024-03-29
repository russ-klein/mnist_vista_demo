
#include <string.h>

#include "defines.h"
#include "cat_access.h"
#ifdef HOST
#ifdef VISTA
  // do nothing
#else
#include "catapult_memory_master.h"
#endif
#endif

#include "regions.h"

#ifdef VISTA
#include "hce_cpu_pv.h"
#endif

/*
hw_cat_type read_cat_memory_as_fixed(int offset)
{
    raw_memory_line line;
    int major;
    int minor;
    const int chatty = 0;

    major = offset/STRIDE;
    minor = offset%STRIDE;

    if (chatty) printf("read_cat_memory_as_fixed(offset=%d) returned %5.3f \n", offset, ((hw_cat_type *)weight_memory)[offset].to_double());

    return get_bus_word(weight_memory[major], minor);

}

void write_cat_memory_as_fixed(int offset, hw_cat_type value)
{
    raw_memory_line line;
    int major;
    int minor;
    const int chatty = 0;

    major = offset/STRIDE;
    minor = offset%STRIDE;

    line = weight_memory[major];
    set_memory_word(line, minor, value);
    weight_memory[major] = line;

    //printf("write_cat_memory_as_fixed(offset=%d, value=%5.3f) \n", offset, value.to_double());
}
*/


void CLASS_PREFIX load_cat_memory(cat_memory_type *memory)
{   
#ifdef HOST  // only neccesary when running on the host, when embedded the weights will be loaded into memory

    size_t r;
    float f[1];
    int offset;

#ifdef VISTA
    float cat_value;
#else
    hw_cat_type cat_value;
#endif

    FILE *weight_database;
    char *weight_path; 
    char weight_base_filename[] = "weights_float.bin";
    char weight_filename[10240];
    
    weight_path = getenv("WEIGHT_PATH");
    
    if (weight_path) sprintf(weight_filename, "%s/%s", weight_path, weight_base_filename);
    else strcpy(weight_filename, weight_base_filename);
    
    weight_database = fopen(weight_filename, "r");
    
    if (weight_database == NULL) { 
        fprintf(stderr, "Unable to open file '%s' for reading \n", weight_filename);
        perror(program_name);
        exit(0);
    }
    
    offset = 0;
    while (!feof(weight_database)) {
       
        r = fread(f, sizeof(float), 1, weight_database);
if ((offset == 12) || (offset == 15)) printf("as read from weight_float.bin: %f \n", f[0]);
    
        if (r == 1) { 
            float expected, got;
            hw_cat_type temp;
            cat_value = f[0];
            set_cat_value(memory, offset++, cat_value);
            got = get_cat_value(0, offset-1);
            temp = f[0];
            expected = temp.to_double();
            if (got != expected) printf("Buzzzz = fail! expected: %f got: %f \n", expected, got);
        }
    }
    
    fclose(weight_database);

    printf("hw_side: weights[12] = %f \n", get_cat_value(0, 12));
    printf("hw_side: weights[15] = %f \n", get_cat_value(0, 15));
    printf("hw_side: weights[4221] = %f \n", get_cat_value(0, 4221));
    printf("hw_side: weights[4235] = %f \n", get_cat_value(0, 4235));
    printf("hw_side: weights[4236] = %f \n", get_cat_value(0, 4236));
#endif
}

/*
void conv2d_hw(
               cat_memory_type *memory,
               int image_offset,
               int weight_offset,
               int bias_offset,
               int output_offset,
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
    ac_channel<bool> go;
    ac_channel<bool> done;
    cat_memory_type debug_signal;
    raw_bus_type *memory_base = memory;

    bool fully_connected = false;
    bool convolve = true;
    
    // print_cat_image(memory, image_offset, 28, 28, 1);
    // print_cat_kernel(memory, weight_offset, 5, 5, 1);
    
    go.write(1);

    conv_par_in(
                debug_signal,
                go,
                done,
                bias,
                relu,
                convolve,
                max_pool,
                fully_connected,
                memory_base,
                image_offset,
                weight_offset,
                bias_offset,
                output_offset,
                height,
                width,
                num_input_images,
                num_output_images);

    done.read();
    
    // print_cat_image(memory, output_offset, 28, 28, 1);
}


void dense_hw(
              cat_memory_type *memory,
              int image_offset,
              int weight_offset,
              int bias_offset,
              int output_offset,
              int num_units,
              int num_input_images,
              int num_output_images,
              int relu,
              int bias)
{
    ac_channel<bool> go;
    ac_channel<bool> done;
    cat_memory_type debug_signal;
    raw_bus_type *memory_base = memory;

    bool convolve = false;
    bool max_pool = false;
    bool fully_connected = true;

    int  height = 0;
    int  width  = 0;
    
    go.write(1);

    conv_par_in(
               debug_signal,
               go,
               done,
               bias,
               relu,
               convolve,
               max_pool,
               fully_connected,
               memory_base,
               image_offset,
               weight_offset,
               bias_offset,
               output_offset,
               height,
               width,
               num_input_images,
               num_output_images);

    done.read();
}

*/

#ifdef HOST

void CLASS_PREFIX print_char_image(unsigned char *image, int height, int width)
{
   int r, c;

   printf(" \n");
   for (r=0; r<height; r++) {
      for (c=0; c<width; c++) {
         printf(" %3d", image[r * width + c]);
      }
      printf("\n");
   }
   printf("\n\n");
}


void CLASS_PREFIX print_image(float *image, int height, int width)
{
   int r, c;

   printf(" \n");
   for (r=0; r<height; r++) {
      for (c=0; c<width; c++) {
         if (image[r * width + c] > 0.001) printf(" %5.2f ", image[r * width + c]);
         else printf("   -   ");
      }
      printf("\n");
   }
   printf("\n\n");
}

void CLASS_PREFIX print_filter(float *image, int height, int width)
{
   int r, c;

   printf(" \n");
   for (r=0; r<height; r++) {
      for (c=0; c<width; c++) {
         printf(" %5.2f ", image[r * width + c]);
      }
      printf("\n");
   }
   printf("\n\n");
}



int CLASS_PREFIX region(unsigned long addr)
{
    int i;
    
    for (i=0; i<sizeof(region_map)/sizeof(region_map[0]); i++) {
        if ((addr >= region_map[i][0]) && (addr < region_map[i][0] + region_map[i][1])) return i;
    }
    return -1;
}

bool CLASS_PREFIX close(float a, float b)
{
    const float threshold = 0.001;
    
    if (abs(a-b) < threshold) return true;
    return false;
}

int CLASS_PREFIX record_differences(float *sw_memory, cat_memory_type *hw_memory, int size)
{
    // reports differences between reference sw (float) inference and the
    // hw inference by comparing the memory state, helps to islotate failures
    // when hw inferences are incorrect

    int i;
    int errors;
    float hw_value;
    float sw_value;
    hw_cat_type temp;
    FILE *f = fopen("differences.txt", "w");
    
    if (!f) {
        fprintf(stderr, "Unable to open differences file \n");
        perror(program_name);
        return 0;
    }
    
    errors = 0;
    for (i=0; i<size; i++) {
#ifdef VISTA
        hw_value = get_cat_value(hw_memory, i);
#else
        hw_value = read_from_system_memory(hw_memory, i).to_double();
#endif
        temp = sw_memory[i];
        sw_value = temp.to_double();
        if (!close(sw_value, hw_value)) {
            fprintf(f, "%25s, %10d sw: %12.7f hw: %12.7f offset: %d \n", region_names[region(i)], i, sw_value, hw_value, i - region_map[region(i)][0]);
            printf("%25s, %10d sw: %12.7f hw: %12.7f offset: %d \n", region_names[region(i)], i, sw_value, hw_value, i - region_map[region(i)][0]);
            errors++;
        }
    }
    
    fclose(f);
    
    printf("Found %d miscompares in %d values \n", errors, size);
    
    return errors;
}

#endif
