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

//const uint8_t jumpArray[FUNC_SIZE] = {0x83, 0xff, 0x00, 0x90,0x74,  0x01, 0x90, 0xc3};
const uint8_t jumpArray[FUNC_SIZE] = {0x40, 0x31, 0xd2, 0x89, 0xf8, 0xff, 0xc7, 0xf7, 0xff, 0x85, 0xd2, 0x74, 0x02,
                                      0x48, 0x48, 0xc3};
//const uint8_t jumpArray[FUNC_SIZE] = {0x55,0x48,0x89,0xe5,0x89,
//                                      0x7d,0xfc,0x83,0x7d,0xfc,
//                                      0x00,0x74,0x01,0x90,0x5d,
//                                      0xc3};
//const uint8_t jumpArray[FUNC_SIZE] = {0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x83,0xff,0x00,0x90,0x75,0x01,0x90,0xc3};

//{0x31,0xd2,0x89,0xf8,0xbf,0x01,0x00,0x00,0x00,0xf7,0xff,0x85
//,0xc0,0x74,0x00,0xc3};

/*
0:  40                      inc    eax
1:  31 d2                   xor    edx,edx
3:  89 f8                   mov    eax,edi
5:  ff c7                   inc    edi
7:  f7 ff                   idiv   edi
9:  85 d2                   test   edx,edx
b:  74 02                   je     0xf
d:  48                      dec    eax
e:  48                      dec    eax
f:  c3                      ret
 */
void pht_release(phtpp_t pht) {
    munmap(pht->memory, FUNC_SIZE * pht->size);
    free(pht);
}

phtpp_t pht_prepare(int probe_size , void * where ) { //0x3000000
    phtpp_t pht = (phtpp_t) malloc(sizeof(struct phtpp));
    for (int i = 0;i<8; i++){
        pht->memory[i] = mmap(where + i*0x100000, FUNC_SIZE * probe_size + i*2, PROT_READ | PROT_WRITE | PROT_EXEC,
                             MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        pht->memory[i] += i*2;
    }
    pht->size = probe_size;
    for (int i = 0; i < probe_size * FUNC_SIZE; i += FUNC_SIZE){
        for (int j = 0; j < 8; ++j) {
            memcpy(pht->memory[j] + i, jumpArray, FUNC_SIZE);

        }
    }
    return pht;
}

//typedef void (*fptr1)(int);
typedef void (*fptr1)();

void pht_prime(phtpp_t pht, int way,int *off , int arrLength) {
    void *p = pht->memory[way];
    int i = arrLength;

    start_label:
    (*((fptr1) p))(0);
    (*((fptr1) p))(0);
    (*((fptr1) p))(0);
    (*((fptr1) p))(0);
    (*((fptr1) p))(0);

    p += FUNC_SIZE*off[i-1];

    CONDITIONAL_JUMP_TO_LABEL(i, start_label);
        __asm__ volatile(".global pht_prepare_end\n\t"
                         "pht_prepare_end:");
    }

static FORCE_INLINE void cpuid_serializing(void) {
    __asm__ volatile(
            "xor %%eax, %%eax\n\t"
            "cpuid":: : "eax", "ebx", "ecx", "edx"
            );
}

void *ignore_me;

// Disable optimizations
__attribute__((optimize("O0")))
void pht_probe(phtpp_t pht, uint64_t *results, int way,int *off , int arrLength) {
    register void *p = pht->memory[way];
    register int i = arrLength;
    register uint64_t *p_result = results;
    register uint64_t start, end;
    uint32_t ecx;

    start_label:
    (*((fptr1) p))(1);
    start = _rdtscp(&ecx);
    _mm_mfence();
    (*((fptr1) p))(1);
    end = _rdtscp(&ecx);
    cpuid_serializing();
    *p_result = end - start;
    p_result++;
    p += FUNC_SIZE*off[i-1];

    CONDITIONAL_JUMP_TO_LABEL(i, start_label);
        __asm__ volatile(".global pht_probe_end\n\t"
                         "pht_probe_end:");
    }
