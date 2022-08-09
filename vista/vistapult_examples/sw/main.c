
#ifndef CLASS_PREFIX
#define CLASS_PREFIX
#endif

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

#ifdef VISTA
#include "hce_cpu_pv.h"
#endif

#ifndef HOST
#include "console.h"
#define printf console_out

int __errno;
#endif

//=====Keras layer functions=================//


void CLASS_PREFIX softmax(
             float *predictions,
             float *probabilities,
             int count)
{
    int i;
    float sum;
    float f;

    sum = 0.0;

    for (i=0; i<count; i++) {
        f = predictions[i];
        sum += exp(f);
    }

    for (i=0; i<count; i++) {
        probabilities[i] = exp(predictions[i])/sum;
    }
}

void CLASS_PREFIX load_memory(float *memory)
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


void CLASS_PREFIX scale(unsigned char *input_image, float *output_image, int count)
{
    int i;

    for (i=0; i<count; i++) {
        output_image[i] = ((float) input_image[i])/255.0;
    }
}


void CLASS_PREFIX sw_inference(unsigned char *input_image, float *memory, float *probabilities)
{
    float image[28*28];
    int image_offset = size_of_weights;
    int i;
    const int chatty = 1;

    load_memory(memory);

    scale(input_image, image, image_height * image_width);
    memcpy(memory+image_offset, image, image_height * image_width * 1 * sizeof(float));

    // print_image(memory + image_offset, image_height, image_width);
    sw_auto_infer(memory, image_offset, probabilities);

    if (chatty) {
        printf("sw prediction: \n");
        for (i=0; i<10; i++) {
           printf("%d = %8.6f \n", i, probabilities[i]);
        }
        printf("\n");
    }
}


void CLASS_PREFIX hw_inference(unsigned char *input_image, cat_memory_type *memory, float *probabilities)
{
    float image[28*28];
    int image_offset = size_of_weights;
    int i;
    const int chatty = 1;

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


int CLASS_PREFIX not_close(float a, float b)
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

void CLASS_PREFIX test_inference()
{
    static float           sw_memory[0x10000];
    static cat_memory_type hw_memory[0x10000];  // make it static so you do not blow up the stack
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
    int verbose = 1;
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


int CLASS_PREFIX p_index(float *probability)
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

unsigned int float_to_cat(float f);
float cat_to_float(unsigned int cat_value);


#ifdef VISTA
int CLASS_PREFIX mnist_main()
#else 
int main()
#endif
{
    float sw_prob[10];
    float hw_prob[10];
    int errors = 0;
    int i;

#ifdef HOST
#ifdef VISTA
    cat_memory_type *hw_memory = (cat_memory_type *) 0x40000000;
    static float           sw_memory[0x1000000];
#else // not vista, just basic host
    static cat_memory_type hw_memory[0x1000000];  // make it static so you do not blow up the stack
    static float           sw_memory[0x1000000];
#endif // not vista
#else
    cat_memory_type *hw_memory = (cat_memory_type *) 0x40800000;
    float           *sw_memory = (float *) 0x40000000;
#endif
/*

    float farray[10] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    float fcopy[10];

    set_cat_value(hw_memory, 0, -1.2);
    set_cat_value(hw_memory, 1, -3.4);
    set_cat_value(hw_memory, 2, -5.6);
    set_cat_value(hw_memory, 3, -7.8);
    set_cat_value(hw_memory, 4, -3.14159);

unsigned int bits;
    cpu_master_read(0x40000000, bits);
    printf("0: %08x\n", bits);
    cpu_master_read(0x40000004, bits);
    printf("1: %08x\n", bits);
    cpu_master_read(0x40000008, bits);
    printf("2: %08x\n", bits);
    cpu_master_read(0x4000000c, bits);
    printf("3: %08x\n", bits);
    cpu_master_read(0x40000010, bits);
    printf("4: %08x\n", bits);


    printf("0: %f \n", get_cat_value(hw_memory, 0));
    printf("1: %f \n", get_cat_value(hw_memory, 1));
    printf("2: %f \n", get_cat_value(hw_memory, 2));
    printf("3: %f \n", get_cat_value(hw_memory, 3));
    printf("4: %f \n", get_cat_value(hw_memory, 4));

    copy_to_cat(hw_memory, 10, farray, sizeof(farray)/sizeof(farray[0]));
    copy_from_cat(hw_memory, fcopy, 10, sizeof(farray)/sizeof(farray[0]));

    for (i=0; i<10; i++) printf("%d: %f \n", i+10, get_cat_value(hw_memory, i+10)); 
    for (i=0; i<10; i++) printf("%d: %f \n", i+10, fcopy[i]); 
return(0);
    cpu_master_write(0x40000000, 1);
*/
    //sc_stop();

    //test_inference();



    printf("start sw: \n");
    sw_inference(&three[0][0], sw_memory, sw_prob);

    copy_to_cat(hw_memory, 0, sw_memory, size_of_weights);

    printf("start hw: \n");
    hw_inference(&three[0][0], hw_memory, hw_prob);
printf(">>> hw done \n");

    for (i=0; i<10; i++) {
        if (not_close(sw_prob[i], hw_prob[i])) {
           printf("%d: hw: %f sw: %f \n", i, hw_prob[i], sw_prob[i]);
           errors++;
        }
    }

    record_differences(sw_memory, hw_memory, size_of_outputs);

    for (i=0; i<10; i++) printf("sw: %d : %f \n", i, sw_memory[ 9458 + i]);
    for (i=0; i<10; i++) printf("hw: %d : %f \n", i, get_cat_value(hw_memory, 9458 + i));
    if (errors) {
        printf("Test failed, hw does not match sw! \n");
        return 1;
    } else {
        printf("Test passed! \n");
        return 0;
    }
printf("bd bd bd bd, thats all folks! \n");
    return 0;
}

void c_interrupt_handler()
{
   printf("Got an interrupt \n");
   return;
}
