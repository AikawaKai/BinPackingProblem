#include "firstfit.h"
#include <stdio.h>


// metodo firstfit
void firstfit(dataset_t *ds, sol_t *sol)
{
  bool fixed = FALSE;
  int j;
  for(int i=0; i<ds->n; i++)
  {
    fixed = FALSE;
    for(j=0; j<sol->n; j++)
    {
      if(add_item_to_bin_if_fits(&(sol->bins[j]), ds->items[i]))
      {
        fixed = TRUE;
        break;
      }
    }
    if(fixed==FALSE && j==(sol->n))
    {
      add_new_bin(sol);
      add_item_to_bin(&(sol->bins[(sol->n)-1]), ds->items[i]);
    }
  }
}

// variante del firstfit con lista di oggetti ordinata in maniera decrescente
void firstfitdecreasing(dataset_t *ds, sol_t *sol)
{
  bool fixed = FALSE;
  int j;
  for(int i=0; i<ds->n; i++)
  {
    fixed = FALSE;
    for(j=0; j<sol->n; j++)
    {
      if(add_item_to_bin_if_fits(&(sol->bins[j]), ds->sorteditems[i]))
      {
        fixed = TRUE;
        break;
      }
    }
    if(fixed==FALSE && j==(sol->n))
    {
      add_new_bin(sol);
      add_item_to_bin(&(sol->bins[(sol->n)-1]), ds->sorteditems[i]);
    }
  }
}
