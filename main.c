#include <stdio.h>
#include "hashset.h"
#include "firstfit.h"

int main(int argc, char *argv[]){
  dataset_t test1;
  sol_t s1;
  sol_t s2;
  int max_num_elem;
  char *filename = argv[1];

  load_dataset(filename, &test1); // carica il caso di test nella struct dataset
  max_num_elem = (test1.bin_size / test1.sorteditems[(test1.n)-1])+1;
  printf("%d\n", test1.sorteditems[(test1.n-1)]);
  initialize_solution(&s1, test1.bin_size, test1.n, max_num_elem);
  initialize_solution(&s2, test1.bin_size, test1.n, max_num_elem);
  firstfit(&test1, &s1);
  firstfitdecreasing(&test1, &s2);
  printf("Solution firstfit: %d\n", s1.n);
  printf("Solution firstfitdecreasing: %d\n", s2.n);
  //print_list(test1.head);
  hashset_t set = hashset_create();
  hashset_add(set, test1.head);
  if (hashset_is_member(set, test1.head) == 1)
  {
    printf("Si\n");
  }
  else
  {
    printf("No\n");
  }
  //print_list(((node_t **)set->items)[0]);
  hashset_remove(set, test1.head);
  if (hashset_is_member(set, test1.head) == 1)
  {
    printf("Si\n");
  }
  else
  {
    printf("No\n");
  }
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
  free_solution(&s2);
}
