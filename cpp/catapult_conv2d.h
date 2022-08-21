
#include "catapult_memory_master.h"

void catapult_conv2d(
                 cat_memory_type &debug_signal,
                 ac_channel<bool> &go,
                 ac_channel<bool> &done,
                 bool use_bias,
                 bool relu,
                 raw_bus_type memory    [0x100000],
                 index_type image_offset,
                 index_type weight_offset,
                 index_type bias_offset,
                 index_type output_offset,
                 index_type num_input_images,
                 index_type num_output_images,
                 index_type image_height,
                 index_type image_width,
                 index_type filter_height,
                 index_type filter_width
     );

