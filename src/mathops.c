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

int first_lnums_permutation(long *nums, size_t nums_len)
{
  long temp;
  long *p = nums;
  for (size_t i = 0; i < nums_len - 1; i++) {
    for (size_t j = i + 1; j < nums_len; j++) {
      if (p[i] > p[j]) {
	temp = p[i];
	p[i] = p[j];
	p[j] = temp;
      }
    }
  }

  return 0;
}

/*
 * Computes the next lexicographical permutation of the specified array of
 * long ints in place */
int next_lnums_permutation(long *nums, size_t len)
{
  // Find the longest non-increasing suffix
  size_t i = len - 1;
  while (i > 0 && nums[i - 1] >= nums[i]) {
    i--;
    // Now i is the head index of the suffix
  }
    
  // Are we at the last permutation  already?
  if (i <= 0) {
    return 0;
  }

  // Let nums[i - 1] be the pivot
  // Find rightmost element greater than the pivot
  size_t j = len - 1;
  while (nums[j] <= nums[i - 1]) {
    j--;
    // Now the value nums[j] will become the new pivot
    // Assertion: j >= i
  }

  // Swap the pivot with j
  long temp = nums[i - 1];
  nums[i - 1] = nums[j];
  nums[j] = temp;

  // Reverse the suffix
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

void print_nums(long *nums, size_t nums_len)
{
  for (size_t i = 0; i < nums_len; i++) {
    printf("%ld ", nums[i]);
  }
  printf("\n");
}

