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

int find_string(char *str, char ch);
int first_ops_item(char *ops_item, size_t len, char *mathops, size_t mathops_len);
int next_ops_item(char *ops_item, size_t len, char *mathops, size_t mathops_len);
int first_long_lexic_permutation(long *nums, size_t nums_len);
int next_long_lexic_permutation(long *nums, size_t nums_len);
size_t pwr_count(long *nums, size_t len);

char *file_with_timestamp(char *name, char *ext);

typedef struct _Rational {
  long num;
  long den;
} rational_t;

void print_nums(long *nums, size_t nums_len);
void rat_init(rational_t *r, long n, long d);
void rat_add(rational_t *z, rational_t x, rational_t y);
void rat_sub(rational_t *z, rational_t x, rational_t y);
void rat_mul(rational_t *z, rational_t x, rational_t y);
void rat_div(rational_t *z, rational_t x, rational_t y);
void rat_reduce(rational_t *z);

#endif /* ALGORITHMS_H___ */

