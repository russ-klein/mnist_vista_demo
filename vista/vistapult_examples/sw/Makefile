
RISCV_GCC_HOME   = /home/russk/tools/compilers/gcc_riscv
#RISCV_GCC_HOME   = /opt/riscv

AS               = $(RISCV_GCC_HOME)/bin/riscv64-unknown-elf-as
CC               = $(RISCV_GCC_HOME)/bin/riscv64-unknown-elf-gcc
LD               = $(RISCV_GCC_HOME)/bin/riscv64-unknown-elf-ld
OC               = $(RISCV_GCC_HOME)/bin/riscv64-unknown-elf-objcopy

COMMON_SOURCE    = ../../hardware_sources
OBJS             = start.o main.o console.o conv_2d.o dense.o cat_access.o catapult_accel.o

#ASFLAGS          = -a -march=rv64imafdc -mabi=lp64d
ASFLAGS          = -a -march=rv32imafc -mabi=ilp32f

CCFLAGS          = -march=rv32imafc
CCFLAGS         += -mabi=ilp32f
CCFLAGS         += -mfdiv -mdiv
#CCFLAGS          = -march=rv64imafdc -mabi=lp64d
CCFLAGS         += -fPIC 
CCFLAGS         += -I . 
CCFLAGS         += -I $(COMMON_SOURCE)
CCFLAGS         += -I ../../../include
CCFLAGS         += -D SMALL
CCFLAGS         += -D RISCV 
CCFLAGS         += -D FIXED_POINT
#CCFLAGS         += -D INTERRUPT

#ifdef DEBUG 
CCFLAGS         += -O0
CCFLAGS         += -g
#else
#CCFLAGS         += -O3 
#endif

LDFLAGS          = -m elf32lriscv 
#LDFLAGS          = -m elf64lriscv
#LDFLAGS         += -L $(RISCV_GCC_HOME)/riscv64-unknown-elf/lib/rv32imafc/ilp32f

TARGET           = dma_test

all: $(TARGET).mem bootrom.mem

$(TARGET).mem : $(TARGET).bin
	@echo "OD     $(TARGET).bin > $(TARGET).mem"
	@od --address-radix=x --output-duplicates --format=x8 --width=8 $(TARGET).bin | \
		cut -c7- > $(TARGET).mem 

$(TARGET).bin: $(TARGET).x
	@echo "OC     $(TARGET).x -O binary $(TARGET).bin"
	@$(OC) -O binary $(TARGET).x $(TARGET).bin >> make.out

$(TARGET).x: $(OBJS)
	@echo "LD     --script link.ld -o $(TARGET).x -lm "
	$(LD) -o $(TARGET).x $(OBJS) $(LDFLAGS) --script link.ld -L $(RISCV_GCC_HOME)/riscv64-unknown-elf/lib/rv32imafc/ilp32f -lc -lm /home/russk/tools/compilers/gcc_riscv/lib/gcc/riscv64-unknown-elf/8.2.0/rv32imafc/ilp32f/libgcc.a -Map $(TARGET).map >> make.out

main.o: main.c console.h conv_2d.h dense.h
	@echo "CC     main.c"
	@$(CC) $(CCFLAGS) -o main.o -c main.c >> make.out
	
conv_2d.o: conv_2d.c conv_2d.h 
	@echo "CC     conv_2d.c"
	@$(CC) $(CCFLAGS) -o conv_2d.o -c conv_2d.c >> make.out
	
dense.o: dense.c dense.h 
	@echo "CC     dense.c"
	@$(CC) $(CCFLAGS) -o dense.o -c dense.c >> make.out
	
console.o: console.c
	@echo "CC     console.c"
	@$(CC) $(CCFLAGS) -o console.o -c console.c >> make.out
	
cat_access.o: cat_access.c
	@echo "CC     cat_access.c"
	@$(CC) $(CCFLAGS) -o cat_access.o -c cat_access.c >> make.out
	
catapult_accel.o: catapult_accel.c
	@echo "CC     catapult_accel.c"
	@$(CC) $(CCFLAGS) -o catapult_accel.o -c catapult_accel.c >> make.out
	
start.o: start.s
	@echo "AS     start.s"
	@$(AS) $(ASFLAGS) -o start.o -c start.s > start.list

bootrom.mem : bootrom.bin
	@echo "OD     bootrom.bin > bootrom.mem"
	@od --address-radix=x --output-duplicates --format=x8 --width=8 bootrom.bin | \
		cut -c7- > temp.mem 
	@cat fat.mem temp.mem > bootrom.mem
	@rm temp.mem

bootrom.bin: bootrom.x
	@echo "OC     bootrom.x -O binary bootrom.bin"
	@$(OC) -O binary bootrom.x bootrom.bin >> make.out

bootrom.x: bootrom.o
	@echo "LD     --script bootrom.ld -o bootrom.x"
	@$(LD) $(LDFLAGS) -o bootrom.x bootrom.o --script bootrom.ld >> make.out

bootrom.o: bootrom.s
	@echo "AS     bootrom.s"
	@$(AS) $(ASFLAGS) -o bootrom.o -c bootrom.s > bootrom.list 


clean:
	@echo "removing created files"
	@rm -f bootrom.mem bootrom.bin bootrom.x bootrom.o bootrom.map bootrom.list $(TARGET).mem $(TARGET).bin $(TARGET).x $(TARGET).map $(OBJS) start.list make.out


