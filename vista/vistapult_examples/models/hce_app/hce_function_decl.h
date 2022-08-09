float get_cat_value(cat_memory_type *memory, int offset);
//cat_memory_type get_cat_value(cat_memory_type *memory, int offset);
//cat_memory_type get_cat_value(cat_memory_type *memory, int offset);
void set_cat_value(cat_memory_type *memory, int offset, float value);
//void set_cat_value(cat_memory_type *memory, int offset, hw_cat_type value);
//void set_cat_value(cat_memory_type *memory, int offset, cat_memory_type value);
void copy_to_cat(cat_memory_type *memory, int offset, float *source, int size);
void copy_from_cat(cat_memory_type *memory, float *dest, int offset, int size);
void load_cat_memory(cat_memory_type *memory);
void print_char_image(unsigned char *image, int height, int width);
void print_image(float *image, int height, int width);
void print_filter(float *image, int height, int width);
int region(unsigned long addr);
bool close(float a, float b);
//hw_cat_type read_from_system_memory(raw_bus_type *memory, index_type offset);
int record_differences(float *sw_memory, cat_memory_type *hw_memory, int size);
int in_bounds( int r, int c, int height, int width);
int offset(int row, int col, int image, int height, int width, int images);
int weight_offset(int row, int col, int input_image, int output_image, int height, int width, int num_input_images, int num_output_images);
void conv2d_sw(float *image, float *weights, float *biases, float *output_image, int num_input_images, int num_output_images, int height, int width, int filter_height, int filter_width, int maxpool, int relu, int bias);
void conv2d_hw(cat_memory_type *memory, int image, int weights, int biases, int output_image, int num_input_images, int num_output_images, int height, int width, int filter_height, int filter_width, int maxpool, int relu, int bias);
void vista_master_write(unsigned int addr, unsigned int data);
unsigned int vista_master_read(unsigned int addr);
void dense_sw(float *input_image, float *weights, float *biases, float *output_image, int num_units, int unit_count, int output_image_elements, int relu, int bias);
void dense_hw(cat_memory_type *memory, int input_image, int weights, int biases, int output_image, int num_units, int unit_count, int output_image_elements, int relu, int bias);
void softmax(float *predictions, float *probabilities, int count);
void load_memory(float *memory);
void scale(unsigned char *input_image, float *output_image, int count);
void sw_inference(unsigned char *input_image, float *memory, float *probabilities);
int not_close(float a, float b);
void test_inference();
int p_index(float *probability);
int mnist_main();
void sw_auto_infer(float *memory, int image_offset, float *probabilities);
void hw_auto_infer(cat_memory_type *memory, int image_offset, float *probabilities);
void hw_inference(unsigned char *input_image, cat_memory_type *memory, float *probabilities);

