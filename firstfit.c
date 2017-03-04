#include "firstfit.h"
#include <stdio.h>

void firstfit(dataset_t *ds, sol_t *sol)
{
  bin_t curr_bin;
  bool fixed = FALSE;
  int j;
  for(int i=0; i<ds->n; i++)
  {
    fixed = FALSE;
    for(j=0; j<sol->n; j++)
    {
      curr_bin = sol->bins[j];
      if(add_item_to_bin_if_fits(&curr_bin, ds->items[i]))
      {
        printf("Fitto l'oggetto %d nel bin %d\n",ds->items[i], j);
        fixed = TRUE;
        break;
      }
    }
    if(!fixed && j==sol->n-1)
    {
      printf("entro qui\n");
      add_new_bin(sol);
      curr_bin = sol->bins[sol->n];
      add_item_to_bin(&curr_bin, ds->items[i]);
    }
  }
  printf("Solution: %d\n", sol->n);
}
