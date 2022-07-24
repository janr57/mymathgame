/*
 * jobs.h
 */

#ifndef JOBS_H___
#define JOBS_H___

typedef struct {
  long total;
  long *nums;
  char *mathops;
  char *filename;
  size_t nums_len;
  size_t mathops_len;
  size_t filename_len;
  size_t ops_item_len;
  size_t nums_perm_rep;
  size_t ops_var_rep;
  size_t jobs_count;
} mathgame_st;

typedef struct {
  size_t job_no;
  long total;
  long *nums_item;
  char *ops_item;
  char *filename;
  size_t nums_item_len;
  size_t ops_item_len;
  size_t filename_len;
  double result;
  int success;
} job_st;

int produce_jobs(mathgame_st *mg);
int calculate_job(job_st *job);
double add(double a, double b);
double substract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
int nums_perm_rep(int *sn, long *nums, mathgame_st *mg);
int ops_var_rep(int *so, char *ops, mathgame_st *mg);
job_st *create_job(size_t job_no, long *nums, char *ops, mathgame_st *mg); 
void print_nums_item(long *nums, size_t nums_len);
void print_ops_item(char *ops);
void print_job(job_st *job, mathgame_st *mg);

#endif /* JOBS_H___ */

