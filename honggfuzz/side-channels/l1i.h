#ifndef __L1I_H__
#define __L1I_H__ 1

#define L1I_SETS 64

typedef struct l1ipp *l1ipp_t;

l1ipp_t l1i_prepare();
void l1i_release(l1ipp_t l1i);
int l1i_nsets(l1ipp_t l1i);
int l1i_monitor(l1ipp_t l1i, int line);
int l1i_unmonitor(l1ipp_t l1i, int line);
void l1i_monitorall(l1ipp_t l1i);
void l1i_unmonitorall(l1ipp_t l1i);
int l1i_getmonitoredset(l1ipp_t l1i, int *lines, int nlines);
void l1i_randomise(l1ipp_t l1);

uint64_t l1i_probe(l1ipp_t l1 , uint16_t set);
void l1i_probeall(l1ipp_t l1, uint64_t *results);

enum L1IPrediction {
    NOT_ACCESSED,
    ACCESSED
};


#endif // __L1I_H__
