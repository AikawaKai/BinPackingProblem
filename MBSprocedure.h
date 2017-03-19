#ifndef MBS_H
#define MBS_H
#include "data.h"
#include "linkedList.h"
#include "hashset.h"
#include "solution.h"

typedef struct A_container
{
  int n;
  node_t *array; //lista degli elementi correnti nell'insieme A
  int *index; //lista degli index (eventualmente da eliminare dalla lista linkata)
  int sum; // inizia con 0. Ogni volta che si aggiunge un elemento si somma a sum
  int slack; // si inizializza con la dimensione del bin. Si decrementa ad ogni aggiunta.
} A_t;

void MBSsearch(int index, int n_max, float min_value, node_t *curr_node, hashset_t curr_set, hashset_t curr_best_set);
void MBS(dataset_t *d_s, sol_t *sol);
void MBSmodified(dataset_t *d_s, sol_t *sol);
sol_t * MBSsampling(dataset_t *d_s);
;
//utility
int bernoulli(float p);
node_t * prob_sorting(node_t ** head_pointer, node_t * head, float sum, int num_el);

#endif
