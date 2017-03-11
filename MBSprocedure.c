#include "linkedList.h"
#include "MBSprocedure.h"

void MBSsearch(int index, int n_max, node_t *curr_node, A_t *curr_set, A_t *curr_best_set)
{
  for (int i=index; i<n_max; i++)
  {
    // EL_i = curr_nod   al primo giro
    if (curr_node->val <= curr_set->slack) // if el_i <= S(A)
    {
      //updateA(curr_set, curr_node, i); // A = A U {i}
      MBSsearch(i+1, n_max, curr_node->next, curr_set, curr_best_set); //MBSsearch(i+1)
      //deleteAi(curr_set, curr_node, i); // A = A / {i}
      if (curr_best_set->slack ==0) // if(s(A*)==0) esco dalla procedura
      {
        return;
      }
    }
  }
  if(curr_set->slack < curr_best_set->slack) // if(s(A)<s(A*)) aggiorno se migliore
  {
    //fillWithAnotherSet(curr_best_set, curr_set);
  }
}
