solution file add ./testbench.cpp
solution file add ./catapult_dense.cpp
solution file add ./catapult_accel.cpp
solution file add ./dense.cpp
solution file add ./catapult_memory_master.cpp
solution file add ./cat_access.cpp
options set Input/CompilerFlags -DWORD_SIZE=$env(WORD_SIZE)
options set Input/CompilerFlags -DINTEGER_BITS=$env(INTEGER_BITS)
options set Input/CompilerFlags {-D FIXED_POINT -D HOST -I ../../../include}
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
ignore_memory_precedences -from *read_mem(dense_in_mem* -to *write_mem(dense_in_mem*
ignore_memory_precedences -from *write_mem(dense_in_mem* -to *read_mem(dense_in_mem*
go allocate
go extract
