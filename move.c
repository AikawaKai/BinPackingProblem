#include <stdio.h>
#include "linkedList.h"
#include "move.h"

void performTransfMove(transfer_t *transf)
{
  node_t *item1 = transf->item1;
}
void performSwapMove(swap_t *transf)
{
  node_t *item1 = transf->item1;
  node_t *item2 = transf->item2;
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
