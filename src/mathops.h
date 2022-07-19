/*
 * mathops.h
 */

#ifndef MATHOPS_H___
#define MATHOPS_H___

typedef struct _Mathgame {
  long total;
  long *nums;
  char *mathops;
  size_t nums_len;
  size_t mathops_len;
  size_t ops_item_len;
  size_t nums_perm_rep;
  size_t ops_var_rep;
  size_t jobs_count;
} mathgame_t;

typedef struct _Job {
  size_t job_no;
  long total;
  long nums;
  char *ops_item;
  size_t *ops_item_len;
  int result;
  int success;
} job_t;

int try_mathops(mathgame_t *mg);
int nums_perm_rep(int *sn, long *nums, mathgame_t *mg);
int ops_var_rep(int *so, char *ops, mathgame_t *mg);
void print_nums_item(long *nums, size_t nums_len);
void print_ops_item(char *ops);
void print_job(size_t job_no, long *nums, char *ops, mathgame_t *mg);

#endif /* MATHOPS_H___ */

