#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>
#include <sched.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

uint8_t temp = 0; /* Used so compiler won’t optimize out some of the loops */



extern int randomize_pht();




static inline void nop_16() {
  asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
  asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
}

static inline void additional_ops() {
  nop_16();
  nop_16();
  nop_16();
  nop_16();
  nop_16();
  nop_16();
}


// Utilities for two-level predictor based attack

#define FORCE_INLINE __attribute__((always_inline)) inline
#define AT taken_branch(0);
#define AT_START taken_branch(0);
#define AT12 AT AT AT AT AT AT AT AT AT AT AT AT; // 12 taken branch
#define AT100 AT12 AT12 AT12 AT12 AT12 AT12 AT12 AT12 AT AT AT AT;