#ifndef NOCODEFUZZ_PHT_PP_API_H
#define NOCODEFUZZ_PHT_PP_API_H
#include <stdint.h>

struct phtpp{
    char *memory[8];
    int size;
};
extern int randomize_pht();
typedef struct phtpp *phtpp_t;
phtpp_t pht_prepare(int probe_size,void* where,int offset);
void pht_prime(phtpp_t pht, int way,int *off , int arrLength);
void pht_probe(phtpp_t pht, uint64_t *results, int way,int *off , int arrLength);
void pht_release(phtpp_t pht);

#endif //NOCODEFUZZ_PHT_PP_API_H
