/*
 * mathops.h
 */

#ifndef MATHOPS_H___
#define MATHOPS_H___

typedef struct _Rational {
  long num;
  long den;
} str_Rational;

int try_mathops(long total, long numcount, long *pnums);
char *get_operation_list(long numcount);
char *start_oplist(long numcount, char *avail_ops);
int next_oplist(char *oplist, long numcount, char *avail_ops);
int find_string(char *avail_ops, char ch);
int next_permutation(long *nums, long len);

#endif /* MATHOPS_H___ */

