

#pragma once

#define SIZE                     0x100
#define MEMORY                   ((unsigned int *) 0x40000000)
#define DMA                      ((unsigned int *) 0x70000000)

#define DMA_SOURCE               (DMA + 0)
#define DMA_DESTINATION          (DMA + 1)
#define DMA_SIZE                 (DMA + 2)
#define DMA_GO                   (DMA + 3)
#define DMA_DONE                 (DMA + 4)
#define DMA_INT_ACK              (DMA + 5)
 
#define SOURCE                   (MEMORY + 0)
#define DESTINATION              (MEMORY + 0x800)

#ifdef HOST 

#define MEMORY_READ(ADDR)        read_word(((long long unsigned int)(ADDR)))
#define MEMORY_WRITE(ADDR, DATA) { unsigned int x = 0xFFFFFFFF & ((long long unsigned int) (DATA)); cpu_master_write(((long long unsigned int)(ADDR)), &x, 1); }

#endif

#ifdef RISCV

#define MEMORY_READ(ADDR)        (*(volatile int *)(ADDR))
#define MEMORY_WRITE(ADDR, DATA) *((volatile int *)(ADDR)) = ((int) DATA)

#endif
