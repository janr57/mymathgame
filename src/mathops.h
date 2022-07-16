/*
 * mathops.h
 */

#ifndef MATHOPS_H___
#define MATHOPS_H___

typedef struct _Rational {
  long num;
  long den;
} strct_rational;

typedef struct _Mathgame {
  long total;
  long *nums;
  char *mathops;
  size_t nums_len;
  size_t mathops_len;
} strct_mathgame;

int try_mathops(strct_mathgame *mg);
char *get_operation_list(size_t numcount);
int first_ops_item(char *ops_item, size_t len, char *mathops, size_t mathops_len);
int next_ops_item(char *ops_item, size_t len, char *mathops, size_t mathops_len);
int find_string(char *avail_ops, char ch);
int next_permutation(long *nums, size_t len);

#endif /* MATHOPS_H___ */

