#include <stdio.h>

#include "defines.h"
#include "cat_access.h"
#include "dense.h"

#ifdef VISTA
#include "hce_cpu_pv.h"
#endif

void CLASS_PREFIX dense_sw(
              float *input_image,
              float *weights,
              float *biases,
              float *output_image,
              int num_units,
              int unit_count,
              int output_image_elements,
              int relu,
              int bias)
{

    int i, n, c;
    float sum;
    float bias_value;
    int chatty = 0;

    for (i=0; i<output_image_elements; i++) {
        sum = 0.0;
        for (n=0; n<num_units; n++) {
            for (c=0; c<unit_count; c++) {
                sum += input_image[n * unit_count + c] * weights[(i*num_units*unit_count)+n*unit_count+c];
                if (chatty) printf("image_value: %5.3f weight_value: %5.3f product: %5.3f sum: %5.3f \n",
                       input_image[n * unit_count + c], weights[(i*num_units*unit_count)+n*unit_count+c], 
                       input_image[n * unit_count + c] * weights[(i*num_units*unit_count)+n*unit_count+c], sum);
            }
        }
        if (bias) {
            bias_value = biases[i];
            output_image[i] = sum + bias_value;
        } else {
            output_image[i] = sum;
        }
        if (relu) {
            if (output_image[i] <0) output_image[i] = 0;
        }
    }
}

#ifdef HOST
#ifdef ALGORITHMIC_VERSION

void CLASS_PREFIX dense_hw(
              cat_memory_type *memory,
              int input_image,
              int weights,
              int biases,
              int output_image,
              int num_units,
              int unit_count,
              int output_image_elements,
              int relu,
              int bias)
{

    int i, n, c;
    hw_cat_type sum;
    hw_cat_type bias_value;
    int chatty = 0;

    for (i=0; i<output_image_elements; i++) {
        sum = 0.0;
        for (n=0; n<num_units; n++) {
            for (c=0; c<unit_count; c++) {
                sum += get_cat_value(memory, input_image + n * unit_count + c) *
                       get_cat_value(memory, weights + (i*num_units*unit_count)+n*unit_count+c);
                // sum += input_image[n * unit_count + c] * weights[(i*num_units*unit_count)+n*unit_count+c];
                // if (chatty) printf("image_value: %5.3f weight_value: %5.3f product: %5.3f sum: %5.3f \n",
                //       input_image[n * unit_count + c], weights[(i*num_units*unit_count)+n*unit_count+c], 
                //       input_image[n * unit_count + c] * weights[(i*num_units*unit_count)+n*unit_count+c], sum);
            }
        }
        if (bias) {
            bias_value = get_cat_value(memory, biases + i); // biases[i];
            set_cat_value(memory, output_image + i, sum + bias_value); // output_image[i] = sum + bias_value;
        } else {
            set_cat_value(memory, output_image + i, sum); // output_image[i] = sum;
        }
        if (relu) {
            //if (output_image[i] <0) output_image[i] = 0;
            if (get_cat_value(memory, output_image + i) < 0) set_cat_value(memory, output_image + i, 0); // output_image[i] = 0;
        }
    }
}

#endif

#ifdef ARCHITECTURE_VERSION

#include "catapult_dense.h"

void CLASS_PREFIX dense_hw(
              cat_memory_type *memory,
              int input_image,
              int weights,
              int biases,
              int output_image,
              int num_units,
              int unit_count,
              int output_image_elements,
              int relu,
              int bias)
{
    ac_channel<bool> go;
    ac_channel<bool> done;

    cat_memory_type debug_signal;

    raw_bus_type *memory_base = memory;

    go.write(1);

    catapult_dense(
               debug_signal,
               go,
               done,
               bias,
               relu,
               memory_base,
               input_image,
               weights,
               biases,
               output_image,
               num_units,
               unit_count,
               output_image_elements);

    done.read();
}

#endif // ARCHITECTURE VERSION

#ifdef VISTA

#define DENSE_BASE    ((unsigned int) 0x80000000)

#define TB_WRITE(ADDR, DATA)          vista_master_write(ADDR, DATA); 
#define TB_READ(ADDR, DATA)           DATA = vista_master_read(ADDR);

#define DNS_GO(X)                     TB_WRITE(DENSE_BASE +  0 * sizeof(unsigned int), X)  
#define DNS_GO_READY(X)               TB_READ (DENSE_BASE +  1 * sizeof(unsigned int), X)
#define DNS_DONE(X)                   TB_WRITE(DENSE_BASE +  2 * sizeof(unsigned int), X)
#define DNS_DONE_VALID(X)             TB_READ (DENSE_BASE +  3 * sizeof(unsigned int), X)
#define DNS_IMAGE_OFFSET(X)           TB_WRITE(DENSE_BASE +  4 * sizeof(unsigned int), X)
#define DNS_WEIGHT_OFFSET(X)          TB_WRITE(DENSE_BASE +  5 * sizeof(unsigned int), X)
#define DNS_BIAS_OFFSET(X)            TB_WRITE(DENSE_BASE +  6 * sizeof(unsigned int), X)
#define DNS_OUTPUT_OFFSET(X)          TB_WRITE(DENSE_BASE +  7 * sizeof(unsigned int), X)
#define DNS_NUM_UNITS(X)              TB_WRITE(DENSE_BASE +  8 * sizeof(unsigned int), X)
#define DNS_UNIT_COUNT(X)             TB_WRITE(DENSE_BASE +  9 * sizeof(unsigned int), X)
#define DNS_OUTPUT_ELEMENTS(X)        TB_WRITE(DENSE_BASE + 10 * sizeof(unsigned int), X)
#define DNS_RELU(X)                   TB_WRITE(DENSE_BASE + 11 * sizeof(unsigned int), X)
#define DNS_BIAS(X)                   TB_WRITE(DENSE_BASE + 12 * sizeof(unsigned int), X)

void CLASS_PREFIX dense_hw(
              cat_memory_type *memory,
              int input_image,
              int weights,
              int biases,
              int output_image,
              int num_units,
              int unit_count,
              int output_image_elements,
              int relu,
              int bias)
{
  int ready;
  int done;
printf("sw_side: starting the dense layer \n");
  DNS_IMAGE_OFFSET        (input_image);
  DNS_WEIGHT_OFFSET       (weights);
  DNS_BIAS_OFFSET         (biases);
  DNS_OUTPUT_OFFSET       (output_image);
  DNS_NUM_UNITS           (num_units);
  DNS_UNIT_COUNT          (unit_count);
  DNS_OUTPUT_ELEMENTS     (output_image_elements);
  DNS_RELU                (relu);
  DNS_BIAS                (bias);

  DNS_GO_READY(ready);
  while (!ready) DNS_GO_READY(ready);

  DNS_GO(1);

  DNS_DONE_VALID(done);
  while (!done) DNS_DONE_VALID(done);

  DNS_DONE(1);
printf("sw_side: done with the dense layer \n");
  return;
}

#endif

#else  // not HOST

// embedded version of dense_hw goes here


void CLASS_PREFIX dense_hw(
              cat_memory_type *memory,
              int input_image,
              int weights,
              int biases,
              int output_image,
              int num_units,
              int unit_count,
              int output_image_elements,
              int relu,
              int bias)
{
  return;
}
#endif // not HOST
