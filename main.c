#include <stdio.h>
#include "firstfit.h"

int main(int argc, char *argv[]){
  dataset_t test1;
  sol_t s1;
  char *filename = argv[1];
  load_dataset(filename, &test1); // carica il caso di test nella struct dataset
  initialize_solution(&s1, test1.bin_size, 51);
  firstfit(&test1, &s1);

  /*
  bin b;
  initialize_bin(&b, test1.bin_size);
  printf("bin size: %d, bin elements: %d, current slack: %d\n",b.size, b.n, b.slack);
  add_item_to_bin(&b, 20);
  printf("bin size: %d, bin elements: %d, current slack: %d\n",b.size, b.n, b.slack);
  add_item_to_bin(&b, 30);
  printf("bin size: %d, bin elements: %d, current slack: %d\n",b.size, b.n, b.slack);
  for (int i=0; i< b.n; i++)
  {
    printf("curr element in: %d\n", b.items[i]);
  }
  free_bin(&b);*/
  free_dataset(&test1); // libero lo spazio occupato dal dataset
  free_solution(&s1);
}
