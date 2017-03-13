#include <stdio.h>
#include "hashset.h"
#include "firstfit.h"
#include "MBSprocedure.h"

int main(int argc, char *argv[]){
  char *filename = argv[1];
  char buff[255];
  int max_num_elem;
  dataset_t *datasets;
  sol_t *solutions;
  FILE *filepointer;
  filepointer = fopen(filename, "r");
  if (filepointer == NULL)
  {
    fprintf(stderr,"File %s could not be opened!\n", filename);
    exit(-1);
  }
  int num_cases;
  fscanf(filepointer, "%s", buff);
  num_cases = atoi(buff);
  datasets = malloc(num_cases * sizeof(dataset_t));
  solutions = malloc(num_cases * sizeof(sol_t));
  for(int i=0; i<num_cases; i++)
  {
    load_dataset_from_file_pointer(filepointer, &datasets[i]);
    max_num_elem = (datasets[i].bin_size / datasets[i].sorteditems[(datasets[i].n)-1])+1;
    initialize_solution(&solutions[i], datasets[i].bin_size, datasets[i].n, max_num_elem);
  }

  for(int i=0; i<num_cases; i++)
  {
    printf("---------------------\n");
    firstfit(&datasets[i], &solutions[i]);
    printf("Solution firstfit: %d\n", solutions[i].n);
    free_solution(&solutions[i]);
    initialize_solution(&solutions[i], datasets[i].bin_size, datasets[i].n, max_num_elem);
    firstfitdecreasing(&datasets[i], &solutions[i]);
    printf("Solution firstfitdecreasing: %d\n", solutions[i].n);
    free_solution(&solutions[i]);
    initialize_solution(&solutions[i], datasets[i].bin_size, datasets[i].n, max_num_elem);
    MBSmodified(&datasets[i], &solutions[i]);
    printf("Solution MBSmodified: %d\n", solutions[i].n);
  }





  /*
  hashset_t test_best_set;
  hashset_t curre_a_set;
  dataset_t test1;
  dataset_t test2;
  node_t ** head_pointer;
  node_t * to_delete;
  sol_t s1;
  sol_t s2;
  sol_t s3;
  sol_t s4;


  load_dataset(filename, &test1); // carica il caso di test nella struct dataset
  load_dataset(filename, &test2);
  printf("Min element:%d\n\n", test1.sorteditems[(test1.n-1)]);
  max_num_elem = (test1.bin_size / test1.sorteditems[(test1.n)-1])+1;
  initialize_solution(&s1, test1.bin_size, test1.n, max_num_elem);
  initialize_solution(&s2, test1.bin_size, test1.n, max_num_elem);
  initialize_solution(&s3, test1.bin_size, test1.n, max_num_elem);
  //print_list(test1.head);
  firstfit(&test1, &s1);
  firstfitdecreasing(&test1, &s2);
  // MBS(&test1, &s3);
  MBS(&test1, &s3);
  printf("Solution firstfit: %d\n", s1.n);
  printf("Solution firstfitdecreasing: %d\n", s2.n);
  printf("Solution MBS: %d\n", s3.n);
  initialize_solution(&s4, test1.bin_size, test1.n, max_num_elem);
  MBSmodified(&test2, &s4);
  printf("Solution MBSmodified: %d\n", s4.n);
  //print_list(test1.head);
  free_dataset(&test1); // libero lo spazio occupato dal dataset
  free_solution(&s1); // libero spazio soluzione s1
  free_solution(&s2); // libero spazio soluzione s2
  free_solution(&s3); // libero spazio soluzione s3
  free_solution(&s4); // libero spazio soluzione s4
  */
}
