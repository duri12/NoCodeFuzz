#ifndef NOCODEFUZZ_PHT_PP_API_H
#define NOCODEFUZZ_PHT_PP_API_H
#include <stdint.h>

struct phtpp{
    char *memory;
    int size;
};

typedef struct phtpp *phtpp_t;
struct phtpp pht_prepare(int probe_size);
void pht_prime(phtpp_t pht);
void pht_probe(phtpp_t pht, uint64_t *results);
void pht_release(phtpp_t pht);
#endif //NOCODEFUZZ_PHT_PP_API_H
