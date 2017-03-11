#ifndef MBS
#define MBS
#include "linkedList.h"
#include "hashset.h"

typedef struct A_container
{
  int n;
  node_t *array; //lista degli elementi correnti nell'insieme A
  int *index; //lista degli index (eventualmente da eliminare dalla lista linkata)
  int sum; // inizia con 0. Ogni volta che si aggiunge un elemento si somma a sum
  int slack; // si inizializza con la dimensione del bin. Si decrementa ad ogni aggiunta.
} A_t;

void MBSsearch(int index, int n_max, int min_value, node_t *curr_node, hashset_t curr_set, hashset_t curr_best_set);

#endif
