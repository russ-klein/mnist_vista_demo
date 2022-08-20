
#define INDEX_BITS          25
#define PAR_BITS            (PAR_IN + BUS_WIDTH)

#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"

typedef ac_int<PAR_BITS, false>     p_type;
typedef ac_int<INDEX_BITS, true>    index_type;

typedef ac_int<BUS_WIDTH * PAR_IN * WORD_SIZE, false> raw_memory_line;

void copy_from_regs(raw_memory_line *dst, index_type dst_offset, hw_cat_type *src, index_type src_offset, index_type size);
void copy_to_regs(hw_cat_type *dst, index_type dst_offset, raw_memory_line *src, index_type src_offset, index_type size);
void store_into_system_memory(raw_memory_line *output_array, index_type array_offset, index_type size,  raw_bus_type *memory, index_type offset);
void load_from_system_memory(raw_bus_type *memory, index_type offset, index_type size, raw_memory_line *input_array, index_type array_offset);
hw_cat_type read_from_system_memory(raw_bus_type *memory, index_type offset);



