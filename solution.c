#include "solution.h"
#include <stdlib.h>
#include <stdio.h>

void initialize_bin(bin_t *b, int size, int num_items)
{
  b->items = (int *)malloc(num_items * sizeof (int));
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
  printf("########################\n");
  printf("--- Bin prima ---\n");
  printf("Numero di el: %d\n", b->n);
  printf("Somma: %d\n", b->sum);
  printf("Slack: %d\n", b->slack);
  b->n++;
  b->sum = b->sum + item;
  b->slack = b->slack - item;
  b->items[b->n-1] = item;
  printf("+++ Bin Dopo +++\n");
  printf("Numero di el: %d\n", b->n);
  printf("Somma: %d\n", b->sum);
  printf("Slack: %d\n", b->slack);
  printf("########################\n");
}

int get_bin_slack(bin_t *b)
{
  return b->slack;
}

bool add_item_to_bin_if_fits(bin_t *b, int item)
{
  int partial = get_bin_slack(b) - item;
  if (partial >= 0)
  {
    add_item_to_bin(b, item);
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

void initialize_solution(sol_t *s, int b_size, int num_items)
{
  s->n = 1;
  s->bin_size = b_size;
  s->bins = (bin_t *)malloc(num_items * sizeof(bin_t));
  if(s->bins == NULL)
  {
    printf("MALLOC FAILED initialize_solution\n");
    exit(-1);
  }
  bin_t b1;
  initialize_bin(&b1, b_size, num_items);
  s->bins[0] = b1;
}

void add_new_bin(sol_t *s)
{
  s->n++;
  bin_t n_b;
  initialize_bin(&n_b, s->bin_size, s->n);
  printf("%d, %d, %d, %d\n",n_b.n, n_b.sum, n_b.size, n_b.slack);
  s->bins[s->n]=n_b;
}

void free_solution(sol_t *s)
{
  free(s->bins);
  s->bins = NULL;
  s->n = 0;
  printf("free(solution) ok\n");
}
