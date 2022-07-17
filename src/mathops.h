/*
 * mathops.h
 */

#ifndef MATHOPS_H___
#define MATHOPS_H___

typedef struct _Rational {
  long num;
  long den;
} rational_t;

typedef struct _Mathgame {
  long total;
  long *nums;
  char *mathops;
  size_t nums_len;
  size_t mathops_len;
} mathgame_t;

int try_mathops(mathgame_t *mg);
void print_nums(long *nums, size_t nums_len);
void rat_init(rational_t *r, long n, long d);
void rat_add(rational_t *z, rational_t x, rational_t y);
void rat_sub(rational_t *z, rational_t x, rational_t y);
void rat_mul(rational_t *z, rational_t x, rational_t y);
void rat_div(rational_t *z, rational_t x, rational_t y);
void rat_reduce(rational_t *z);

#endif /* MATHOPS_H___ */

