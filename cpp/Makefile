
CATAPULT_VERSION ?= 2022.1
CATAPULT_HOME    ?= /wv/hlsb/CATAPULT/$(CATAPULT_VERSION)/PRODUCTION/aol/Mgc_home

#==============================================

PAR              ?= 1

OBJS             = main.o
OBJS             += cat_access.o
OBJS             += catapult_accel.o
OBJS             += conv_2d.o
OBJS             += dense.o

HOST_EXE         = mnist_infer

CRUFT            = Catapult* catapult.log make.out design_checker_constraints.tcl design_checker_pre_build.tcl catapult.pinfo differences.txt *.o $(HOST_EXE)

CATAPULT         = $(CATAPULT_HOME)/bin/catapult
CATAPULT_FLAGS   = -shell -file master_par$(PAR).tcl

INCLUDES         = -I .
INCLUDES         += -I ../include
INCLUDES         += -I $(CATAPULT_HOME)/shared/include 
INCLUDES         += -I ~/catapult/include 

OPTS             = -std=c++11
OPTS             += -D HOST
OPTS             += -D FIXED_POINT
OPTS             += -D ALGORITHMIC_VERSION

QUIET_FLAG       = --no-print-directory

GCC              = g++
LD               = g++

export WEIGHT_PATH = ../data

.PHONY: all run_host clean

all: $(HOST_EXE)

run_host: $(HOST_EXE)
	@echo "Running host testbench"
	@./$(HOST_EXE)

$(HOST_EXE): $(OBJS)
	@echo "LD       -o $@"
	@echo "$(LD) -g -o $@ $(OBJS)" >> make.out
	@$(LD) -g -o $@ $(OBJS) >> make.out

MAIN_HEADERS      = defines.h
MAIN_HEADERS     += ../include/weights.h
MAIN_HEADERS     += catapult_accel.h
MAIN_HEADERS     += cat_access.h
MAIN_HEADERS     += ../include/auto_infer.h
MAIN_HEADERS     += catapult_conv2d.h
MAIN_HEADERS     += catapult_dense.h

main.o: main.cpp $(MAIN_HEADERS)
	@echo "GCC      $<"
	@echo "$(GCC) -g -c $< -o $@ $(INCLUDES) $(OPTS) " >> make.out
	@$(GCC) -g -c $< -o $@ $(INCLUDES) $(OPTS) &> make.out 

read_wave.o: read_wave.cpp read_wave.h defines.h
	@echo "GCC      $<"
	@echo "$(GCC) -g -c $< -o $@ $(INCLUDES) $(OPTS) " >> make.out
	@$(GCC) -g -c $< -o $@ $(INCLUDES) $(OPTS) >> make.out

cat_access.o: cat_access.cpp cat_access.h defines.h
	@echo "GCC      $<"
	@echo "$(GCC) -g -c $< -o $@ $(INCLUDES) $(OPTS) " >> make.out
	@$(GCC) -g -c $< -o $@ $(INCLUDES) $(OPTS) >> make.out

catapult_accel.o: catapult_accel.cpp catapult_accel.h defines.h ../include/regions.h
	@echo "GCC      $<"
	@echo "$(GCC) -g -c $< -o $@ $(INCLUDES) $(OPTS) " >> make.out
	@$(GCC) -g -c $< -o $@ $(INCLUDES) $(OPTS) >> make.out

conv_2d.o: conv_2d.cpp conv_2d.h defines.h cat_access.h
	@echo "GCC      $<"
	@echo "$(GCC) -g -c $< -o $@ $(INCLUDES) $(OPTS) " >> make.out
	@$(GCC) -g -c $< -o $@ $(INCLUDES) $(OPTS) >> make.out

dense.o: dense.cpp dense.h defines.h cat_access.h
	@echo "GCC      $<"
	@echo "$(GCC) -g -c $< -o $@ $(INCLUDES) $(OPTS) " >> make.out
	@$(GCC) -g -c $< -o $@ $(INCLUDES) $(OPTS) >> make.out

mfcc.o: mfcc.cpp mfcc.h
	@echo "GCC      $<"
	@echo "$(GCC) -g -c $< -o $@ $(INCLUDES) $(OPTS) " >> make.out
	@$(GCC) -g -c $< -o $@ $(INCLUDES) $(OPTS) >> make.out

clean:
	@echo "Removing created files and cruft"
	@rm -rf $(CRUFT) $(HOST_EXE) 
