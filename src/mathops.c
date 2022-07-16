/*
 * mathops.c
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mathops.h"

int try_mathops(strct_mathgame *mg)
{
  /* Copy array 'mg->nums' into 'nums' */
  long *nums = malloc(mg->nums_len * sizeof(long));
  for (size_t i=0; i<mg->nums_len; i++) {
    nums[i] = mg->nums[i];
  }

  for (size_t i = 0; i < mg->nums_len; i++) {
    printf("%ld ", nums[i]);
  }
  printf("\n");

  int ret;
  while ((ret = next_permutation(nums, mg->nums_len)) != 0) {
    ret = next_permutation(nums, mg->nums_len);
    for (size_t i = 0; i < mg->nums_len; i++) {
      printf("%ld ", nums[i]);
    }
    printf("\n");
  }

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
  
  return 0;
}


int first_ops_item(char *ops_item, size_t len, char *mathops, size_t mathops_len)
{ 
  if (mathops_len == 0) {
    return -1;
  }
  
  for (int i=0; i<len; i++) {
    ops_item[i] = mathops[0];
  }
  
  return 0;
}

int next_ops_item(char *ops_item, size_t len, char *mathops, size_t mathops_len)
{
  char first_char = mathops[0];
  char last_char = mathops[mathops_len - 1];
  char *p = ops_item;

  int retval = 0;
  int j;
  char ch;

  for (int i = len - 1; i >= 0; i--) {
    if ((ch = *(p + i)) != last_char) {
      j = find_string(mathops, ch);
      *(p + i) = mathops[j + 1];
      retval = 1;
      break;
    } else {
      *(p + i) = first_char;
    }
  }
  
  return retval;
}

int find_string(char *mathops, char ch)
{
  char *found = strchr(mathops, ch);
  if (found == NULL) {
    return -1;
  }
  
  int i = strlen(mathops) - strlen(found);

  return i;
}

/*
 * Computes the next lexicographical permutation of the specified array of
 * long ints in place */
int next_permutation(long *nums, size_t len)
{
  // Find non-increasing suffix
  if (len == 0) {
    return 0;
  }

  size_t i = len - 1;
  while (i > 0 && nums[i - 1] >= nums[i]) {
    i--;
  }

  if (i == 0) {
    return 0;
  }

  // Find successor to pivot
  size_t j = len - 1;
  while (nums[j] <=  nums[i - 1]) {
    j--;
  }

  int temp = nums[i - 1];
  nums[i - 1] = nums[j];
  nums[j] = temp;

  // Reverse suffix
  j = len - 1;
  while (i < j) {
    temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
    i++;
    j--;
  }

  return 1;
}


