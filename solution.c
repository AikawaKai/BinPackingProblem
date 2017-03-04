#include "solution.h"
#include <stdlib.h>
#include <stdio.h>

void initialize_bin(bin_t *b, int size)
{
  b->items = malloc(0 * sizeof (b->items));
  b->n = 0;
  b->sum = 0;
  b->size = size;
  b->slack = size;
}

void free_bin(bin_t *b)
{
  // libero lo spazio occupato dal bin
  free(b->items);
  b->items = NULL;
  b->n = 0;
  b->sum = 0;
  b->size = 0;
  b->slack = 0;
}

void add_item_to_bin(bin_t *b, int item)
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
  new_items[b->n-1] = item;
  b->items = new_items;
}

int get_bin_slack(bin_t *b)
{
  return b->slack;
}

bool add_item_to_bin_if_fits(bin_t *b, int item)
{
  if (get_bin_slack(b) - item >= 0)
  {
    add_item_to_bin(b, item);
    return TRUE;
  }
  return FALSE;
}

void initialize_solution(sol_t *s, int b_size)
{
  s->n = 1;
  s->bins = malloc(1 * sizeof(s->bins));
  if(s->bins == NULL)
  {
    printf("MALLOC FAILED initialize_solution\n");
    exit(-1);
  }
  bin_t b1;
  initialize_bin(&b1, b_size);
  s->bins[0] = b1;
}

void free_solution(sol_t *s)
{
  free(s->bins);
  s->bins = NULL;
  s->n = 0;
  printf("free(solution) ok\n");
}
