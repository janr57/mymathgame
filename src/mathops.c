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
  mg->ops_item_len = nums_len - 1;
  char *ops = malloc(1 + mg->ops_item_len);

  // Calculate number of different permutations with repetition of 'nums'
  mg->nums_perm_rep = pwr_count(nums, mg->nums_len); 
  // Calculate number of different variations with repetition of 'ops'
  mg->ops_var_rep = pow(mg->mathops_len, mg->ops_item_len);
  // Calculate number of jobs
  mg->jobs_count = mg->nums_perm_rep * mg->ops_var_rep;

  // Print above calculations
  printf("Numerical permutations: %lu\n", mg->nums_perm_rep);
  printf("Number of variations of operations: %lu\n",mg-> ops_var_rep);
  printf("Number of jobs: %lu\n", mg->nums_perm_rep * mg->ops_var_rep);

  // Start both, nums and ops
  int sn = 1;
  int so = 1;
  int retnums, retops;
  size_t job_no = 1;
  // Produce jobs to calculate and compare with total
  while ((retnums = nums_perm_rep(&sn, nums, mg)) != 0) {
    while ((retops = ops_var_rep(&so, ops, mg)) != 0) {
      print_job(job_no, nums, ops, mg);
      job_no++;
    }
  }

  free(nums);
  free(ops);
  
  return 0;
}

// Produce permutations with repetition of 'nums, as a list,
// one at a time
int nums_perm_rep(int *sn, long *nums, mathgame_t *mg)
{
  int retnums = 1;
  
  if (*sn == 1) {
    retnums = first_lnums_permutation(nums, mg->nums_len);
    *sn = 0;
  } else if (*sn == 0) {
    retnums = next_lnums_permutation(nums, mg->nums_len);
  }
  
  return retnums;
}

// Produce variations with repetition of mathematical operations as a list,
// one at a time
int ops_var_rep(int *so, char *ops, mathgame_t *mg)
{
  int retops = 1;

  if (*so == 1) {
    retops = first_ops_item(ops, mg->ops_item_len, mg->mathops, mg->mathops_len);
    *so = 0;
  } else if (*so == 0) {
    retops = next_ops_item(ops, mg->ops_item_len, mg->mathops, mg->mathops_len);
  }

  if (retops == 0) {
    *so = 1;
  }

  return retops;
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

void print_nums_item(long *nums, size_t nums_len)
{
  printf("[");
  for (size_t i = 0; i < nums_len; i++) {
    printf("%ld", nums[i]);
    if (i != nums_len - 1) {
      printf(",");
    }
  }
  printf("]");
}

void print_ops_item(char *ops)
{
  printf("%s\n", ops);
}

void print_job(size_t job_no, long *nums, char *ops, mathgame_t *mg)
{
  char format_string[] = "%\0\0\0\0\0";
  //int digits_no = ceil(log(mg->jobs_count)/log(10));
  int digits_no = 1 + (int) (log(mg->jobs_count)/log(10));
  int written_digits = snprintf(format_string + 1, digits_no + 1, "%d", digits_no);
  int pos = (written_digits == 1) ? 2 : 3;
  format_string[pos] = 'd';
  
  printf(format_string, job_no);
  printf(" -> ");
  print_nums_item(nums, mg->nums_len);
  printf(" ");
  print_ops_item(ops);
}

