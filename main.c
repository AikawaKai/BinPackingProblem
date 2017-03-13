#include <stdio.h>
#include "hashset.h"
#include "firstfit.h"
#include "MBSprocedure.h"

int main(int argc, char *argv[]){
  char *filename = argv[1];
  char fileoutput[] = "output.csv";
  char buff[255];
  int max_num_elem;
  int firstfit_res, firstfistdecr_res, mbs_res;
  dataset_t *datasets;
  sol_t *solutions;
  FILE *filepointer;
  FILE *filepointeroutput;
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
  filepointeroutput = fopen(fileoutput, "w");
  for(int i=0; i<num_cases; i++)
  {
    printf("---------------------\n");
    firstfit(&datasets[i], &solutions[i]);
    printf("Solution firstfit: %d\n", solutions[i].n);
    firstfit_res = solutions[i].n;
    free_solution(&solutions[i]);
    initialize_solution(&solutions[i], datasets[i].bin_size, datasets[i].n, max_num_elem);
    firstfitdecreasing(&datasets[i], &solutions[i]);
    firstfistdecr_res = solutions[i].n;
    printf("Solution firstfitdecreasing: %d\n", solutions[i].n);
    free_solution(&solutions[i]);
    initialize_solution(&solutions[i], datasets[i].bin_size, datasets[i].n, max_num_elem);
    MBSmodified(&datasets[i], &solutions[i]);
    mbs_res = solutions[i].n;
    printf("Solution MBSmodified: %d\n", solutions[i].n);
    fprintf(filepointeroutput, "%d, %d, %d, %d\n", firstfit_res, firstfistdecr_res, mbs_res, datasets[i].best_sol);
  }

  for(int i=0; i<num_cases; i++)
  {
    free_solution(&solutions[i]);
    free_dataset(&datasets[i]);
  }
}
