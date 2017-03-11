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
    printf("S(A*): %d S(A):%d\n", curr_best_set->slack, curr_set->slack);
    deepCopy(curr_best_set, curr_set);
  }
}

void MBS(dataset_t *d_s, sol_t *sol)
{
}
