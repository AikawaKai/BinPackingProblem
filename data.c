#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void load_dataset(char *filename, dataset d_s)
{
  FILE *fp;
  char buff[255];
  int num_cases;
  char problem_identifier[255];
  char problem_header[255];
  int bin_capacity;
  int num_instances;
  int best_solution;

  // apertura del file
  printf("\nOpening File: %s\n", filename);
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    fprintf(stderr,"File %s could not be opened!\n", filename);
    exit(-1);
  }
  // numero di casi di test nel file
  fscanf(fp, "%s", buff);
  num_cases = atoi(buff);
  printf("Number of cases : %d\n", num_cases);

  // nome del caso di test specifico
  fscanf(fp, "%s", buff);
  strcpy(problem_identifier, buff);
  printf("Problem string: %s\n", problem_identifier);

  // bin capacity del caso di test
  fscanf(fp, "%s", buff);
  bin_capacity = atoi(buff);
  printf("bin_capacity: %d\n", bin_capacity);

  // numero di istanze del caso di test
  fscanf(fp, "%s", buff);
  num_instances = atoi(buff);
  printf("Instances number: %d\n", num_instances);

  // miglior soluzione fino ad ora
  fscanf(fp, "%s", buff);
  best_solution = atoi(buff);
  printf("Best Solution: %d\n", best_solution);

}
