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
#include "util.h"
uint8_t temp1 = 0; /* Used so compiler won’t optimize out some of the loops */


void mfence() {
    /* Utility functions from https://github.com/IAIK/transientfail/ */
    __asm__ volatile("mfence");
}

void flush(void *p) {
    /* Utility functions from https://github.com/IAIK/transientfail/ */
    __asm__ volatile("clflush 0(%0)\n" : : "c"(p) : "rax");
}

void maccess(void *p) {
    /* Utility functions from https://github.com/IAIK/transientfail/ */
    __asm__ volatile("movq (%0), %%rax\n" : : "c"(p) : "rax");
}

uint64_t rdtsc() {
    /* Utility functions from https://github.com/IAIK/transientfail/ */
    uint64_t a, d;
    __asm__ volatile("mfence");
    __asm__ volatile("rdtscp" : "=a"(a), "=d"(d) :: "rcx");
    a = (d << 32) | a;
    __asm__ volatile("mfence");
    return a;
}


