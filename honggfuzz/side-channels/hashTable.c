//
// Created by ofir shapira on 16/02/2024.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "xxhash.h"

#include "hashTable.h"

struct elt {
    struct elt *next;
    char *key;
    int value;
};

struct Histogram {
    int size;           /* size of the pointer table */
    int n;              /* number of elements stored */
    struct elt **table;
    int keySize;
};

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)


/* Histogram initialization code used in both HistogramCreate and grow */
Histogram internalHistogramCreate(int size, int keySize)
{
    Histogram d;
    int i;

    d = malloc(sizeof(*d));

    assert(d != 0);

    d->size = size;
    d->n = 0;
    d->table = malloc(sizeof(struct elt *) * d->size);
    d->keySize = keySize;

    assert(d->table != 0);

    for(i = 0; i < d->size; i++)
    {
        d->table[i] = 0;//point to first node in cell
    }

    return d;
}

Histogram HistogramCreate(void)
{
    return internalHistogramCreate(INITIAL_SIZE);
}

void HistogramDestroy(Histogram d)
{
    int i;
    struct elt *e;
    struct elt *next;

    for(i = 0; i < d->size; i++) {
        for(e = d->table[i]; e != 0; e = next) {
            next = e->next;

            free(e->key);
            free(e);
        }
    }

    free(d->table);
    free(d);
}

#define MULTIPLIER (97)

static unsigned long hash_function(const char *s, int len)
{
    XXH64_hash_t seed = 0;
    XXH64_hash_t hash = XXH64(s, len, seed);

    return h;
}

static void grow(Histogram d)
{
    Histogram d2;            /* new Histogramionary we'll create */
    struct Histogram swap;   /* temporary structure for brain transplant */
    int i;
    struct elt *e;

    d2 = internalHistogramCreate(d->size * GROWTH_FACTOR);

    for(i = 0; i < d->size; i++) {
        for(e = d->table[i]; e != 0; e = e->next) {
            /* note: this recopies everything */
            /* a more efficient implementation would
             * patch out the strdups inside HistogramInsert
             * to avoid this problem */
            HistogramInsert(d2, e->key, e->value);
        }
    }

    /* the hideous part */
    /* We'll swap the guts of d and d2 */
    /* then call HistogramDestroy on d2 */
    swap = *d;
    *d = *d2;
    *d2 = swap;

    HistogramDestroy(d2);
}

/* insert a new key-value pair into an existing Histogramionary */
//NOTICE: key here won't be any str
void HistogramInsert(Histogram d, const char *key, int value)
{
    struct elt *e;
    unsigned long h;

    assert(key);
    assert(value);

    e = malloc(sizeof(*e));

    assert(e);

    e->key = key;
    e->value = value;

    h = hash_function(key) % d->size;

    e->next = d->table[h];
    d->table[h] = e;

    d->n++;

    /* grow table if there is not enough room */
    if(d->n >= d->size * MAX_LOAD_FACTOR) {
        grow(d);
    }
}

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
int HistogramSearch(Histogram d, const char *key)
{
    struct elt *e;

    for(e = d->table[hash_function(key) % d->size]; e != 0; e = e->next) {
        if(!memcmp(e->key, key,d.keySize)) {
            /* got it */
            return e->value;
        }
    }

    return 0;
}

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void
HistogramDelete(Histogram d, const char *key)
{
    struct elt **prev;          /* what to change when elt is deleted */
    struct elt *e;              /* what to delete */

    for(prev = &(d->table[hash_function(key) % d->size]);
        *prev != 0;
        prev = &((*prev)->next)) {
        if(!memcmp((*prev)->key, key,d->keySize)) {
            /* got it */
            e = *prev;
            *prev = e->next;

            free(e->key);
            free(e);

            return;
        }
    }
}
