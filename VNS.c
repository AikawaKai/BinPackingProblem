#include <string.h>
#include <math.h>
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

  if((slack_i+value_i-value_j)>=0 && (slack_j+value_j-value_i)>=0)
  {
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

void shakingSolution(dataset_t *d_s, sol_t *starting_sol, node_t *Z, int k_curr)
{
  char moves[50] = "tests/";
  strcat(moves, d_s->name);
  strcat(moves, "moves.txt");
  FILE *filepointer;
  filepointer = fopen(moves, "a");
  hashset_t items_set = hashset_create(d_s->bin_size);
  int k=0;
  int size_dataset = d_s->n;
  int num_bin = starting_sol->n;
  bin_t *bins = starting_sol->bins;
  int i = random_at_most(size_dataset-1);
  //fprintf(filepointer, "\nk_curr: %d\n", k_curr);
  while(k<k_curr && (int)hashset_num_items(items_set)<d_s->n)
  {
    int num_swap, num_transf;
    num_swap = 0;
    num_transf = 0;
    node_t *curr_node = &Z[i];
    swap_t *list_swaps = calloc(size_dataset, sizeof(swap_t));
    transfer_t *list_transfers = calloc(size_dataset, sizeof(swap_t));
    // fill transfer moves array
    for(int j=0; j<curr_node->id; j++)
    {
      fillArrayTransferWithMoves(&num_transf, curr_node, list_transfers, &bins[j], j);
    }
    for(int j=curr_node->id+1; j<num_bin; j++)
    {
      fillArrayTransferWithMoves(&num_transf, curr_node, list_transfers, &bins[j], j);
    }
    // fill swap moves array
    for(int j=size_dataset-1; j>i; j--)
    {
      if (curr_node->val != Z[j].val && curr_node->id != Z[j].id && !hashset_is_member(items_set, &Z[j]))
      {
        fillArraySwapWithMoves(&num_swap, curr_node, &Z[j], list_swaps, bins);
      }
    }
    if(num_transf+num_swap>0)
    {
      int index_move = random_at_most(num_transf+num_swap-1);
      if(index_move<num_transf)
      {
        //fprintf(filepointer, "\n\n[move performed]\n");
        //print_to_file_transfer_move(&list_transfers[index_move], filepointer);
        //fprintf(filepointer, "[+-+-+-+-+-+-+-+]\n\n");
        performTransfMove(&list_transfers[index_move], bins);
        // perform rand transf move
      }
      else
      {
        //fprintf(filepointer, "\n\n[move performed]\n");
        //print_to_file_swap_move(&list_swaps[index_move-num_transf], filepointer);
        //fprintf(filepointer, "[+-+-+-+-+-+-+-+] \n");
        performSwapMove(&list_swaps[index_move-num_transf], bins);
        for(int g=0; g<starting_sol->n;g++)
        {
          bin_t bin = starting_sol->bins[g];
          if(bin.slack<0)
          {
            print_bin(&bin);
            exit(-1);
          }
        }
        // perform rand swap move
      }
      hashset_add(items_set, curr_node);
      k++;
    }
    i = random_at_most(size_dataset-1);
    curr_node = &Z[i];
    while(hashset_is_member(items_set, &Z[i]))
    {
      i = random_at_most(size_dataset-1);
      curr_node = &Z[i];
    }
    free(list_transfers);
    free(list_swaps);
  }
  hashset_destroy(items_set);
  fclose(filepointer);
}

int getZbinNotFullFromSolution(node_t *items,  sol_t *starting_sol, int *bins_not_full, int *num_bin)
{
  bin_t *bins = starting_sol->bins;
  int num_el=0;
  for(int i=0;i<starting_sol->n;i++)
  {
    if(bins[i].slack!=0)
    {
      bins_not_full[*num_bin] = i;
      *num_bin = *num_bin + 1;
      for(int j=0;j<bins[i].n;j++)
      {
        items[num_el].id = i;
        items[num_el].val = bins[i].items[j];
        items[num_el].item_index_bin = j;
        num_el++;
      }
    }
  }
  sort_list(items, num_el);
  return num_el;
}

float getAndPerformBestMove(bin_t *bins, node_t *Z, int num_el, int *bins_not_full, int num_bin_not_full)
{
  transfer_t *transf = calloc(1, sizeof(transfer_t));
  transfer_t *best_tr = NULL;
  float best_transf = 0.0;
  for(int i=0;i<num_bin_not_full;i++)
  {
    bin_t *curr_bin = &bins[bins_not_full[i]];
    float sum_bin_dest = curr_bin->sum;
    for(int j=num_el-1;j>=0;j--)
    {
      node_t *curr_node = &Z[j];
      if(curr_node->val> curr_bin->slack)
      {
        break;
      }
      if(curr_node->id!=bins_not_full[i] && curr_node->val<=curr_bin->slack)
      {
        float sum_bin_source = bins[Z[j].id].sum;
        float temp_val = pow((sum_bin_dest + Z[j].val), 2) + pow((sum_bin_source - Z[j].val), 2) - pow(sum_bin_source, 2) - pow(sum_bin_dest, 2);
        if(temp_val>best_transf && temp_val>0)
        {
          transf->item1 = curr_node;
          transf->index_bin = bins_not_full[i];
          best_tr = transf;
          best_transf = temp_val;
        }
      }
    }
  }

  // best swap search
  swap_t *swap = calloc(1, sizeof(swap_t));
  swap_t *best_s = NULL;
  float best_swap = 0.0;
  for(int q=num_el; q>=0;q--)
  {
    node_t *curr_node = &Z[q];
    bin_t *curr_bin = &bins[curr_node->id];
    float curr_sum = curr_bin->sum;
    float curr_slack = curr_bin->slack;
    int r = q;
    while(Z[r].val == Z[q].val && r>0)
    {
      r--;
    }
    for(int new_r = r; new_r>=0; new_r--)
    {
      node_t *curr_node_r = &Z[new_r];
      bin_t *curr_bin_r = &bins[curr_node_r->id];
      float curr_sum_r = curr_bin_r->sum;
      if(curr_node_r->val>(curr_node->val + curr_slack))
      {
        break;
      }
      if(curr_node->id != curr_node_r->id)
      {
        float curr_sum_r_update = curr_sum_r - curr_node_r->val + curr_node->val;
        float curr_sum_update = curr_sum - curr_node->val + curr_node_r->val;
        float temp = pow(curr_sum_update, 2) + pow(curr_sum_r_update, 2) - pow(curr_sum_r, 2) - pow(curr_sum, 2);
        if(temp>best_swap)
        {
          swap->item1 = curr_node;
          swap->item2 = curr_node_r;
          best_s = swap;
          best_swap = temp;
        }
      }
    }
  }
  if(best_swap>best_transf)
  {
    performSwapMove(best_s, bins);
    //printf("swap move: %f\n",best_swap);
    return best_swap;
  }
  else if(best_tr != NULL)
  {
    performTransfMove(best_tr, bins);
    //printf("transf move: %f\n",best_transf);
  }
  return best_transf;
}

void localSearch(dataset_t *d_s, sol_t *curr_sol)
{
  float objectiveF = 0.0;
  int *bins_not_full = calloc(d_s->n, sizeof(int));
  int num_bin_not_full = 0;
  float best_move = 0.0;
  bin_t *bins = curr_sol->bins;
  for(int i=0; i<curr_sol->n;i++)
  {
    objectiveF = objectiveF + pow(bins[i].sum, 2);
  }
  node_t *Z = (node_t *)calloc(d_s->n, sizeof(node_t));
  //printf("Before objectiveF: %f\n", objectiveF);
  /*
  do
  {
    int num_el = getZbinNotFullFromSolution(Z, curr_sol, bins_not_full, &num_bin_not_full);
    best_move = getAndPerformBestMove(bins, Z, num_el, bins_not_full, num_bin_not_full);
    //printf("best move %f\n", best_move);
    float newObjectiveF = 0.0;
    for(int i=0; i<curr_sol->n;i++)
    {
      newObjectiveF = newObjectiveF + (bins[i].sum * bins[i].sum);
    }
    //printf("After transf move: %f\n", newObjectiveF);
    printf("Coherent value: %f == %f -> %d \n", newObjectiveF - best_move, objectiveF, (newObjectiveF - best_move)==objectiveF);
    objectiveF = newObjectiveF;
    num_bin_not_full = 0;
    num_el = 0;
  }while(best_move>0.0);
  */
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
  sol_t *curr_sol = calloc(1, sizeof(sol_t));
  sol_t *best_sol = calloc(1, sizeof(sol_t));
  sol_t *temp_sol;

  initialize_solution(curr_sol, d_s->bin_size, d_s->n, starting_sol->max_num_el);
  copy_solution(starting_sol, curr_sol);
  initialize_solution(best_sol, d_s->bin_size, d_s->n, starting_sol->max_num_el);
  copy_solution(starting_sol, best_sol);
  node_t *Z = getZFromSolution(d_s, curr_sol);
  int k=1;
  sol_t *step;
  while(k<k_max)
  {
    temp_sol = calloc(1, sizeof(sol_t));
    initialize_solution(temp_sol, d_s->bin_size, d_s->n, starting_sol->max_num_el);
    copy_solution(curr_sol, temp_sol);
    shakingSolution(d_s, curr_sol, Z, k);
    localSearch(d_s, curr_sol);
    if(curr_sol->n > best_sol->n)
    {
      free_solution(best_sol);
      best_sol = calloc(1, sizeof(sol_t));
      initialize_solution(best_sol, d_s->bin_size, d_s->n, starting_sol->max_num_el);
      copy_solution(best_sol, curr_sol);
      Z = getZFromSolution(d_s, curr_sol);
      k=1;
      free_solution(temp_sol);
    }
    else
    {
      free_solution(curr_sol);
      curr_sol = calloc(1, sizeof(sol_t));
      initialize_solution(curr_sol, d_s->bin_size, d_s->n, starting_sol->max_num_el);
      copy_solution(temp_sol, curr_sol);
      free_solution(temp_sol);
      k++;
    }
    k++; // momentaneamente
  }
}
