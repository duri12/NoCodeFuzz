#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <assert.h>
#include <strings.h>

#include "pht_PP_api.h"
#include "util.h"

#define PAGE_SIZE 4096
#define FUNC_SIZE 16

const uint8_t jumpArray[FUNC_SIZE] = {0x55,0x48,0x89,0xe5,0x89,
                                       0x7d,0xfc,0x83,0x7d,0xfc,
                                       0x00,0x74,0x01,0x90,0x5d,
                                       0xc3};

void write_probe(uint8_t* p){
   for (int i = 0; i <FUNC_SIZE;i++){
       p[i] =jumpArray[i];
   }
}


void pht_release(phtpp_t pht){
    munmap(pht->memory, FUNC_SIZE*pht->size);
    bzero(pht, sizeof(struct phtpp));
    free(pht);
}


phtpp_t pht_prepare(int probe_size){
    phtpp_t pht = (phtpp_t)malloc(sizeof(struct phtpp));
    pht->memory = mmap(0, FUNC_SIZE*probe_size, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANON, -1, 0);
    pht->size = probe_size;
    uint8_t* p = pht->memory;
    for(int i =0;i < probe_size*FUNC_SIZE; i+=FUNC_SIZE)
    {
        write_probe(p+i);
    }
    return pht;
}


typedef void (*fptr1)(int);
void pht_prime(phtpp_t pht,int starting_state){
    randomize_pht();
    for(int i = 0;i<pht->size; i++){
        void *p = (pht->memory+i*FUNC_SIZE);
        (*((fptr1)p))(starting_state);
        (*((fptr1)p))(starting_state);
        (*((fptr1)p))(starting_state);
        (*((fptr1)p))(starting_state);
    }
}


void pht_probe(phtpp_t pht,int not_starting_state, uint64_t *results){
    uint64_t start = 0;
    uint64_t end = 0;
    for(int i = 0;i < pht->size; i++){
        void *p = (pht->memory+i*FUNC_SIZE);
        (*((fptr1)p))(not_starting_state);
        start = rdtsc();
        (*((fptr1)p))(not_starting_state);
        end = rdtsc();
        results[i] = end-start;
    }
}