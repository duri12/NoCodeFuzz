#include "util.h"
#include <x86intrin.h>

void mfence() {
    _mm_mfence();
}

void flush(void *p) {
    _mm_clflush(p);
}

void maccess(void *p) {
    __asm__ volatile("movq (%0), %%rax\n" : : "c"(p) : "rax");
}

uint64_t rdtsc() {
    uint64_t a;
    unsigned int c;
    _mm_mfence();
    a = _rdtscp(&c);
    _mm_mfence();
    return a;
}
