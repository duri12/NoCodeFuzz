#include "util.h"


/* Utility functions from https://github.com/IAIK/transientfail/ */
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
void nop_16() {
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
}