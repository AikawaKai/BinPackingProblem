#include <stdio.h>
#include "data.h"
#include "solution.h"

int main(int argc, char *argv[]){
  dataset test1;
  char *filename = argv[1];
  load_dataset(filename, &test1); // carica il caso di test nella struct dataset

  bin b;
  initialize_bin(&b, test1.bin_size);
  printf("bin size: %d, bin elements: %d\n",b.size, b.n);
  /*
  add_item_to_bin(&b, 20); */
}
