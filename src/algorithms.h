/*
 * algorithms.h
 */

#ifndef ALGORITHMS_H___
#define ALGORITHMS_H___

// Small factorial table, from 0! up to 20!
static long factorial_table[] =
  {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600,
   6227020800, 87178291200, 1307674368000, 20922789888000, 355687428096000,
   6402373705728000, 121645100408832000, 2432902008176640000};

int find_string(char *mathops, char ch);
int first_ops_item(char *ops_item, size_t len, char *mathops, size_t mathops_len);
int next_ops_item(char *ops_item, size_t len, char *mathops, size_t mathops_len);
int find_string(char *avail_ops, char ch);
int first_lnums_permutation(long *nums, size_t len);
int next_lnums_permutation(long *nums, size_t len);
size_t pwr_count(long *nums, size_t len);

#endif /* ALGORITHMS_H___ */

