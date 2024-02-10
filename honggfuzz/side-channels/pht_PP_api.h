#ifndef NOCODEFUZZ_PHT_PP_API_H
#define NOCODEFUZZ_PHT_PP_API_H

typedef struct phtpp *phtpp_t;
phtpp_t pht_prepare(int probe_size);
void pht_prime(phtpp_t pht);
void pht_probe(phtpp_t pht, uint16_t *results);

#endif //NOCODEFUZZ_PHT_PP_API_H
