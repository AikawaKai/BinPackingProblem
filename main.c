#include <stdio.h>
#include "hashset.h"
#include "firstfit.h"
#include "string.h"
#include "MBSprocedure.h"
#include "VNS.h"

int main(int argc, char *argv[]){
  srand(7);
  char *filename = argv[1];
  char buff[255];
  int max_num_elem;
  int firstfit_res, firstfistdecr_res, mbs_res, mbs_i_res, mbs_sampling;
  dataset_t *datasets;
  sol_t *solutions;
  sol_t *sampling_sol;
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
  fclose(filepointer);
  //print_list(copy(datasets[0].head));
  filepointeroutput = fopen(strcat(filename, ".csv"), "w");
  fprintf(filepointeroutput, "%s, %s, %s, %s, %s, %s, %s\n","dataset", "firstfit", "firstfitdecreasing", "MBS", "MBS'", "MBS'sampling", "best known solution");
  for(int i=0; i<num_cases; i++)
  {
    node_t *new_head = malloc(sizeof(node_t));
    printf("---------------------\n");

    // First fit
    firstfit(&datasets[i], &solutions[i]);
    printf("Solution firstfit: %d\n", solutions[i].n);
    firstfit_res = solutions[i].n;

    // First Fit decreasing
    free_solution(&solutions[i]);
    max_num_elem = (datasets[i].bin_size / datasets[i].sorteditems[(datasets[i].n)-1])+1;
    initialize_solution(&solutions[i], datasets[i].bin_size, datasets[i].n, max_num_elem);
    firstfitdecreasing(&datasets[i], &solutions[i]);
    firstfistdecr_res = solutions[i].n;
    printf("Solution firstfitdecreasing: %d\n", solutions[i].n);

    // Minimum Bin Slack
    free_solution(&solutions[i]);
    initialize_solution(&solutions[i], datasets[i].bin_size, datasets[i].n, max_num_elem);
    new_head = copy(datasets[i].head);
    MBS(&datasets[i], &solutions[i]);
    mbs_res = solutions[i].n;
    printf("Solution MBS: %d\n", solutions[i].n);

    // Minimum Bin Slack Modified
    free_list(datasets[i].head);
    datasets[i].head = malloc(sizeof(node_t));
    datasets[i].head = new_head;
    new_head = copy(datasets[i].head);
    free_solution(&solutions[i]);
    initialize_solution(&solutions[i], datasets[i].bin_size, datasets[i].n, max_num_elem);
    MBSmodified(&datasets[i], &solutions[i]);
    mbs_i_res = solutions[i].n;
    printf("Solution MBSmodified: %d\n", solutions[i].n);
    // Minimum Bin Slack Modified Sampling
    free_list(datasets[i].head);
    datasets[i].head = malloc(sizeof(node_t));
    datasets[i].head = new_head;

    // VNS METHOD
    VNSmethod(&datasets[i], &solutions[i], 7);
    //VNS METHOD

    free_solution(&solutions[i]);
    sampling_sol = MBSsampling(&datasets[i]);
    mbs_sampling = sampling_sol->n;
    printf("Solution MBSsampling: %d\n", mbs_sampling);
    // Write to csv
    fprintf(filepointeroutput, "%s, %d, %d, %d, %d, %d, %d\n",datasets[i].name, firstfit_res, firstfistdecr_res, mbs_res, mbs_i_res, mbs_sampling, datasets[i].best_sol);
    //print_solution(sampling_sol);
    free_solution(sampling_sol);
    free_dataset(&datasets[i]);
  }
  free(solutions);
  free(datasets);
  fclose(filepointeroutput);
}
