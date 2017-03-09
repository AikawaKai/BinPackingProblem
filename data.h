#include <stdlib.h>
#include "linkedList.h"

typedef struct dataset
 {
  char *name; // case test name
  int n;          // numero di oggetti da inserire nei bin
  int bin_size;   // grandezza del bin
  int best_sol;   // miglior soluzione fino ad ora
  int *items;     // vettore degli oggetti totali
  int *sorteditems;
  node_t *head;
} dataset_t;


void load_dataset(char *filename, dataset_t *d_s);
void free_dataset(dataset_t *d_s);
