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
  int size_bin = 0;
  int bin_n;
  int prec = 0;
  int threshold = 0;
  printf("--------\n");
  for(int i = 0; i<m_bins; i++)
  {
    bin_n = bins[i].n;
    threshold = size_bin + threshold;
    for(int j=prec; j<threshold;j++)
    {
      temp->id = i;
      temp->val = bins[i].items[j];
      temp->item_index_bin = j;
      items[i+j+size_bin-1] = *temp;
      printf("%d\n", i+j+size_bin);
      temp = calloc(1, sizeof(node_t));
    }
    prec = threshold;
    size_bin = bin_n;
  }
  //sort_not_linked_list(items, num_items);
  printf("###########\n");
  for(int i=0; i<num_items;i++)
  {
    printf("%f\n", items[i].val);
  }
}
