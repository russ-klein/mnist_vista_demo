
#include "defines.h"
#include "cat_access.h"

#ifdef VISTA
#include "hce_cpu_pv.h"
#endif
//#error #CLASS_PREFIX
//#define CLASS_PREFIX hce_cpu_pv::
//#error #CLASS_PREFIX

// catapult memory access routines


//=====Weight/scratchpad memory==============//

// everything that reads and writes the weight/scratchpad memory should be of the type "cat_memory_type"
// and should use the routines set|get_cat_value() and copy_to|from_cat() as the type will be different 
// ac_fixed or native float types at different times
// this keeps all the conversions in one place

#ifdef FIXED_POINT
#ifdef HOST
#ifdef VISTA
float CLASS_PREFIX get_cat_value(cat_memory_type *memory, int offset)
{
    unsigned int     array_word;
    unsigned int     index = (offset / (WORD_SIZE/32)) * 4;
    unsigned int     mask = (1 << WORD_SIZE) - 1;
    unsigned long    shift = (offset % (WORD_SIZE/32)) * WORD_SIZE;
    unsigned int     sign_bit;
    unsigned int     bit_pattern;
    float            cat_value;
    hw_cat_type      value;
    ac_int<WORD_SIZE, false> ac_value;

    cpu_master_read(0x40000000 + index, array_word);
    bit_pattern = (array_word >> shift) & mask;
    ac_value = bit_pattern;
    value.set_slc(0, ac_value);
    return value.to_double();

//printf("Cat access read: offset: %d index: %d \n", offset, index);
    cpu_master_read(0x40000000 + index, array_word);
    bit_pattern = (array_word >> shift) & mask;
    sign_bit = bit_pattern >> (WORD_SIZE - 1);
    if (sign_bit == 1) bit_pattern = (~bit_pattern) + 1;
//printf("Cat access read: bit pattern: %08x \n", bit_pattern);
    cat_value = (float)(bit_pattern >> FRACTIONAL_BITS);
    cat_value += ((float)(((1 << FRACTIONAL_BITS) -1) & bit_pattern))/((float)(1<<FRACTIONAL_BITS));
    if (sign_bit == 1) cat_value = cat_value * -1.0;
//printf("Cat access read: returning: %f \n", cat_value);
    return cat_value;
}

#else
hw_cat_type get_cat_value(cat_memory_type *memory, int offset)
{
    hw_cat_type value;
    unsigned long index = offset / STRIDE;

    value.set_slc(0, memory[index].slc<WORD_SIZE>((offset % STRIDE) * WORD_SIZE));
    return value;
}
#endif
#else // not HOST (i.e. EMBEDDED)

cat_memory_type get_cat_value(cat_memory_type *memory, int offset)
{
    unsigned int     array_word;
    unsigned int     index = offset / (WORD_SIZE/32);
    unsigned int     mask = (1 << WORD_SIZE) - 1;
    unsigned long    shift = (offset % (WORD_SIZE/32)) * WORD_SIZE;
    cat_memory_type  cat_value;

    array_word = memory[index];
    cat_value = (array_word >> shift) & mask;
    return cat_value;
}

#endif
#else // not FIXED_POINT (i.e. FLOAT)   

cat_memory_type CLASS_PREFIX get_cat_value(cat_memory_type *memory, int offset)
{
    return memory[offset];
}

#endif


