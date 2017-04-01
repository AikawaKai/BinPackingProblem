#include <stdio.h>
#include "solution.h"
#include "linkedList.h"
#include "move.h"

void performTransfMove(transfer_t *transf, bin_t *bins)
{
  node_t *item1 = transf->item1;
  int bin_from = item1->id;
  int bin_dest = transf->index_bin;
  int index_in_bin_1 = item1->item_index_bin;
  removeItemFromBin(&bins[bin_from], index_in_bin_1);
  //printf("bin from:%d bin dest:%d\n", bin_from, bin_dest);
}
void performSwapMove(swap_t *transf, bin_t *bins)
{
  node_t *item1 = transf->item1;
  node_t *item2 = transf->item2;
  int index_in_bin_1 = item1->item_index_bin;
  int index_in_bin_2 = item2->item_index_bin;
  removeItemFromBin(&bins[item1->id], index_in_bin_1);
  removeItemFromBin(&bins[item2->id], index_in_bin_2);
}

void print_transfer_move(transfer_t *move)
{
  printf("------------\n");
  printf("++TRANSFER++\n");
  printf("Item1: ");
  print_list(move->item1);
  printf("Bin: %d\n", move->index_bin);
}

void print_swap_move(swap_t *move)
{
  printf("------------\n");
  printf("++++SWAP++++\n");
  printf("Item1: ");
  print_list(move->item1);
  printf("\nItem2: ");
  print_list(move->item2);
  printf("\n");
}
