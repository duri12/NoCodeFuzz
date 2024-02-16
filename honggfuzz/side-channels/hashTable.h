//
// Created by ofir shapira on 16/02/2024.
//

#ifndef OS_PROJECT_HASHTABLE_H
#define OS_PROJECT_HASHTABLE_H

struct Histogram {
    int size;           /* size of the pointer table */
    int n;              /* number of elements stored */
    struct elt **table;
    int keySize;
};
typedef struct Histogram* Histogram;

/* create a new empty Histogram */
Histogram HistogramCreate(void);

/* destroy a Histogram */
void HistogramDestroy(Histogram);

/* insert a new key-value pair into an existing Histogram */
void HistogramInsert(Histogram, uint8_t *key, int value);

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
int HistogramSearch(Histogram, uint8_t *key);

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void HistogramDelete(Histogram, uint8_t *key);

#endif //OS_PROJECT_HASHTABLE_H
