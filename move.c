#include <stdio.h>
#include "solution.h"
#include "linkedList.h"
#include "move.h"

// esegue la mossa di trasferimento
void performTransfMove(transfer_t *transf, sol_t *solution , bin_t *bins)
{
  node_t *item1 = transf->item1;
  int bin_from = item1->id;
  int bin_dest = transf->index_bin;
  removeItemFromBin(&bins[bin_from], item1->val);
  add_item_to_bin(&bins[bin_dest], item1->val);
  item1->id = bin_dest;
  if(bins[bin_from].n==0)
  {
    delete_bin_from_solution(solution, bin_from);
  }
}

// esegue la mossa di scambio
void performSwapMove(swap_t *transf, bin_t *bins)
{

  node_t *item1 = transf->item1;
  node_t *item2 = transf->item2;
  int bin_from = item1->id;
  int bin_dest = item2->id;
  float val1 = item1->val;
  float val2 = item2->val;
  removeItemFromBin(&bins[bin_from], val1);
  removeItemFromBin(&bins[bin_dest], val2);
  add_item_to_bin(&bins[bin_from], val2);
  add_item_to_bin(&bins[bin_dest], val1);
  item1->id = bin_dest;
  item2->id = bin_from;
}

// stampa sullo stdout la mossa di trasferimento
void print_transfer_move(transfer_t *move)
{
  printf("------------\n");
  printf("++TRANSFER++\n");
  printf("Item1: ");
  print_list(move->item1);
  printf("Bin from: %d\n", move->item1->id);
  printf("Bin dest: %d\n", move->index_bin);
}

// stampa su file la mossa di trasferimento
void print_to_file_transfer_move(transfer_t *move, FILE *filepointer)
{
  node_t *item1 = move->item1;
  fprintf(filepointer, "++++TRANSFER++++\n");
  fprintf(filepointer, "Item1: %f\n", item1->val);
  fprintf(filepointer, "bin: %d\n",item1->id);
  fprintf(filepointer, "bin_dest: %d\n", move->index_bin);
}


// stampa su stdout la mossa di scambio
void print_swap_move(swap_t *move)
{
  printf("------------\n");
  printf("++++SWAP++++\n");
  printf("Item1: ");
  print_list(move->item1);
  printf("bin_1: %d\n",move->item1->id);
  printf("\nItem2: ");
  print_list(move->item2);
  printf("bin_2: %d\n",move->item2->id);
  printf("\n");
}

// stampa su file la mossa di scambio
void print_to_file_swap_move(swap_t *move, FILE *filepointer)
{
  node_t *item1 = move->item1;
  node_t *item2 = move->item2;
  fprintf(filepointer, "++++SWAP++++\n");
  fprintf(filepointer, "Item1: %f\n", item1->val);
  fprintf(filepointer, "bin: %d\n",item1->id);
  fprintf(filepointer, "Item2: %f\n", item2->val);
  fprintf(filepointer, "bin: %d\n",item2->id);
}
