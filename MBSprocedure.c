#include "linkedList.h"
#include "hashset.h"
#include "MBSprocedure.h"
#include <stdio.h>

void MBSsearch(int index, int n_max, int min_value, node_t *curr_node, hashset_t curr_set, hashset_t curr_best_set)
{
  for (int i=index; i<n_max; i++)
  {
    // EL_i = curr_nod   al primo giro
    if (curr_set->slack < min_value)
    {
      return;
    }
    if (curr_node->val <= curr_set->slack) // if el_i <= S(A)
    {
      //updateA(curr_set, curr_node, i); // A = A U {i}
      hashset_add(curr_set, curr_node);
      MBSsearch(i+1, n_max, min_value, curr_node->next, curr_set, curr_best_set); //MBSsearch(i+1)
      hashset_remove(curr_set, curr_node);
      //deleteAi(curr_set, curr_node, i); // A = A / {i}
      if (curr_best_set->slack ==0) // if(s(A*)==0) esco dalla procedura
      {
        return;
      }
    }
    curr_node = curr_node->next;
  }
  if(curr_set->slack < curr_best_set->slack) // if(s(A)<s(A*)) aggiorno se migliore
  {
    // printf("S(A*): %d S(A):%d\n", curr_best_set->slack, curr_set->slack);
    deepCopy(curr_best_set, curr_set);
  }
}

void MBS(dataset_t *d_s, sol_t *sol)
{
  node_t ** head_pointer;
  head_pointer = &(d_s->head);
  hashset_t best_A_set = hashset_create(d_s->bin_size);
  hashset_t curr_A_set = hashset_create(d_s->bin_size);
  int elem_to_insert = d_s->n;
  while (elem_to_insert>0)
  {
    add_new_bin(sol);
    MBSsearch(0, elem_to_insert, d_s->sorteditems[(d_s->n)-1], d_s->head, curr_A_set, best_A_set);
    for(int i=0; i<best_A_set->nitems; i++)
    {
      printf("elem %d: %d |",i, ((node_t **)best_A_set->items)[i]->val);
      add_item_to_bin(&(sol->bins[(sol->n)-1]), ((node_t **)best_A_set->items)[i]->val);
      remove_by_node_value(head_pointer, ((node_t **)best_A_set->items)[i]);
    }
    printf("\n");
    elem_to_insert = elem_to_insert-best_A_set->nitems;
    hashset_destroy(best_A_set);
    hashset_destroy(curr_A_set);
    best_A_set = hashset_create(d_s->bin_size);
    curr_A_set = hashset_create(d_s->bin_size);
  }
}
