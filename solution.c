#include "solution.h"
#include <stdlib.h>
#include <stdio.h>

void initialize_bin(bin_t *b, float size, int num_items)
{
  b->items = (float *) calloc(num_items, sizeof (float));
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

void add_item_to_bin(bin_t *b, float item)
{
  b->n = b->n + 1;
  b->sum = b->sum + item;
  b->slack = b->slack - item;
  b->items[b->n-1] = item;
}

int get_bin_slack(bin_t *b)
{
  return b->slack;
}

bool add_item_to_bin_if_fits(bin_t *b, float item)
{
  float partial = get_bin_slack(b) - item;
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

void initialize_solution(sol_t *s, float b_size, int num_items, int max_num_el)
{
  s->n = 1;
  s->bin_size = b_size;
  s->max_num_el = max_num_el;
  s->bins = (bin_t *)calloc(num_items, sizeof(bin_t));
  if(s->bins == NULL)
  {
    printf("MALLOC FAILED initialize_solution\n");
    exit(-1);
  }
  bin_t b1;
  initialize_bin(&b1, b_size, s->max_num_el);
  s->bins[0] = b1;
}

void add_new_bin(sol_t *s)
{
  s->n = s->n+1;
  bin_t n_b;
  initialize_bin(&n_b, s->bin_size, s->max_num_el);
  s->bins[s->n-1]=n_b;
}

void free_solution(sol_t *s)
{
  for(int i=0; i<s->n; i++)
  {
    free_bin(&(s->bins[i]));
  }
  free(s->bins);
  s->bins = NULL;
  s->n = 0;
  //printf("free(solution) ok\n");
}

void print_bin(bin_t *bin)
{
  FILE *fp = fopen("check.txt", "a");
  for(int i=0;i<bin->n;i++)
  {
    //printf("%d\n",bin->items[i]);
    fprintf(fp, " %f ",bin->items[i] );
  }
  fprintf(fp, " %f \n",bin->slack);
  fclose(fp);
  //printf("slack: %d\n", bin->slack);
}

void print_solution(sol_t *s)
{
  char results[200];
  //printf("BIN SIZE: %d\n",s->bin_size);

  for(int i=0; i<s->n;i++)
  {
    //printf("-------\n");
    print_bin(&(s->bins[i]));
    //printf("-------\n");
  }
}
