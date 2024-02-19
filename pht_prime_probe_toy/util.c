#include "util.h"


void mfence() {
    __asm__ volatile("mfence");
}

void flush(void *p) {
    __asm__ volatile("clflush 0(%0)\n" : : "c"(p) : "rax");
}

void maccess(void *p) {
    __asm__ volatile("movq (%0), %%rax\n" : : "c"(p) : "rax");
}

uint64_t rdtsc() {
    uint64_t a, d;
    __asm__ volatile("mfence");
    __asm__ volatile("rdtscp" : "=a"(a), "=d"(d) :: "rcx");
    a = (d << 32) | a;
    __asm__ volatile("mfence");
    return a;
}
