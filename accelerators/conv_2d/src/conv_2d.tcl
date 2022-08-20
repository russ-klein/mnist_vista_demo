solution file add ./testbench.cpp
solution file add ./catapult_conv2d.cpp
solution file add ./catapult_accel.cpp
solution file add ./dense.cpp
solution file add ./catapult_memory_master.cpp
solution file add ./cat_access.cpp
options set Input/CompilerFlags {-D PAR_IN=1 -D FIXED_POINT -D HOST -I ../../../include}
go analyze
go compile
solution library add nangate-45nm_beh -- -rtlsyntool DesignCompiler -vendor Nangate -technology 045nm
solution library add rom_nangate-45nm-sync_regin_beh
solution library add ccs_sample_mem
solution library add amba
go libraries
directive set -CLOCKS {clk {-CLOCK_PERIOD 10 -CLOCK_EDGE rising -CLOCK_HIGH_TIME 5 -CLOCK_OFFSET 0.000000 -CLOCK_UNCERTAINTY 0.0 -RESET_KIND sync -RESET_SYNC_NAME rst -RESET_SYNC_ACTIVE high -RESET_ASYNC_NAME arst_n -RESET_ASYNC_ACTIVE low -ENABLE_NAME {} -ENABLE_ACTIVE high}}
go assembly
go architect
go allocate
go extract
