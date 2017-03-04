#include "firstfit.h"
#include <stdio.h>

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
        printf("bin j: %d, added item %d: %d\n",j, i, ds->items[i]);
        printf("bin slack: %d\n", (sol->bins[j]).slack );
        fixed = TRUE;
        break;
      }
    }
    if(fixed==FALSE && j==(sol->n))
    {
      add_new_bin(sol);
      add_item_to_bin(&(sol->bins[(sol->n)-1]), ds->items[i]);
      printf("bin j: %d, added item %d: %d\n",j, i, ds->items[i]);
      printf("bin slack: %d\n", (sol->bins[j]).slack );
    }
  }
  printf("Solution: %d\n", sol->n);
}
