#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <assert.h>
#include <string.h>
#include <cpuid.h>

#include "pht_PP_api.h"
#include "util.h"

#define PAGE_SIZE 4096
#define FUNC_SIZE 16

const uint8_t jumpArray[FUNC_SIZE] = {0x55,0x48,0x89,0xe5,0x89,
                                       0x7d,0xfc,0x83,0x7d,0xfc,
                                       0x00,0x74,0x01,0x90,0x5d,
                                       0xc3};
/*
0:  55                      push   ebp
1:  48                      dec    eax
2:  89 e5                   mov    ebp,esp
4:  89 7d fc                mov    DWORD PTR [ebp-0x4],edi
7:  83 7d fc 00             cmp    DWORD PTR [ebp-0x4],0x0
b:  75 01                   jne    0xe
d:  90                      nop
e:  5d                      pop    ebp
f:  c3                      ret
 */

void pht_release(phtpp_t pht){
    munmap(pht->memory, FUNC_SIZE*pht->size);
    free(pht);
}

phtpp_t pht_prepare(int probe_size){
    phtpp_t pht = (phtpp_t)malloc(sizeof(struct phtpp));
    pht->memory = mmap((void*)0x30000000, FUNC_SIZE*probe_size, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    pht->size = probe_size;
    for (int i = 0; i < probe_size*FUNC_SIZE; i+=FUNC_SIZE)
        memcpy(pht->memory + i, jumpArray, FUNC_SIZE);
    return pht;
}

typedef void (*fptr1)(int);

void pht_prime(phtpp_t pht){
    void *p = pht->memory;
    int i = pht->size;

start_label:
    (*((fptr1)p))(0);
    (*((fptr1)p))(0);
    (*((fptr1)p))(0);
    (*((fptr1)p))(0);
    
    p += FUNC_SIZE;
    
    CONDITIONAL_JUMP_TO_LABEL(i, start_label);
    __asm__ volatile(".global pht_prepare_end\n\t"
                    "pht_prepare_end:");
}

static FORCE_INLINE void cpuid_serializing(void) {
    __asm__ volatile(
        "xor %%eax, %%eax\n\t"
        "cpuid" ::: "eax", "ebx", "ecx", "edx"
    );
}

void* ignore_me;

// Disable optimizations
__attribute__((optimize("O0")))
void pht_probe(phtpp_t pht, uint64_t *results){
    register void *p = pht->memory;
    register int i = pht->size;
    register uint64_t *p_result = results;
    register uint64_t start, end;
    uint32_t ecx;

start_label:
    (*((fptr1)p))(1);
    start = _rdtscp(&ecx);
    _mm_mfence();
    (*((fptr1)p))(1);
    end = _rdtscp(&ecx);
    cpuid_serializing();
    *p_result = end - start;
    p_result++;
    p += FUNC_SIZE;

    CONDITIONAL_JUMP_TO_LABEL(i, start_label);
    __asm__ volatile(".global pht_probe_end\n\t"
                    "pht_probe_end:");
}