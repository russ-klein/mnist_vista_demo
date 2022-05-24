
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "defines.h"
#include "digits.h"
#include "weights.h"
#include "catapult_accel.h"
#include "cat_access.h"
#include "conv_2d.h"
#include "dense.h"


//=====Keras layer functions=================//


void softmax(
             float *predictions,
             float *probabilities,
             int count)
{
    int i;
    double sum;
    double f;

    sum = 0.0;

    for (i=0; i<count; i++) {
        f = predictions[i];
        sum += exp(f);
    }

    for (i=0; i<count; i++) {
        probabilities[i] = exp(predictions[i])/sum;
    }
}

void load_memory(float *memory)
{

#ifdef HOST     // only neccesary when running on the host, when embedded the weights will be loaded into memory
    size_t r;
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

    r = fread(memory, sizeof(float), size_of_weights, weight_database);

    if (r != size_of_weights) {
        fprintf(stderr, "Unable to read in weights from file '%s' \n", weight_filename);
        perror(program_name);
        exit(0);
    }

    fclose(weight_database);

#endif
}


#include "auto_infer.h"


void scale(unsigned char *input_image, float *output_image, int count)
{
    int i;

    for (i=0; i<count; i++) {
        output_image[i] = ((float) input_image[i])/255.0;
    }
}


void sw_inference(unsigned char *input_image, float *memory, float *probabilities)
{
    float image[28*28];
    int image_offset = size_of_weights;
    int i;
    const int chatty = 0;

    load_memory(memory);

    scale(input_image, image, image_height * image_width);
    memcpy(memory+image_offset, image, image_height * image_width * 1 * sizeof(float));

    sw_auto_infer(memory, image_offset, probabilities);

    if (chatty) {
        printf("sw prediction: \n");
        for (i=0; i<10; i++) {
           printf("%d = %8.6f \n", i, probabilities[i]);
        }
        printf("\n");
    }
}


void hw_inference(unsigned char *input_image, cat_memory_type *memory, float *probabilities)
{
    float image[28*28];
    int image_offset = size_of_weights;
    int i;
    const int chatty = 0;

    load_cat_memory(memory);

    scale(input_image, image, image_height * image_width);
    copy_to_cat(memory, image_offset, image, image_height * image_width * 1); // layer1_input_images);

    hw_auto_infer(memory, image_offset, probabilities);

    if (chatty) {
        printf("hw prediction: \n");
        for (i=0; i<10; i++) {
           printf("%d = %8.6f \n", i, probabilities[i]);
        }
        printf("\n");
    }
}


int not_close(float a, float b)
{
    if (a > b) {
       if ((a - b) > 0.001) return 1; else return 0;
    }

    if (b > a) {
       if ((b - a) > 0.001) return 1; else return 0;
    }

    return 0;
}


struct features_and_labels_struct {
    unsigned char *features;
    int            label;
};

typedef struct features_and_labels_struct testdata_type;

void test_inference()
{
    static float           sw_memory[0x1000000];
    static cat_memory_type hw_memory[0x1000000];  // make it static so you do not blow up the stack
    float sw_prob[10];
    float hw_prob[10];
    float image[28*28];
    int i;
    const testdata_type   testdata[] = 
                                 { { (unsigned char *) zero,  0},
                                   { (unsigned char *) one,   1},
                                   { (unsigned char *) two,   2},
                                   { (unsigned char *) three, 3},
                                   { (unsigned char *) four,  4},
                                   { (unsigned char *) five,  5},
                                   { (unsigned char *) six,   6},
                                   { (unsigned char *) seven, 7},
                                   { (unsigned char *) eight, 8},
                                   { (unsigned char *) nine,  9} };
    bool verbose = true;
    const int num_tests = sizeof(testdata)/sizeof(testdata[0]);

    printf("testing sw inference... \n");

    for (i=0; i<num_tests; i++) {
       if (verbose) print_char_image(testdata[i].features, 28, 28);
       sw_inference(testdata[i].features, sw_memory, sw_prob);
       if (verbose) {
           printf("Label: %d \n\n", testdata[i].label);
           printf("Probabilities: \n");
           for (int p=0; p<10; p++) printf("p[%d]: %6.4f \n", p, sw_prob[p]);
           printf("\n");
       }
       if (sw_prob[testdata[i].label] > 0.5) printf("sw inference for %d passed %6.2f \n", i, sw_prob[i] * 100.0); 
                                        else printf("sw inference for %d failed %6.2f \n", i, sw_prob[i] * 100.0);
    }

    printf("testing hw inference... \n");

    for (i=0; i<num_tests; i++) {
       hw_inference(testdata[i].features, hw_memory, hw_prob);
       if (hw_prob[testdata[i].label] > 0.5) printf("hw inference for %d passed %6.2f \n", i, hw_prob[i] * 100.0); 
                        else printf("hw inference for %d failed %6.2f \n", i, hw_prob[i] * 100.0);
    }
}


int p_index(float *probability)
{
    int i;
    int max_index = 0;
    float max = 0.0;

    for (i=0; i<10; i++) {
       if (probability[i] > max) {
          max = probability[i];
          max_index = i;
       }
    }
    return max_index;
}


int main()
{
    float sw_prob[10];
    float hw_prob[10];
    int errors = 0;
    int i;

#ifdef HOST
    static cat_memory_type hw_memory[0x1000000];  // make it static so you do not blow up the stack
    static float           sw_memory[0x1000000];
#else
    cat_memory_type *hw_memory = (cat_memory_type *) 0x40000000;
    float           *sw_memory = (float *) 0x50000000;
#endif

    test_inference();

    printf("start sw: \n");
    sw_inference(&three[0][0], sw_memory, sw_prob);

    printf("start hw: \n");
    hw_inference(&three[0][0], hw_memory, hw_prob);

    for (i=0; i<10; i++) {
        if (not_close(sw_prob[i], hw_prob[i])) {
           printf("%d: hw: %f sw: %f \n", i, hw_prob[i], sw_prob[i]);
           errors++;
        }
    }

    record_differences(sw_memory, hw_memory, size_of_outputs);

    if (errors) {
        printf("Test failed, hw does not match sw! \n");
        return 1;
    } else {
        printf("Test passed! \n");
        return 0;
    }

    return 0;
}

