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
#include <x86intrin.h>

extern void *ignore_me;

#define CONDITIONAL_JUMP_TO_LABEL(i, start_label) \
do { \
    __asm__ goto ( \
        "xor %%rax, %%rax\n\t" \
        "lea 1f(%%rip), %%rbx\n\t" \
        "lea ignore_me(%%rip), %%rcx\n\t" \
        "decl %0\n\t" \
        "cmovzq %%rbx, %%rcx\n\t" \
        "movl $0, (%%rcx)\n\t" \
        "cpuid\n\t" \
        ".byte 0xe9\n\t" \
        "1:\n\t" \
        ".long %l[" #start_label "] - . - 4\n\t" \
        "movl $(%l[" #start_label "] - .), 1b(%%rip)\n\t" \
        : "+r" (i) \
        : \
        : "rax", "rbx", "rcx", "rdx", "cc", "memory" \
        : start_label                             \
    ); \
} while(0);

extern int randomize_pht();
/*
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
*/

// Utilities for two-level predictor based attack

#define FORCE_INLINE __attribute__((always_inline)) inline
#define AT taken_branch(0);
#define AT_START taken_branch(0);
#define AT12 AT AT AT AT AT AT AT AT AT AT AT AT; // 12 taken branch
#define AT100 AT12 AT12 AT12 AT12 AT12 AT12 AT12 AT12 AT AT AT AT;

extern uint64_t rdtsc();
