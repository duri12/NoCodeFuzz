//
// Created by ofir shapira on 16/02/2024.
//

#ifndef OS_PROJECT_HASHTABLE_H
#define OS_PROJECT_HASHTABLE_H
typedef struct Histogram *Histogram;

/* create a new empty Histogram */
Histogram HistogramCreate(void);

/* destroy a Histogram */
void HistogramDestroy(Histogram);

/* insert a new key-value pair into an existing Histogram */
void HistogramInsert(Histogram, const char *key, int value);

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
const char *HistogramSearch(Histogram, const char *key);

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void HistogramDelete(Histogram, const char *key);

#endif //OS_PROJECT_HASHTABLE_H
