#include "data.h"
#include "solution.h"
#include "linkedList.h"
#include "VNS.h"

void VNSmethod(dataset_t *d_s, sol_t *starting_sol)
{
  int num_items = d_s->n;
  node_t *items = (node_t *)calloc(num_items, sizeof(node_t));
  bin_t *bins = starting_sol->bins;
  node_t *temp = calloc(1, sizeof(node_t));
  int m_bins = starting_sol->n;
  int bin_n = 0;
  for(int i = 0; i<m_bins; i++)
  {
    for(int j=0; j<bin_n;j++)
    {
      temp->id = i;
      temp->val = bins[i].items[j];
      temp->item_index_bin = j;
      items[j+bin_n] = *temp;
      temp = calloc(1, sizeof(node_t));
    }
    bin_n = bins[i].n;
  }
  //sort_not_linked_list(items, num_items);
  printf("###########\n");
  for(int i=0; i<num_items;i++)
  {
    printf("%f\n", items[i].val);
  }
}
