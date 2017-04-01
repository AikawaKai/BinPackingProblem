#include "data.h"
#include "solution.h"
#include "linkedList.h"
#include "move.h"
#include "VNS.h"
#include "hashset.h"

int fillArrayTransferWithMoves(int *num_transf, node_t *curr_node, transfer_t *list_transfers, bin_t *bin, int j)
{
  transfer_t *move_tr;
  float val = curr_node->val;
  float slack = bin->slack;
  if ((bin->slack - val)>=0)
  {
    print_bin(bin);
    move_tr = calloc(1, sizeof(transfer_t));
    move_tr->item1 = curr_node;
    move_tr->index_bin = j;
    list_transfers[*num_transf] = *move_tr;
    *num_transf = *num_transf + 1;
    return 1;
  }
  return 0;
}

int fillArraySwapWithMoves(int *num_swap, node_t *curr_node, node_t *curr_node_j, swap_t *list_swaps, bin_t *bins)
{
  swap_t *move_swap;
  int bin_index_i = curr_node->id;
  int bin_index_j = curr_node_j->id;
  float slack_i = bins[bin_index_i].slack;
  float slack_j = bins[bin_index_j].slack;
  float value_i = curr_node->val;
  float value_j = curr_node_j->val;

  if(slack_i+value_i-value_j>=0 && slack_j+value_j-value_i>=0)
  {
    printf("[---ok swap---]\n");
    print_bin(&bins[bin_index_i]);
    print_list(curr_node);
    print_bin(&bins[bin_index_j]);
    print_list(curr_node_j);
    move_swap = calloc(1, sizeof(swap_t));
    move_swap->item1 = curr_node;
    move_swap->item2 = curr_node_j;
    list_swaps[*num_swap] = *move_swap;
    *num_swap = *num_swap + 1;
    return 1;
  }
  return 0;
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
  hashset_t items_set = hashset_create(d_s->bin_size);
  int size_dataset = d_s->n;
  int num_bin = starting_sol->n;
  bin_t *bins = starting_sol->bins;
  while(k_curr>0)
  {
    int i = random_at_most(size_dataset-1);
    int num_swap, num_transf;
    num_swap = 0;
    num_transf = 0;

    node_t curr_node = Z[i];
    hashset_add(items_set, &curr_node);
    swap_t *list_swaps = calloc(size_dataset, sizeof(swap_t));
    transfer_t *list_transfers = calloc(size_dataset, sizeof(swap_t));

    // fill transfer moves array
    for(int j=0; j<curr_node.id; j++)
    {
      fillArrayTransferWithMoves(&num_transf, &curr_node, list_transfers, &bins[j], j);
    }
    for(int j=curr_node.id+1; j<num_bin; j++)
    {
      fillArrayTransferWithMoves(&num_transf, &curr_node, list_transfers, &bins[j], j);
    }

    // fill swap moves array
    for(int j=size_dataset-1; j>i; j--)
    {
      if (curr_node.val != Z[j].val)
      {
        fillArraySwapWithMoves(&num_swap, &curr_node, &Z[j], list_swaps, bins);
      }
    }
    printf("num swap: %d, num transf: %d\n", num_swap, num_transf);
    exit(-1);
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
  sol_t *curr_sol;
  sol_t *best_sol;
  int k=1;
  /*
  for(int i=0; i<starting_sol->n;i++)
  {
    print_bin(&(starting_sol->bins[i]));
  }*/
  while(k<k_max)
  {
    curr_sol = shakingSolution(d_s, starting_sol, Z, k);
    exit(-1);
  }
}
