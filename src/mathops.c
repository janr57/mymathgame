/*
 * mathops.c
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "algorithms.h"
#include "mathops.h"

int try_mathops(mathgame_t *mg)
{
  // Copy array 'mg->nums' into 'nums'
  // Reserve memory for the array
  long *nums = malloc(mg->nums_len * sizeof(long));
  for (size_t i=0; i<mg->nums_len; i++) {
    nums[i] = mg->nums[i];
  }

  // Copy array 'mg->mathops' into 'mathops'
  // Reserve memory for the string
  size_t len = mg->nums_len - 1;
  char *ops_item = malloc(1 + len);

  // Produce permutations of numbers
  // For each permutation try every possible combination of math operations
  int ret;
  ret = first_lnums_permutation(nums, mg->nums_len);
  // Number of different permutations with repetition of 'nums'
  size_t nums_pwr_count = pwr_count(nums, mg->nums_len);
  
  printf("nums permutations: %lu\n", nums_pwr_count);
  print_nums(nums, mg->nums_len);
  // Generate first mathops_item string
  first_ops_item(ops_item, len, mg->mathops, mg->mathops_len);
  printf("Maths operation [ 1]: %s\n", ops_item);
  // Generate the rest mathops_items
  int i = 1;
  int val;
  while ((val = next_ops_item(ops_item, len, mg->mathops, mg->mathops_len)) == 1) {
    printf("Maths operation [%2d]: %s\n", i, ops_item);
    i++;
  }

  while ((ret = next_lnums_permutation(nums, mg->nums_len)) != 0) {
    print_nums(nums, mg->nums_len);
    // Generate first mathops_item string
    first_ops_item(ops_item, len, mg->mathops, mg->mathops_len);
    printf("Math maths operation item [ 1]: %s\n", ops_item);
    // Generate the rest mathops_items
    int i = 1;
    int val;
    while ((val = next_ops_item(ops_item, len, mg->mathops, mg->mathops_len)) == 1) {
      printf("Next maths operation item [%2d]: %s\n", i, ops_item);
      i++;
    }
  }

  /*
  // Generate first mathops_item
  // Reserve memory for the string
  size_t len = mg->nums_len - 1;
  char *ops_item = malloc(1 + len);
  first_ops_item(ops_item, len, mg->mathops, mg->mathops_len);
  printf("Math maths operation item [ 0]: %s\n", ops_item);
  
  // Generate the rest mathops_items
  int i = 1;
  int val;
  while ((val = next_ops_item(ops_item, len, mg->mathops, mg->mathops_len)) == 1) {
    printf("Next maths operation item [%2d]: %s\n", i, ops_item);
    i++;
  }
  */
  
  return 0;
}

void rat_init(rational_t *r, long n, long d)
{
  r->num = n;
  r->den = d;
}

void rat_add(rational_t *z, rational_t x, rational_t y)
{
  z->num = x.num * y.den + x.den * y.num;
  z->den = x.den * y.den;
}

void rat_sub(rational_t *z, rational_t x, rational_t y)
{
  z->num = x.num * y.den - x.den * y.num;
  z->den = x.den * y.den;
}

void rat_mul(rational_t *z, rational_t x, rational_t y)
{
  z->num = x.num * y.num;
  z->den = x.den * y.den;
}

void rat_div(rational_t *z, rational_t x, rational_t y)
{
  z->num = x.num * y.den;
  z->den = x.den * y.num;
}

void rat_reduce(rational_t *z)
{
  long r1 = z->num;
  long r2 = z->den;
  long gcd = r2;

  while (r1 % r2) {
    gcd = r1 % r2;
    r1 = r2;
    r2 = gcd;
  }

  z->num /= gcd;
  z->den /= gcd;
}

