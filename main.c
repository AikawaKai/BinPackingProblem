#include <stdio.h>
#include "hashset.h"
#include "firstfit.h"
#include "string.h"
#include "MBSprocedure.h"
#include "VNS.h"

int main(int argc, char *argv[]){
  srand(0);
  char *filename = argv[1];
  char buff[255];
  int max_num_elem;
  int firstfit_res, firstfistdecr_res, mbs_res, mbs_i_res, mbs_sampling, vns;
  int num_cases;
  dataset_t *datasets;
  sol_t *solutions;
  sol_t *sampling_sol;
  sol_t *vns_sol;
  FILE *filepointer;
  FILE *filepointeroutput;
  filepointer = fopen(filename, "r");
  if (filepointer == NULL)
  {
    fprintf(stderr,"File %s could not be opened!\n", filename);
    exit(-1);
  }
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
  fprintf(filepointeroutput, "%s, %s, %s, %s, %s, %s, %s, %s\n","dataset", "firstfit", "firstfitdecreasing", "MBS", "MBS'", "MBS'sampling", "VNS", "best known solution");
  for(int i=0; i<num_cases; i++)
  {
    node_t *new_head = malloc(sizeof(node_t));
    printf("---------------------\n");

    // First fit
    firstfit(&datasets[i], &solutions[i]);
    printf("Solution firstfit: %d\n", solutions[i].n);
    firstfit_res = solutions[i].n;
    check_solution(&datasets[i], &solutions[i]);
    free_solution(&solutions[i]);


    // First Fit decreasing
    max_num_elem = (datasets[i].bin_size / datasets[i].sorteditems[(datasets[i].n)-1])+1;
    initialize_solution(&solutions[i], datasets[i].bin_size, datasets[i].n, max_num_elem);
    firstfitdecreasing(&datasets[i], &solutions[i]);
    firstfistdecr_res = solutions[i].n;
    printf("Solution firstfitdecreasing: %d\n", solutions[i].n);
    check_solution(&datasets[i], &solutions[i]);
    free_solution(&solutions[i]);


    // MBS
    initialize_solution(&solutions[i], datasets[i].bin_size, datasets[i].n, max_num_elem);
    new_head = copy(datasets[i].head);
    MBS(&datasets[i], &solutions[i]);
    mbs_res = solutions[i].n;
    printf("Solution MBS: %d\n", solutions[i].n);
    check_solution(&datasets[i], &solutions[i]);
    free_list(datasets[i].head);
    datasets[i].head = malloc(sizeof(node_t));
    datasets[i].head = new_head;
    new_head = copy(datasets[i].head);
    free_solution(&solutions[i]);

    // MBS Modified
    initialize_solution(&solutions[i], datasets[i].bin_size, datasets[i].n, max_num_elem);
    MBSmodified(&datasets[i], &solutions[i]);
    mbs_i_res = solutions[i].n;
    printf("Solution MBSmodified: %d\n", solutions[i].n);
    check_solution(&datasets[i], &solutions[i]);
    free_list(datasets[i].head);
    datasets[i].head = malloc(sizeof(node_t));
    datasets[i].head = new_head;

    // VNS METHOD
    vns_sol = VNSmethod(&datasets[i], &solutions[i], 15);
    check_solution(&datasets[i], vns_sol);
    vns = vns_sol->n;
    printf("Solution VNS: %d\n", vns_sol->n);
    free_solution(&solutions[i]);

    // MBS sampling
    sampling_sol = MBSsampling(&datasets[i], 100);
    check_solution(&datasets[i], sampling_sol);
    mbs_sampling = sampling_sol->n;
    printf("Solution MBSsampling: %d\n", mbs_sampling);
    free_solution(sampling_sol);

    // Write to csv
    fprintf(filepointeroutput, "%s, %d, %d, %d, %d, %d, %d, %d\n",datasets[i].name, firstfit_res, firstfistdecr_res, mbs_res, mbs_i_res, mbs_sampling, vns, datasets[i].best_sol);
    free_dataset(&datasets[i]);
  }
  free(solutions);
  free(datasets);
  fclose(filepointeroutput);
}
