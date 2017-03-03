#include <stdio.h>
#include "data.h"

int main(int argc, char *argv[]){
  dataset test1;
  char *filename = argv[1];
  load_dataset(filename, &test1); // carica il caso di test nella struct dataset
}
