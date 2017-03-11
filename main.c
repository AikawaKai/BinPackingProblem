#include <stdio.h>
#include "hashset.h"
#include "firstfit.h"
#include "MBSprocedure.h"

int main(int argc, char *argv[]){
  hashset_t test_best_set;
  hashset_t curre_a_set;
  dataset_t test1;
  node_t ** head_pointer;
  node_t * to_delete;
  sol_t s1;
  sol_t s2;
  sol_t s3;
  int max_num_elem;
  char *filename = argv[1];

  load_dataset(filename, &test1); // carica il caso di test nella struct dataset
  max_num_elem = (test1.bin_size / test1.sorteditems[(test1.n)-1])+1;
  printf("%d\n", test1.sorteditems[(test1.n-1)]);
  initialize_solution(&s1, test1.bin_size, test1.n, max_num_elem);
  initialize_solution(&s2, test1.bin_size, test1.n, max_num_elem);
  initialize_solution(&s3, test1.bin_size, test1.n, max_num_elem);
  firstfit(&test1, &s1);
  firstfitdecreasing(&test1, &s2);
  MBS(&test1, &s3);
  printf("Solution firstfit: %d\n", s1.n);
  printf("Solution firstfitdecreasing: %d\n", s2.n);
  printf("Solution MBS: %d\n", s3.n);
  /*print_list(test1.head);
  head_pointer = &test1.head;
  test_best_set = hashset_create(test1.bin_size);
  curre_a_set = hashset_create(test1.bin_size);
  MBSsearch(0, 120, 20, test1.head, curre_a_set, test_best_set);
  for(int i=0; i<test_best_set->nitems; i++)
  {
    remove_by_node_value(head_pointer, ((node_t **)test_best_set->items)[i]);
  }
  print_list(test1.head);
  printf("----------------------------------\n");
  hashset_destroy(test_best_set);
  hashset_destroy(curre_a_set);
  test_best_set = hashset_create(test1.bin_size);
  curre_a_set = hashset_create(test1.bin_size);
  MBSsearch(0, 117, 20, test1.head, curre_a_set, test_best_set);
  for(int i=0; i<test_best_set->nitems; i++)
  {
    remove_by_node_value(head_pointer, ((node_t **)test_best_set->items)[i]);
  }
  print_list(test1.head);
  hashset_destroy(test_best_set);
  hashset_destroy(curre_a_set);
  */
  free_dataset(&test1); // libero lo spazio occupato dal dataset
  free_solution(&s1);
  free_solution(&s2);
}
