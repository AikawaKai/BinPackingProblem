#include "solution.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// inizializza il bin
void initialize_bin(bin_t *b, float size, int num_items)
{
  b->items = (float *) calloc(num_items, sizeof(float));
  b->n = 0;
  b->sum = 0;
  b->size = size;
  b->slack = size;
}

// copia il contenuto di bin source in bin dest
void copy_bin(bin_t *source, bin_t *dest)
{
  for(int i=0; i<source->n; i++)
  {
    add_item_to_bin(dest, source->items[i]);
  }
}

// libera l'area di memoria occupata dal bin passato come parametro
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

// aggiunge un oggetto al bin
void add_item_to_bin(bin_t *b, float item)
{
  b->n = b->n + 1;
  b->sum = b->sum + item;
  b->slack = b->slack - item;
  b->items[b->n-1] = item;
}

// rimuove un oggetto dal bin (passato come parametro)
void removeItemFromBin(bin_t *bin, float value_to_remove)
{
  int index;
  int bool_val = 0;
  for(int i=0; i<bin->n;i++)
  {
    if(bin->items[i]==value_to_remove)
    {
      bool_val = 1;
      index = i;
      break;
    }
  }
  if(bool_val == 0)
  {
    printf("float to remove: %f\n", value_to_remove);
    print_bin(bin);
    exit(-1);
  }
  float value = bin->items[index];
  if(((bin->n)-1)>index)
  {
    for(int j=index;j<bin->n-1;j++)
    {
      bin->items[j]=bin->items[j+1];
    }
  }
  bin->items[bin->n-1] = 0.0;
  bin->n = bin->n-1;
  bin->slack = bin->slack + value;
  bin->sum = bin->sum - value;
}

// controlla se il bin contiene l'oggetto passato come parametro
int check_if_item_in_bin(bin_t *b, float item)
{
  for(int i = 0; i<b->n;i++)
  {
    if(item==b->items[i])
    {
      return 1;
    }
  }
  return 0;
}

// restituisce lo slack del bin
int get_bin_slack(bin_t *b)
{
  return b->slack;
}

// aggiunge un oggetto al bin se c'è abbastanza spazio
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

// inizializza la soluzione
void initialize_solution(sol_t *s, float b_size, int num_items, int max_num_el)
{
  s->n = 0;
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

// copia il contenuto di una soluzione in un'altra variabile result
void copy_solution(sol_t *sol, sol_t *result)
{
  result->n = sol->n;
  result->bin_size = sol->bin_size;
  result->max_num_el = sol->max_num_el;
  for(int i=0; i<sol->n;i++)
  {
    initialize_bin(&(result->bins[i]), sol->bin_size, sol->max_num_el);
    copy_bin(&(sol->bins[i]), &(result->bins[i]));
  }
}

// aggiunge un nuovo bin alla soluzione
void add_new_bin(sol_t *s)
{
  s->n = s->n+1;
  bin_t n_b;
  initialize_bin(&n_b, s->bin_size, s->max_num_el);
  s->bins[s->n-1]=n_b;
}

// cancella un bin dalla soluzione
void delete_bin_from_solution(sol_t *solution, int index_bin)
{
  if(index_bin == solution->n-1)
  {
    solution->n = solution->n-1;
    return;
  }
  for(int i=index_bin; i<solution->n-1; i++)
  {
    solution->bins[i] = solution->bins[i+1];
  }
  solution->n = solution->n-1;
}

// libera l'area di memoria occupata dalla soluzione passata come parametro
void free_solution(sol_t *s)
{
  for(int i=0; i<s->n; i++)
  {
    free_bin(&(s->bins[i]));
  }
  free(s->bins);
  s->bins = NULL;
  s->n = 0;
}

// stampa nello stdout il bin
void print_bin(bin_t *bin)
{
  printf("------\nItems:\n");
  for(int i=0;i<bin->n;i++)
  {
    printf("%f\n",bin->items[i]);
  }
  printf("slack: %f\n", bin->slack);
}

// stampa nello stdout la soluzione
void print_solution(sol_t *s)
{
  for(int i=0; i<s->n;i++)
  {
    printf("\nCURRENT BIN:%d\n", i);
    print_bin(&(s->bins[i]));
  }
}

// controlla che la soluzione sia coerente\corretta rispetto al dataset e ai vincoli
void check_solution(dataset_t *d_s, sol_t *s)
{
  bin_t *bins = s->bins;
  float *items_sol = calloc(d_s->n*2, sizeof(float));
  int pos = 0;
  float curr_size = 0.0;
  for(int i=0; i<s->n;i++)
  {
    for(int j=0;j<bins[i].n;j++)
    {
      items_sol[pos] = bins[i].items[j];
      pos = pos + 1;
      curr_size = curr_size+bins[i].items[j];
    }
    if (curr_size-d_s->bin_size>0.0001)
    {
      printf("Incoherent Solution\n");
      printf("Bin size: %f Filled: %f\n", d_s->bin_size, curr_size);
      exit(-1);
    }
    curr_size = 0.0;
  }
  qsort(items_sol, pos, sizeof(float), compare_function);
  if(pos!=d_s->n)
  {
    printf("Incoherent Solution\n");
    printf("size 1 %d size 2 %d\n", d_s->n, pos);
    exit(-1);
  }
  float *items = d_s->items;
  qsort(items, pos, sizeof(float), compare_function);
  for(int i=0; i<pos; i++)
  {
    if(items[i]!=items_sol[i])
    {
      printf("Incoherent Solution\n");
      printf("first: %f second: %f -----------\n",items[i], items_sol[i]);
      exit(-1);
    }
  }
  free(items_sol);
}
