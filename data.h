#ifndef DATA_SET
#define DATA_SET
#include <stdlib.h>
#include <stdio.h>
#include "linkedList.h"

typedef struct dataset
 {

  char *name; // case test name
  int n;          // numero di oggetti da inserire nei bin
  float bin_size;   // grandezza del bin
  int best_sol;   // miglior soluzione fino ad ora
  float *items;     // vettore degli oggetti totali
  float *sorteditems; //vettore degli oggetti ordinati
  node_t *head; //linked list

} dataset_t;

int compare_function(const void* p1, const void* p2);
void load_dataset(char *filename, dataset_t *d_s);
void free_dataset(dataset_t *d_s);
void load_dataset_from_file_pointer(FILE *filepointer, dataset_t *d_s);

#endif
