#ifndef __L1I_H__
#define __L1I_H__ 1

#define L1I_SETS 64

typedef struct l1ipp *l1ipp_t;

l1ipp_t l1i_prepare();
void l1i_release(l1ipp_t l1i);

int l1i_monitor(l1ipp_t l1i, int line);
int l1i_unmonitor(l1ipp_t l1i, int line);
void l1i_monitorall(l1ipp_t l1i);
void l1i_unmonitorall(l1ipp_t l1i);
int l1i_getmonitoredset(l1ipp_t l1i, int *lines, int nlines);
void l1i_randomise(l1ipp_t l1);

void l1i_probe(l1ipp_t l1, uint16_t *results);

// Slot is currently not implemented
int l1i_repeatedprobe(l1ipp_t l1, int nrecords, uint16_t *results, int slot);



#endif // __L1I_H__
