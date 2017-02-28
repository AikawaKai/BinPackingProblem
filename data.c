#include "data.h"
#include <stdio.h>


void load_dataset(char *filename, dataset d_s)
{
  FILE *fp;
  printf("\nOpening File: %s\n", filename);
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    fprintf(stderr,"File %s could not be opened!\n", filename);
  }
  fprintf(fp, "Testing...\n");
}
