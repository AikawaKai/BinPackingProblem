#ifndef MBS
#define MBS
#include "linkedList.h"

typedef struct A_container
{
  int n;
  node_t *array;
  int sum; // inizia con 0. Ogni volta che si aggiunge un elemento si somma a sum
  int slack; // si inizializza con la dimensione del bin. Si decrementa ad ogni aggiunta.
} A_t;

// get slack from set
int getS(A_t * set, int bin_size);

#endif
