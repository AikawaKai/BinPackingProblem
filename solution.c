#include "solution.h"
#include <stdlib.h>
#include <stdio.h>

void initialize_bin(bin *b, int size)
{
  b->n = 0;
  b->sum = 0;
  b->size = size;
  b->slack = size;
}

void add_item_to_bin(bin *b, int item)
{
  b->n++;
  b->sum = b->sum + item;
  b->slack = b->slack - item;
  printf("%d %d %d", b->n, b->sum, b->slack);
  int *new_items = realloc(b->items, b->n * sizeof(int));
  if (new_items!=NULL)
  {
    exit(-1);
  }
  else
  {
    new_items[b->n-1] = item;
    b->items = new_items;
  }
}
