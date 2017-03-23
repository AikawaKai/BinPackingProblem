#include "data.h"
#include "solution.h"
#include "linkedList.h"
#include "VNS.h"

sol_t * shakingSolution(sol_t *starting_sol, node_t *Z, int k_curr)
{

}

node_t *getZFromSolution(dataset_t *d_s, sol_t *starting_sol)
{
  int num_items = d_s->n;
  node_t *items = (node_t *)calloc(num_items, sizeof(node_t));
  bin_t *bins = starting_sol->bins;
  node_t *temp = calloc(1, sizeof(node_t));
  int m_bins = starting_sol->n;
  int bin_n = 0;
  int prec = 0;
  int threshold = 0;
  printf("--------\n");
  for(int i = 0; i<m_bins; i++)
  {
    prec = threshold;
    threshold = bins[i].n + threshold;
    int k = 0;
    for(int j=prec; j<threshold;j++)
    {
      temp->id = i;
      temp->val = bins[i].items[k];
      temp->item_index_bin = k;
      items[j] = *temp;
      temp = calloc(1, sizeof(node_t));
      k++;
    }
    prec = threshold;
    bin_n = bins[i].n;
  }
  sort_and_link_list(items, num_items);
  return &items[0];
}

void VNSmethod(dataset_t *d_s, sol_t *starting_sol, int k_max)
{
  node_t *Z_head = getZFromSolution(d_s, starting_sol);
  print_list(Z_head);
  sol_t *curr_sol;
  int k=1;
  while(k<k_max)
  {
    curr_sol = shakingSolution(starting_sol, Z_head, k);
  }
}
