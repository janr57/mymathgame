/*
 * mathops.c
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "algorithms.h"
#include "mathops.h"

int try_mathops(mathgame_t *mg)
{
  // Copy array 'mg->nums' into 'nums'
  // Reserve memory for the array
  long *nums = malloc(mg->nums_len * sizeof(long));
  for (size_t i=0; i<mg->nums_len; i++) {
    nums[i] = mg->nums[i];
  }
  size_t nums_len = mg->nums_len;
  
  // Copy array 'mg->mathops' into 'mathops'
  // Reserve memory for the string
  size_t ops_len = nums_len - 1;
  char *ops = malloc(1 + ops_len);

  int ret;
  // Start, both nums and ops
  int sn = 1;
  int so = 1;
  // Produce permutation of 'nums' and 'ops_item' variations with repetitions
  while ((ret = pwr_varwr(&sn, &so, nums,  ops, ops_len, mg)) != 0) {
    //print_job(nums, nums_len, ops, ops_len);
  }

  free(nums);
  free(ops);
  
  return 0;
}

int pwr_varwr(int *sn, int *so, long *nums, char *ops, size_t ops_len, mathgame_t *mg)
{
  int retnums = 1;
  int retops = 1;

  if (*sn == 1) {
    if ((retnums = first_lnums_permutation(nums, mg->nums_len)) != 0) {
      *sn = 0;
      // Calculate number of different permutations with repetition of 'nums'
      size_t nums_pwr_count = pwr_count(nums, mg->nums_len);
      // Calculate number of different variations with repetition of 'ops'
      size_t ops_varr_count = pow(mg->mathops_len, ops_len);
      printf("Numerical permutations: %lu\n", nums_pwr_count);
      printf("Number of variations of operations: %lu\n", ops_varr_count);
      printf("Number of jobs: %lu\n", nums_pwr_count * ops_varr_count);
      retops = varwr(so, ops, ops_len, mg);
      *so = (retops == 0) ? 1 : 0;
    }
  } else if (*so == 0) {
    // Más operaciones y mantener números
    retops = varwr(so, ops, ops_len, mg);
    *so = (retops == 0) ? 1 : 0;
  } else if (retnums != 0) {
    retnums = next_lnums_permutation(nums, mg->nums_len);
    retops = varwr(so, ops, ops_len, mg);
    *so = (retops == 0) ? 1 : 0;
  }
  
  return retnums;
}

int varwr(int *so, char *ops, size_t ops_len, mathgame_t *mg)
{
  int ret;
  if (*so == 0) {
    ret = next_ops_item(ops, ops_len, mg->mathops, mg->mathops_len);
    if (ret == 0) {
      *so = 1;
    }
    return ret;
  } else {
    // Generate first mathops_item string
    ret = 1;
    first_ops_item(ops, ops_len, mg->mathops, mg->mathops_len);
    *so = 0;
    return ret;
  }
}

void print_job(long *nums, size_t nums_len, char *ops, size_t ops_len)
{
  print_nums(nums, nums_len);
  printf(" %s\n", ops);
}

  /*
  // Produce permutations of numbers
  // For each permutation try every possible combination of math operations
  
  int ret;
  ret = first_lnums_permutation(nums, mg->nums_len);
  // Number of different permutations with repetition of 'nums'
  size_t nums_pwr_count = pwr_count(nums, mg->nums_len);
  printf("nums permutations: %lu\n", nums_pwr_count);
  print_nums(nums, mg->nums_len);
  // Generate first mathops_item string
  first_ops_item(ops_item, len, mg->mathops, mg->mathops_len);
  printf("Maths operation [ 1]: %s\n", ops_item);
  // Generate the rest mathops_items
  int i = 1;
  int val;
  while ((val = next_ops_item(ops_item, len, mg->mathops, mg->mathops_len)) == 1) {
    printf("Maths operation [%2d]: %s\n", i, ops_item);
    i++;
  }

  while ((ret = next_lnums_permutation(nums, mg->nums_len)) != 0) {
    print_nums(nums, mg->nums_len);
    // Generate first mathops_item string
    first_ops_item(ops_item, len, mg->mathops, mg->mathops_len);
    printf("Math maths operation item [ 1]: %s\n", ops_item);
    // Generate the rest mathops_items
    int i = 1;
    int val;
    while ((val = next_ops_item(ops_item, len, mg->mathops, mg->mathops_len)) == 1) {
      printf("Next maths operation item [%2d]: %s\n", i, ops_item);
      i++;
    }
  }
  */

  /*
  // Generate first mathops_item
  // Reserve memory for the string
  size_t len = mg->nums_len - 1;
  char *ops_item = malloc(1 + len);
  first_ops_item(ops_item, len, mg->mathops, mg->mathops_len);
  printf("Math maths operation item [ 0]: %s\n", ops_item);
  
  // Generate the rest mathops_items
  int i = 1;
  int val;
  while ((val = next_ops_item(ops_item, len, mg->mathops, mg->mathops_len)) == 1) {
    printf("Next maths operation item [%2d]: %s\n", i, ops_item);
    i++;
  }
  */

