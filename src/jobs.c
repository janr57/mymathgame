/*
 * jobs.c
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "messages.h"
#include "algorithms.h"
#include "jobs.h"

int produce_jobs(mathgame_t *mg)
{
  // Copy array 'mg->nums' into 'nums'
  // Reserve memory for the array
  long *nums_item = malloc(mg->nums_len * sizeof(long));
  for (size_t i=0; i<mg->nums_len; i++) {
    nums_item[i] = mg->nums[i];
  }
  size_t nums_len = mg->nums_len;
  
  // Copy array 'mg->mathops' into 'mathops'
  // Reserve memory for the string
  mg->ops_item_len = nums_len - 1;
  char *ops_item = malloc(1 + mg->ops_item_len);

  // Calculate number of different permutations with repetition of 'nums'
  mg->nums_perm_rep = pwr_count(nums_item, mg->nums_len); 
  // Calculate number of different variations with repetition of 'ops'
  mg->ops_var_rep = pow(mg->mathops_len, mg->ops_item_len);
  // Calculate number of jobs
  mg->jobs_count = mg->nums_perm_rep * mg->ops_var_rep;

  // Print above calculations
  printf("Numerical permutations: %zu\n", mg->nums_perm_rep);
  printf("Number of variations of operations: %zu\n",mg-> ops_var_rep);
  printf("Number of jobs: %zu\n", mg->nums_perm_rep * mg->ops_var_rep);

  // Start both, nums and ops
  int sn = 1;
  int so = 1;
  int retnums, retops, retjob;
  size_t job_no = 1;
  job_t *job = NULL;
  // Produce jobs to calculate and compare with total
  while ((retnums = nums_perm_rep(&sn, nums_item, mg)) != 0) {
    while ((retops = ops_var_rep(&so, ops_item, mg)) != 0) {
      job = create_job(job_no, nums_item, ops_item, mg);
      if ((retjob = calculate_job(job)) == -1) {
	fprintf(stderr, "%s: %zu\n", ERR_JOB_CALC, job->job_no);
      }
      print_job(job, mg);
      job_no++;
      free(job->nums_item);
      free(job->ops_item);
      free(job);
    }
  }

  free(nums_item);
  free(ops_item);
  
  return 0;
}

job_t *create_job(size_t job_no, long *nums, char *ops, mathgame_t *mg)
{
  job_t *job = malloc(sizeof(job_t));
  job->job_no = job_no;
  job->total = mg->total;
  job->nums_item = malloc(mg->nums_len * sizeof(long));
  for (size_t i = 0; i < mg->nums_len; i++) {
    job->nums_item[i] = nums[i];
  };
  job->nums_item_len = mg->nums_len;
  job->ops_item = malloc(1 + mg->ops_item_len * sizeof(char));
  snprintf(job->ops_item, 1 + mg->ops_item_len, "%s", ops);
  job->ops_item_len = mg->ops_item_len;
  job->filename = malloc(1 + mg->filename_len * sizeof(char));
  snprintf(job->filename, 1 + mg->filename_len, "%s", mg->filename);
  job->filename_len = mg->filename_len;
  return job;
}

int calculate_job(job_t *job)
{
  double acum = 0;
  char op;
  
  // Initial calculation
  op = job->ops_item[0];
  if (op == '+') {
    acum = job->nums_item[0] + job->nums_item[1];
  } else if (op == '-') {
    acum = job->nums_item[0] - job->nums_item[1];
  } else if (op == '*') {
    acum = job->nums_item[0] * job->nums_item[1];
  } else if (op == '/') {
    acum = job->nums_item[0] / job->nums_item[1];
  }

  for (size_t i = 1; i < job->ops_item_len; i++) {
    op = job->ops_item[i];
    if (op == '+') {
      acum += job->nums_item[i+1];
    } else if (op == '-') {
      acum -= job->nums_item[i+1];
    } else if (op == '*') {
      acum *= job->nums_item[i+1];
    } else if (op == '/') {
      acum /= job->nums_item[i+1];
    }
  }

  job->result = acum;

  if (job->result == job->total) {
    job->success = 1;
  } else {
    job->success = 0;
  }

  return 0;
}

double add(double a, double b)
{
  return a + b;
}

double substract(double a, double b)
{
  return a - b;
}

double multiply(double a, double b)
{
  return a * b;
}

double divide(double a, double b)
{
  return a/b;
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
  printf("%s", ops);
}

void print_job(job_t *job, mathgame_t *mg)
{
  char format_string[] = "%\0\0\0\0\0";
  int digits_no = 1 + (int) (log(mg->jobs_count)/log(10));
  int written_digits = snprintf(format_string + 1, digits_no + 1, "%d", digits_no);
  int pos = (written_digits == 1) ? 2 : 3;
  format_string[pos] = 'd';
  
  printf(format_string, job->job_no);
  printf(": ");
  print_nums_item(job->nums_item, mg->nums_len);
  printf(" ");
  print_ops_item(job->ops_item);
  if (job->success == 1) {
    printf(" -> SUCCESS ");
  } else {
    printf(" -> ------- ");
  }
  printf(" %g\n", job->result);
}

