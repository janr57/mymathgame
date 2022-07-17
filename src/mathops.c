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
  /* Copy array 'mg->nums' into 'nums' */
  long *nums = malloc(mg->nums_len * sizeof(long));
  for (size_t i=0; i<mg->nums_len; i++) {
    nums[i] = mg->nums[i];
  }

  int ret;
  ret = first_lnums_permutation(nums, mg->nums_len);
  print_nums(nums, mg->nums_len);
  /*
  while ((ret = next_lnums_permutation(nums, mg->nums_len)) != 0) {
  print_nums(nums, mg->nums_len);
  */
  
  while ((ret = next_lnums_permutation(nums, mg->nums_len)) != 0) {
    print_nums(nums, mg->nums_len);
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






