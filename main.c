#include <stdio.h>
#include "data.h"

int main(int argc, char *argv[]){
  dataset test1;
  char *filename = argv[1];
  load_dataset(filename, &test1);
  printf("CaseTest Name: %s\n", test1.name);
  printf("Num of items: %d\n", test1.n);
  for(int i=0; i<test1.n;i++)
  {
    printf("Loaded item%d: %d\n", i, test1.items[i]);
  }
}