#ifdef FIXED_POINT
#ifdef HOST
#ifdef VISTA
void CLASS_PREFIX set_cat_value(cat_memory_type *memory, int offset, float value)
{
    unsigned int    array_word;
    unsigned int    index = (offset / (WORD_SIZE/32)) * 4;
    unsigned int    mask = (1 << WORD_SIZE) - 1;
    unsigned int    fmask = (1 << FRACTIONAL_BITS) - 1;
    unsigned long   shift = (offset % (WORD_SIZE/32)) * WORD_SIZE;
    unsigned int    bit_pattern;
    unsigned int    integer_bits;
    unsigned int    fractional_bits;
    hw_cat_type     h;

    h = value;
    bit_pattern = h.slc<WORD_SIZE>(0);

#if PAR_IN==1
    array_word = bit_pattern;
#else
    cpu_master_read(0x40000000 + index, array_word);
    array_word = array_word & (mask >> shift);
    array_word = array_word | (bit_pattern >> shift);
#endif
    cpu_master_write(0x40000000 + index, array_word);

    return;
}
/*
    t = * (int *) (void *) &value;
    t_ac = t;
   
    array_word = 

    unsigned int    array_word;
    unsigned int    index = (offset / (WORD_SIZE/32)) * 4;
    unsigned int    mask = (1 << WORD_SIZE) - 1;
    unsigned int    fmask = (1 << FRACTIONAL_BITS) - 1;
    unsigned long   shift = (offset % (WORD_SIZE/32)) * WORD_SIZE;
    unsigned int    bit_pattern;
    unsigned int    integer_bits;
    unsigned int    fractional_bits;

    fractional_bits = (value - ((float)(int) value)) * (1 << FRACTIONAL_BITS);
    fractional_bits &= fmask; // mask off integer portion
printf("value as int: %d \n", (int) value);

    integer_bits = ((int) value) << FRACTIONAL_BITS;
printf("Fractional bits: %08x Integer bits: %08x \n", fractional_bits, integer_bits);
    bit_pattern = integer_bits | fractional_bits;

printf("Cat access write: offset: %d index: %d \n", offset, index);
printf("Cat access write: setting: %f \n", value);

#if PAR_IN==1
printf("Cat access write: bit pattern: %08x \n", bit_pattern);
    array_word = bit_pattern;
#else
    cpu_master_read(0x40000000 + index, array_word);
    array_word = array_word & (mask >> shift);
    array_word = array_word | (bit_pattern >> shift);
#endif
    cpu_master_write(0x40000000 + index, array_word);
}
*/
#else
void set_cat_value(cat_memory_type *memory, int offset, hw_cat_type value)
{
    unsigned long index = offset / STRIDE;
    // hw_cat_type rv;
    ac_int <WORD_SIZE, false> temp;

    // rv.set_slc(0, value.slc<WORD_SIZE>(0));
    memory[index].set_slc((offset % STRIDE) * WORD_SIZE, value.slc<WORD_SIZE>(0));
}
#endif
#else // not HOST (i.e. EMBEDDED)

void CLASS_PREFIX set_cat_value(cat_memory_type *memory, int offset, hw_cat_type value)
{
    unsigned int     array_word;
    unsigned int     index = offset / (WORD_SIZE/32);
    unsigned int     mask = (1 << WORD_SIZE) - 1;
    unsigned long    shift = (offset % (WORD_SIZE/32)) * WORD_SIZE;

    array_word = memory[offset/STRIDE];
    array_word = array_word & (mask >> shift);
    array_word = array_word | (value >> shift);
    memory[offset/STRIDE] = array_word;
}   
#endif // not HOST
#else // not FIXED_POINT (i.e. FLOAT)

void CLASS_PREFIX set_cat_value(cat_memory_type *memory, int offset, cat_memory_type value)
{
    memory[offset] = value;
}

#endif // not FIXED_POINT


void CLASS_PREFIX copy_to_cat(cat_memory_type *memory, int offset, float *source, int size)
{
    int i;
    hw_cat_type temp;
    float set_value, expected;

    for (i=0; i<size; i++) {
       set_cat_value(memory, offset+i, source[i]);
       set_value = get_cat_value(memory, offset+i);
       temp = source[i];
       expected = temp.to_double();
       if (set_value != expected) {
          printf("Expected: %f got: %f bit_pattern: %08x \n", expected, set_value, 0xFFFFFFFF);
       }
    }
}

void CLASS_PREFIX copy_from_cat(cat_memory_type *memory, float *dest, int offset, int size)
{
    int i;
#ifdef HOST
#ifdef VISTA
    for (i=0; i<size; i++) dest[i] = get_cat_value(memory, offset + i);
#else
    for (i=0; i<size; i++) dest[i] = get_cat_value(memory, offset + i).to_double();
#endif
#else // not HOST
    for (i=0; i<size; i++) dest[i] = get_cat_value(memory, offset + i);
#endif // noy HOST
}

