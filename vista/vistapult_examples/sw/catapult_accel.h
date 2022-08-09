
hw_cat_type read_cat_memory_as_fixed(int offset);
void write_cat_memory_as_fixed(int offset, hw_cat_type value);
void load_cat_memory(cat_memory_type *memory);
int record_differences(float *sw_memory, cat_memory_type *hw_memory, int size);
void print_image(float *f, int r, int c);
void print_char_image(unsigned char *f, int r, int c);
void print_filter(float *f, int r, int c);

