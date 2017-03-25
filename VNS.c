#include "data.h"
#include "solution.h"
#include "linkedList.h"
#include "move.h"
#include "VNS.h"
#include "hashset.h"

void fillArrayWithMoves(int *num_swap, int *num_transf, node_t *curr_node, node_t *Z_j, swap_t *list_swap, transfer_t *list_transfers, int switch_val)
{
  transfer_t *move_tr;
  swap_t *move_swap;
  switch (switch_val) {
    case 0: //transfer
      move_tr = calloc(1, sizeof(transfer_t));
      move_tr->index_bin = Z_j->id;
      move_tr->item1 = curr_node;
      list_transfers[*num_transf] = *move_tr;
      *num_transf = *num_transf + 1;
      break;
    case 1: //swap
      move_swap = calloc(1, sizeof(swap_t));
      move_swap->item1 = curr_node;
      move_swap->item2 = Z_j;
      list_swap[*num_swap] = *move_swap;
      *num_swap = *num_swap + 1;
      break;
    case 2: //transfer and swap
      move_tr = calloc(1, sizeof(transfer_t));
      move_tr->index_bin = Z_j->id;
      move_tr->item1 = curr_node;
      list_transfers[*num_transf] = *move_tr;
      *num_transf++;
      move_swap = calloc(1, sizeof(swap_t));
      move_swap->item1 = curr_node;
      move_swap->item2 = Z_j;
      list_swap[*num_swap] = *move_swap;
      *num_swap = *num_swap + 1;
      break;
    default:
      //printf("move not ammitted: %d \n", switch_val);
      return;
  }
}

int operationPermitted(node_t *curr_node, node_t *z_val, bin_t *bins)
{
  //swap
  int swap = 0;
  int transf = 0;
  float val1 = curr_node->val;
  float val2 = z_val->val;
  int bin_index_1 = curr_node->id;
  int bin_index_2 = z_val->id;
  bin_t bin1 = bins[bin_index_1];
  bin_t bin2 = bins[bin_index_2];
  //printf("\nItem_i: %f, Itemd Z[j]: %f\n",val1, val2);
  //print_bin(&bin1);
  //print_bin(&bin2);
  float slack1 = bin1.slack;
  float slack2 = bin2.slack;
  float diff1 = slack1+val1-val2;
  float diff2 = slack2+val2-val1;
  if(diff1>=0)
  {
    if(diff2>=0)
    {
      swap++;
    }
  }
  if(slack2>=val1)
  {
    return transf++;
  }
  if(swap && transf)
  {
    return 2;
  }
  if(swap && !transf)
  {
    return 1;
  }
  if(!swap && transf)
  {
    return 0;
  }
  return -1;
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
  hashset_t items_set = hashset_create(d_s->bin_size);
  bin_t *bins = starting_sol->bins;
  node_t curr_node = Z[i];
  hashset_add(items_set, &curr_node);
  swap_t *list_swaps = calloc(d_s->n, sizeof(swap_t));
  transfer_t *list_transfers = calloc(d_s->n, sizeof(swap_t));
  for(int j=0; j<size_dataset;j++)
  {
    if (!hashset_is_member(items_set, &Z[j]))
    {
      //printf("##########\n");
      switch_val = operationPermitted(&curr_node, &Z[j], bins);
      fillArrayWithMoves(&num_swap, &num_transf, &curr_node, &Z[j], list_swaps, list_transfers, switch_val);
      if(num_swap>0 || num_transf>0)
      {
        printf("num_swap:%d num_transf:%d \n", num_swap, num_transf);
      }
      //printf("operation permitted: %d\n", switch_val);
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
