#include "solution.h"
#include <stdlib.h>
#include <stdio.h>

void initialize_bin(bin *b, int size)
{
  b->items = malloc(0 * sizeof (b->items));
  b->n = 0;
  b->sum = 0;
  b->size = size;
  b->slack = size;
}

void free_bin(bin *b)
{
  // libero lo spazio occupato dal bin
  free(b->items);
  b->n = 0;
  b->sum = 0;
  b->size = 0;
  b->slack = 0;
}

void add_item_to_bin(bin *b, int item)
{
  b->n++;
  b->sum = b->sum + item;
  b->slack = b->slack - item;
  int *new_items = realloc(b->items, b->n * sizeof(*new_items));
  if (new_items==NULL)
  {
    printf("REALLOC FAILED add_item_to_bin\n");
    exit(-1);
  }
  else
  {
    new_items[b->n-1] = item;
    b->items = new_items;
  }
}
