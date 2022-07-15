/*
 * mathops.h
 */

#ifndef MATHOPS_H___
#define MATHOPS_H___

typedef struct _Rational {
  long num;
  long den;
} str_Rational;

int try_mathops(long total, size_t numcount, long *pnums);
char *get_operation_list(size_t numcount);
char *start_oplist(size_t numcount, char *avail_ops);
int next_oplist(char *oplist, size_t numcount, char *avail_ops);
int find_string(char *avail_ops, char ch);
int next_permutation(long *nums, size_t len);

#endif /* MATHOPS_H___ */

