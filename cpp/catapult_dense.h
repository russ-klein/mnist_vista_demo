
#include "catapult_memory_master.h"

#pragma hls_design top

void catapult_dense(
                 cat_memory_type   &debug_signal,
                 ac_channel<bool>  &go,
                 ac_channel<bool>  &done,
                 bool               use_bias,
                 bool               relu,
                 raw_bus_type       memory[0x100000],
                 index_type         image_offset,
                 index_type         weight_offset,
                 index_type         bias_offset,
                 index_type         output_offset,
                 index_type         num_units,
                 index_type         num_input_values,
                 index_type         num_output_values);
