#include "firstfit.h"
#include <stdio.h>

void firstfit(dataset_t *ds, sol_t *sol)
{
  bin_t curr_bin;
  for(int i=0; i<ds->n; i++)
  {
    for(int j=0; j<sol->n; j++)
    {
      curr_bin = sol->bins[j];
      if(add_item_to_bin_if_fits(&curr_bin, ds->items[i]))
      {
        break;
      }
    }
  }
}
