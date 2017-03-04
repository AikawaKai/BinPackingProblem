#include <stdlib.h>

typedef struct dataset
 {
  char *name; // case test name
  int n;          // numero di oggetti da inserire nei bin
  int bin_size;   // grandezza del bin
  int best_sol;   // miglior soluzione fino ad ora
  int *items;     // vettore degli oggetti totali
} dataset;


void load_dataset(char *filename, dataset *d_s);
void free_dataset(dataset *d_s);
