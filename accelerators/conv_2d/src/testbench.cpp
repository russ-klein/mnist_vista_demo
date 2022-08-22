
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defines.h"

#include "conv_2d.h"
#include "cat_access.h"

static void initialize_data(float *f, int n)
{
    const int random_seed = 0;
    static int first = true;
    int i;

    if (first) {
       if (random_seed) {
          srand(time(NULL));
       } else {
          srand(31795);
       }
    }

    for (i=0; i<n; i++) f[i] = 2.0 * (float) rand() / (float) RAND_MAX - 1.0;
    // for (i=0; i<n; i++) f[i] = (float) i;
    return;
}

int compare(float *a, float *b, int n)
{
   int errors = 0;

   for (int i=0; i<n; i++) {
      if (abs(a[i]-b[i])>0.001) {
         printf("mismatch at %d a[%d] = %f b[%d] = %f \n", i, i, a[i], i, b[i]);
         errors++;
      }
   }
   return errors;
}

#define T_IMAGE_HEIGHT  7
#define T_IMAGE_WIDTH   7

#define T_FILTER_WIDTH     7
#define T_FILTER_HEIGHT    7

#define NUM_INPUTS       1
#define NUM_OUTPUTS      1

#define NUM_FEATURES (T_IMAGE_HEIGHT * T_IMAGE_WIDTH * NUM_INPUTS)
#define NUM_WEIGHTS  (T_FILTER_HEIGHT * T_FILTER_WIDTH * NUM_OUTPUTS)
#define NUM_BIASES   (NUM_OUTPUTS)
#define NUM_RESULTS  (T_IMAGE_HEIGHT * T_IMAGE_WIDTH * NUM_OUTPUTS)

#define TOTAL_SIZE   (T_IMAGE_HEIGHT * T_IMAGE_WIDTH * NUM_OUTPUTS)

int main()
{
    int errors;
    float features[NUM_FEATURES];
    float weights[NUM_WEIGHTS] = {0,0,0, 0,1,0, 0,0,0}; // {0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0};
    float biases[NUM_BIASES];
    float hw_results[NUM_RESULTS];
    float sw_results[NUM_RESULTS];

    cat_memory_type cat_memory[0x2000];

    printf("word_size: %d \n", WORD_SIZE);
    printf("integer_bits: %d \n", INTEGER_BITS);
    printf("fractional_bits: %d \n", FRACTIONAL_BITS);
    printf("par_in: %d \n", PAR_IN);

    const int features_offset = 0;
    const int weights_offset  = features_offset + NUM_FEATURES;
    const int bias_offset     = weights_offset + NUM_WEIGHTS;
    const int output_offset   = bias_offset + NUM_BIASES;

    initialize_data(features, NUM_FEATURES);
    initialize_data(weights, NUM_WEIGHTS);

    conv2d_sw(features, weights, biases, sw_results, NUM_INPUTS, NUM_OUTPUTS, 
               T_IMAGE_HEIGHT, T_IMAGE_WIDTH, T_FILTER_HEIGHT, T_FILTER_WIDTH, 0, 0, 0);

    copy_to_cat(cat_memory, features_offset, features, NUM_FEATURES);
    copy_to_cat(cat_memory, weights_offset, weights, NUM_WEIGHTS);
    copy_to_cat(cat_memory, bias_offset, biases, NUM_BIASES);

    conv2d_hw(cat_memory, features_offset, weights_offset, bias_offset, output_offset, NUM_INPUTS, NUM_OUTPUTS,
              T_IMAGE_HEIGHT, T_IMAGE_WIDTH, T_FILTER_HEIGHT, T_FILTER_WIDTH, 0, 0, 0);
    copy_from_cat(cat_memory, hw_results, output_offset, NUM_RESULTS);

    errors = compare(hw_results, sw_results, TOTAL_SIZE);

    printf("%d errors \n", errors);
    return errors;
}
