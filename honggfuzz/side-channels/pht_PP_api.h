#ifndef NOCODEFUZZ_PHT_PP_API_H
#define NOCODEFUZZ_PHT_PP_API_H
#include <stdint.h>

struct phtpp{
    void *memory;
    int size;
};

typedef struct phtpp *phtpp_t;
phtpp_t pht_prepare(int probe_size);
void pht_prime(phtpp_t pht,int starting_state);
void pht_probe(phtpp_t pht,int not_starting_state, uint64_t *results);
void pht_release(phtpp_t pht);

enum PHTPrediction {
    NO_BRANCH,
    TAKEN,
    NOT_TAKEN
};

#endif //NOCODEFUZZ_PHT_PP_API_H
