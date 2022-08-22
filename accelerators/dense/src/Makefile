
CATAPULT_VERSION ?= 10.5c

CATAPULT_HOME    ?= /wv/hlsb/CATAPULT/$(CATAPULT_VERSION)/PRODUCTION/aol/Mgc_home

#==============================================


WORD_SIZE        ?= 32
INTEGER_BITS     ?= 16

FUNCTION         ?= dense
ACCEL_NAME       ?= cat_accel
PAR              ?= 1

SOURCES          = testbench.cpp dense.cpp cat_access.cpp catapult_accel.cpp catapult_dense.cpp catapult_memory_master.cpp
SPEC_FILE        = $(FUNCTION).spec
HEADERS          = cat_access.h catapult_accel.h dense.h catapult_dense.h

ACCELERATOR      = ../hw/dense_$(WORD_SIZE)_$(INTEGER_BITS).v
BUS_IF           = ../hw/$(ACCEL_NAME).v
HEADER           = ../sw/$(FUNCTION).sw.h 

HOST_EXE         = testbench

CRUFT            = Catapult* catapult.log make.out design_checker_constraints.tcl design_checker_pre_build.tcl catapult.pinfo

CATAPULT         = $(CATAPULT_HOME)/bin/catapult
#CATAPULT_FLAGS   = -shell -file master_par$(PAR).tcl
CATAPULT_FLAGS   = -shell -file dense.tcl

ifgen            = ../../../if_gen/if_gen_axi

INCLUDES         = -I $(CATAPULT_HOME)/shared/include -I ../../../include -I . -I ../sw
#INCLUDES         = -I ~/catapult/include -I ../../../include -I .

OPTS             += -D FIXED_POINT -D WEIGHT_MEMORY -D MASTER -D A53
OPTS             += -D WORD_SIZE=$(WORD_SIZE)
OPTS             += -D INTEGER_BITS=$(INTEGER_BITS)


export WEIGHT_PATH = ../../../data
export PAR
export WORD_SIZE
export INTEGER_BITS

.PHONY: all run_host clean

all: $(ACCELERATOR) $(HEADER) $(BUS_IF) $(HOST_EXE)

run_host: $(HOST_EXE)
	@echo "Running host testbench"
	@./$(HOST_EXE)

$(ACCELERATOR): $(SOURCES) $(HEADERS) dense.tcl
	@echo "catapult testbench.cpp -o $(ACCELERATOR)"
	@rm -rf $(CRUFT)
	@$(CATAPULT) $(CATAPULT_FLAGS) >> make.out
	@cp Catapult/*/concat_rtl.v $@
	@rm -rf $(CRUFT)

$(HOST_EXE): $(HEADERS) $(SOURCES) 
	@echo "gcc $(SOURCES) -o $@"
	@g++ -g -o $@ $(INCLUDES) -D HOST -std=c++11 $(OPTS) $(SOURCES) >> make.out

$(BUS_IF): $(SPEC_FILE) $(SOURCES)
	@echo ifgen $(FUNCTION) $(SPEC_FILE) $(ACCEL_NAME) > $@
	@$(ifgen) $(FUNCTION) $(SPEC_FILE) $(ACCEL_NAME)
	mv $(ACCEL_NAME).v $(BUS_IF)
	mv $(FUNCTION).sw.h $(HEADER)

$(HEADER): $(SPEC_FILE) $(SOURCES)
	@echo if_gen $(SPEC_FILE) > $@
	@$(ifgen) $(FUNCTION) $(SPEC_FILE) $(ACCEL_NAME)
	mv $(ACCEL_NAME).v $(BUS_IF)
	mv $(FUNCTION).sw.h $(HEADER)

clean:
	rm -rf $(CRUFT) $(ACCELERATOR) $(HOST_EXE) $(BUS_IF) $(HEADER)


