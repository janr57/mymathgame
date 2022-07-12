/*
 * mathops.c
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mathops.h"

int try_mathops(long total, long numcount, long *pnums)
{
  /* Available math operations */
  char *avail_ops = "+-*/";
  
  /* Copy 'pnums' in 'tnums' */
  long *tnums = malloc(numcount * sizeof(long));
  for (int i=0; i<numcount; i++) {
    tnums[i] = pnums[i];
  }

  /* */
  char *oplist = start_oplist(numcount, avail_ops);
  printf("First math operation list: %s\n", oplist);
  int retval = 1;
  int i = 1;
  while ((retval = next_oplist(oplist, numcount, avail_ops) == 1)) {
    printf("Next math operation list %d: %s\n", i, oplist);
    i++;
  }
  
  printf("No math operations yet!\n");

  for (int i = 0; i < numcount; i++) {
    printf("%ld ", tnums[i]);
  }
  printf("\n");

  int ret;
  do {
    ret = next_permutation(tnums, numcount);
    for (int i = 0; i < numcount; i++) {
      printf("%ld ", tnums[i]);
    }
    printf("\n");
  } while(ret);
  
  return 0;
}


char *start_oplist(long numcount, char *avail_ops)
{
  char first_char = avail_ops[0];

  char *oplist = malloc((numcount - 1) * sizeof(long));
  for (int i = 0; i < numcount -1; i++) {
    oplist[i] = first_char;
  }

  return oplist;
}


/*
 * Computes the next lexicographical permutation of the specified array of
 * long ints in place */

int next_oplist(char *oplist, long numcount, char *avail_ops)
{
  int count_avail_ops = strlen(avail_ops);
  char first_char = avail_ops[0];
  char last_char = avail_ops[count_avail_ops - 1];
  char *p = oplist;

  int retval = 0;
  int i;
  int count = 0;
  char ch;
  
  do {
    if ((ch = *p) != last_char) {
      i = find_string(avail_ops, ch);
      *p = avail_ops[i + 1];
      retval = 1;
      break;
    } else {
      *p = first_char;
      p++;
      count++;
    }
  } while (count < (numcount - 1));

  return retval;
}

int find_string(char *avail_ops, char ch)
{
  int i = strlen(avail_ops) - strlen(strchr(avail_ops, ch));

  return i;
}

int next_permutation(long *nums, long len)
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


