#ifndef _UTIL_
#define _UTIL_
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



extern int randomize_pht();


void mfence();

void flush(void *p);

void maccess(void *p);

uint64_t rdtsc();

#define NOP_65() \
    __asm__ __volatile__ ( \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t")

#define RANDOM_INSTRUCTIONS() \
    "mov ecx, 0xABCDEF01; " \
    "xor edx, edx; " \
    "add eax, ecx; " \
    "sub ebx, eax; " \
    "mov esi, edx; " \
    "mov edi, ebx; " \
    "shl esi, 4; " \
    "shr edi, 4; " \
    "mov eax, esi; " \
    "mov ebx, edi; " \
    "sub ecx, edx; " \
    "xor edx, edx; " \
    "add eax, ecx; " \
    "sub ebx, eax; " \
    "mov esi, edx; " \
    "mov edi, ebx; " \
    "shl esi, 4; " \
    "shr edi, 4; "

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
#endif