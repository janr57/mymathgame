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
} mathgame_t;

int try_mathops(mathgame_t *mg);
int pwr_varwr(int *sn, int *so, long *nums, char *ops, size_t ops_len, mathgame_t *mg);
int varwr(int *so, char *ops, size_t ops_len, mathgame_t *mg);
void print_job(long *nums, size_t nums_len, char *ops, size_t ops_len);

#endif /* MATHOPS_H___ */

