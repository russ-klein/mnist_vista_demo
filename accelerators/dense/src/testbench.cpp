
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defines.h"

#include "dense.h"
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
    return;
}

#define FEATURE_LENGTH 100
#define FEATURE_WIDTH    1
#define OUTPUT_LENGTH   10

#define NUM_FEATURES (FEATURE_LENGTH * FEATURE_WIDTH)
#define NUM_WEIGHTS  (NUM_FEATURES * OUTPUT_LENGTH)
#define NUM_RESULTS  (OUTPUT_LENGTH)
#define NUM_BIASES   (OUTPUT_LENGTH)

int main()
{
    float features[NUM_FEATURES];
    float weights[NUM_WEIGHTS];
    float biases[NUM_BIASES];
    float hw_results[NUM_RESULTS];
    float sw_results[NUM_RESULTS];

    cat_memory_type cat_memory[0x2000];

    const int features_offset = 0;
    const int weights_offset  = features_offset + NUM_FEATURES;
    const int bias_offset     = weights_offset + NUM_WEIGHTS;
    const int output_offset   = bias_offset + NUM_BIASES;

    initialize_data(features, NUM_FEATURES);
    initialize_data(weights, NUM_WEIGHTS);

    dense_sw(features, weights, biases, sw_results, FEATURE_LENGTH, FEATURE_WIDTH, NUM_RESULTS, 0, 0);

    copy_to_cat(cat_memory, features_offset, features, NUM_FEATURES);
    copy_to_cat(cat_memory, weights_offset, weights, NUM_WEIGHTS);
    copy_to_cat(cat_memory, bias_offset, biases, NUM_BIASES);

    dense_hw(cat_memory, features_offset, weights_offset, bias_offset, output_offset, 
              FEATURE_LENGTH, FEATURE_WIDTH, NUM_RESULTS, 0, 0);

    copy_from_cat(cat_memory, hw_results, output_offset, NUM_RESULTS);
    return 0;
} 

    


