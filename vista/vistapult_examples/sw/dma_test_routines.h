
#pragma once

#include "dma_defines.h"
#ifdef HOST
#define CLASS hce_cpu_pv::
#else // target
#define CLASS
#include "console.h"
#endif


static int write_data[SIZE];
static int read_data[SIZE];

void CLASS dma_stimulus()
{
  unsigned int i;

  printf("DMA Test Start \n");

  for (i=0; i<SIZE; i++) write_data[i] = i;

  for (i=0; i<SIZE; i++) {
    MEMORY_WRITE(SOURCE + i, write_data[i]);
  }

  //== Program DMA controller

  MEMORY_WRITE(DMA_SOURCE, SOURCE);
  MEMORY_WRITE(DMA_DESTINATION, DESTINATION);
  MEMORY_WRITE(DMA_SIZE, SIZE);

  MEMORY_WRITE(DMA_GO, 1);

  printf("DMA programming complete \n");
}

void CLASS check_results()
{
  unsigned int i;
  unsigned int errors = 0;

  for (i=0; i<SIZE; i++) read_data[i] = MEMORY_READ(DESTINATION + i);

  for (i=0; i<SIZE; i++) {
    // printf("read: %d expected: %d \n", read_data[i], write_data[i]);
    if (read_data[i] != write_data[i]) {
      errors++;
      printf("Error: at offset: %d read: %d expected: %d \n", i, read_data[i], write_data[i]);
    }
  }

  if (errors == 0) {
    printf("DMA Test Passed \n");
  } else {
    printf("DMA Test Failed \n");
  }
}
