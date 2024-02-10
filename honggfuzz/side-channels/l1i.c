#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <assert.h>
#include <strings.h>

#include <mastik/low.h>
#include "l1i.h"
#include "util.h"


l1ipp_t l1i_prepare(void) {
    static uint8_t jmp[] = { JMP_OPCODE,
                             JMP_OFFSET & 0xff,
                             (JMP_OFFSET >>8) & 0xff,
                             (JMP_OFFSET >> 16) & 0xff,
                             (JMP_OFFSET >> 24) & 0xff};


    l1ipp_t l1 = (l1ipp_t)malloc(sizeof(struct l1ipp));
    l1->memory = mmap(0, PAGE_SIZE * L1I_ASSOCIATIVITY, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANON, -1, 0);
    for (int i = 0; i < L1I_SETS; i++) {
        for (int j = 0; j < L1I_ASSOCIATIVITY - 1; j++) {
            uint8_t *p = SET(j, i);
            *p++ = JMP_OPCODE;
            *p++ = JMP_OFFSET & 0xff;
            *p++ = (JMP_OFFSET >>8) & 0xff;
            *p++ = (JMP_OFFSET >> 16) & 0xff;
            *p++ = (JMP_OFFSET >> 24) & 0xff;
        }
        *SET(L1I_ASSOCIATIVITY - 1, i) = RET_OPCODE;
    }
    l1i_monitorall(l1);
    return l1;
}

void l1i_release(l1ipp_t l1i) {
    munmap(l1i->memory, PAGE_SIZE * L1I_ASSOCIATIVITY);
    bzero(l1i, sizeof(struct l1ipp));
    free(l1i);
}

int l1i_monitor(l1ipp_t l1i, int line) {
    for (int i = 0;  i < l1i->nsets; i++)
        if (l1i->monitored[i] == line)
            return 0;
    l1i->monitored[l1i->nsets++] = line;
    return 1;
}

int l1i_unmonitor(l1ipp_t l1i, int line) {
    for (int i = 0;  i < l1i->nsets; i++)
        if (l1i->monitored[i] == line) {
            l1i->monitored[i] = l1i->monitored[l1i->nsets--];
            return 1;
        }
    return 0;
}

void l1i_monitorall(l1ipp_t l1i) {
    for (int i = 0; i < L1I_SETS; i++)
        l1i->monitored[i] = i;
    l1i->nsets = L1I_SETS;
    l1i_randomise(l1i);
}

void l1i_unmonitorall(l1ipp_t l1i) {
    l1i->nsets = 0;
}


int l1i_getmonitoredset(l1ipp_t l1i, int *lines, int nlines) {
    if (lines != NULL) {
        if (nlines > l1i->nsets)
            nlines = l1i->nsets;
        for (int i = 0; i < nlines; i++)
            lines[i] = l1i->monitored[i];
    }
    return l1i->nsets;
}


int l1i_nsets(l1ipp_t l1i) {
    return l1i->nsets;
}

void l1i_randomise(l1ipp_t l1) {
    char *mem = (char *)l1->memory;
    for (int i = 0; i < l1->nsets; i++) {
        int p = random() % (l1->nsets - i) + i;
        uint8_t t = l1->monitored[p];
        l1->monitored[p] = l1->monitored[i];
        l1->monitored[i] = t;
    }
}

typedef void (*fptr)(void);
uint64_t l1i_probe(l1ipp_t l1 , uint16_t set)
{
    //TODO: switch rdtscp to our global measure tool - rdtsc
    uint64_t start = rdtsc();
    //FUTURE TODO: move every indirect access out of timing
    (*((fptr)SET(0, set)))();
    uint64_t end = rdtsc();
    uint64_t res = end - start;
    return res > UINT16_MAX ? UINT16_MAX : res;
}


void l1i_probeall(l1ipp_t l1, uint64_ts *results)
{
    for (int i = 0; i < l1->nsets; i++)
    {
        //TODO: handle cases when not all sets are tracked.
        uint16_t set = l1->monitored[i];
        uint64_t res = l1i_probe(l1, set);
        if(results) //not null (for priming mostly)
            results[set] = res;
    }

    return results;
}

//FUTURE TODO: add specific function for prime (without rdtsc,