#include <stdio.h>
#include "data.h"
#include "solution.h"

int main(int argc, char *argv[]){
  dataset test1;
  char *filename = argv[1];
  load_dataset(filename, &test1); // carica il caso di test nella struct dataset


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
}
