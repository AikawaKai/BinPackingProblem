#include "data.h"
#include "solution.h"
#include "linkedList.h"
#include "move.h"
#include "VNS.h"
#include "hashset.h"

int operationPermitted(node_t *curr_node, node_t *z_val)
{

}

long random_at_most(long max)
{
  unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

  long x;
  do {
   x = random();
  }
  // This is carefully written not to overflow
  while (num_rand - defect <= (unsigned long)x);

  // Truncated division is intentional
  return x/bin_size;
}

sol_t * shakingSolution(dataset_t *d_s, sol_t *starting_sol, node_t *Z, int k_curr)
{
  int size_dataset = d_s->n;
  int switch_val;
  int rand_index = random_at_most(size_dataset-1);
  int num_swap, num_transf;
  num_swap = 0;
  num_transf = 0;
  int i = rand_index;
  int j = 0;
  hashset_t items_set = hashset_create(d_s->bin_size);
  node_t curr_node = Z[i];
  hashset_add(items_set, &curr_node);
  swap_t *list_swaps = calloc(1, sizeof(swap_t));
  transfer_t *list_transfers = calloc(1, sizeof(swap_t));
  while(k_curr>0)
   {
     for(int j=0; j<size_dataset;j++)
     {
       if (!hashset_is_member(items_set, &Z[j]))
       {
         switch_val = operationPermitted(&curr_node, &Z[j]);
         printf("operation permitted%d\n", switch_val);
       }
     }
   }
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
  sort_list(items, num_items);
  return items;
}

void VNSmethod(dataset_t *d_s, sol_t *starting_sol, int k_max)
{
  node_t *Z = getZFromSolution(d_s, starting_sol);
  // print_list(Z_head);
  sol_t *curr_sol;
  sol_t *best_sol;
  int k=1;
  while(k<k_max)
  {
    curr_sol = shakingSolution(d_s, starting_sol, Z, k);
  }
}
