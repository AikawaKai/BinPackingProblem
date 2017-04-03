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
  add_item_to_bin(&bins[bin_dest], item1->val);
  item1->id = bin_dest;
  item1->item_index_bin = bins[bin_dest].n - 1;
}
void performSwapMove(swap_t *transf, bin_t *bins)
{
  node_t *item1 = transf->item1;
  node_t *item2 = transf->item2;
  int bin_from = item1->id;
  int bin_dest = item2->id;
  float val1 = item1->val;
  float val2 = item2->val;
  int index_in_bin_1 = item1->item_index_bin;
  int index_in_bin_2 = item2->item_index_bin;
  removeItemFromBin(&bins[bin_from], index_in_bin_1);
  removeItemFromBin(&bins[bin_dest], index_in_bin_2);
  add_item_to_bin(&bins[bin_from], val2);
  add_item_to_bin(&bins[bin_dest], val1);
  item1->id = bin_dest;
  item2->id = bin_from;
  item1->val = val2;
  item2->val = val1;
  item1->item_index_bin = bins[bin_dest].n-1;
  item2->item_index_bin = bins[bin_from].n-1;
}

void print_transfer_move(transfer_t *move)
{
  printf("------------\n");
  printf("++TRANSFER++\n");
  printf("Item1: ");
  print_list(move->item1);
  printf("Bin from: %d\n", move->item1->id);
  printf("Bin dest: %d\n", move->index_bin);
}

void print_to_file_transfer_move(transfer_t *move, FILE *filepointer)
{
  node_t *item1 = move->item1;
  fprintf(filepointer, "++++TRANSFER++++\n");
  fprintf(filepointer, "Item1: %f\n", item1->val);
  fprintf(filepointer, "bin: %d\n",item1->id);
  fprintf(filepointer, "bin_dest: %d\n", move->index_bin);
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
