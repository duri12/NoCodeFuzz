#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <assert.h>
#include <strings.h>

#include "util.h"

#define PAGE_SIZE 4096
#define FUNC_SIZE 17

struct phtpp{
    void *memory;
    int size;
}phtpp_t;


uint64_t start = 0;
uint64_t end = 0;

void write_probe(uint8_t* p,int i){
    p[i] =0x55;
    p[i+1] =0x48;
    p[i+2] =0x89;
    p[i+3] =0xe5;
    p[i+4] =0x89;
    p[i+5] =0x7d;
    p[i+6] =0xfc;
    p[i+7] =0x83;
    p[i+8] =0x7d;
    p[i+9] =0xfc;
    p[i+10] =0x00;
    p[i+11] =0x74;
    p[i+12] =0x01;
    p[i+13] =0x90;
    p[i+14] =0x90;
    p[i+15] =0x5d;
    p[i+16] =0xc3;
}

phtpp_t pht_prepare(int probe_size){
    phtpp_t pht = (phtpp_t)malloc(sizeof(struct phtpp));
    pht->memory = mmap(0, FUNC_SIZE*probe_size, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANON, -1, 0);
    pht->size = probe_size;
    uint8_t* p = pht->memory;
    for(int i =0;i < probe_size*FUNC_SIZE; i+=FUNC_SIZE){
        write_probe(p,i);
    }
    return pht;
}

typedef void (*fptr1)(int);
void pht_prime(phtpp_t pht){
    randomize_pht();
    for(int i = 0;<pht->size; i++){
        void *p = pht->memory[i*FUNC_SIZE];
        (*((fptr1)p))(0);
        (*((fptr1)p))(0);
        (*((fptr1)p))(0);
        (*((fptr1)p))(0);
    }
}

void pht_probe(phtpp_t pht, uint16_t *results){
    for(int i = 0;<pht->size; i++){
        void *p = pht->memory[i*FUNC_SIZE];
        (*((fptr1)p))(1);
        start = rdtsc();
        (*((fptr1)p))(1);
        end = rdtsc();
        results[i] = end-start;
    }
}