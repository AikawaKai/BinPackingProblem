#include <stdio.h>
#include "linkedList.h"
#include "move.h"

void print_transfer_move(transfer_t *move)
{
  printf("-----------\n");
  print_list(move->item1);
  printf("Bin: %d\n", move->index_bin);
}
