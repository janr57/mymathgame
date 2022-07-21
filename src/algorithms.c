/*
 * algorithms.c
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "algorithms.h"

int find_string(char *mathops, char ch)
{
  char *found = strchr(mathops, ch);
  if (found == NULL) {
    return -1;
  }
  
  int i = strlen(mathops) - strlen(found);

  return i;
}

int first_ops_item(char *ops_item, size_t len, char *mathops, size_t mathops_len)
{ 
  if (mathops_len == 0) {
    return -1;
  }
  
  for (int i=0; i<len; i++) {
    ops_item[i] = mathops[0];
  }
  
  return 1;
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

  return 1;
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

// Number of permutations with repetition of 'nums' elements
size_t pwr_count(long *nums, size_t nums_len)
{
  size_t pwr = factorial_table[nums_len];
  long num = nums[0];
  size_t count = 1;
  for (size_t i = 1; i < nums_len; i++) {
    if (num == nums[i]) {
      count ++;
    } else {
      if (count != 1) {
	pwr /= factorial_table[count];
	count = 1;
      } 
      num = nums[i];
    }
  }

  if (count != 1) {
    pwr /= count;
  }
  
    return pwr;
}

/*
 Returns the current time.
*/
char *file_with_timestamp(char *name, char *ext)
{
  //char *name = "mathgame_";
  //char *ext = ".log";
  
  char *filename = malloc(strlen(name) + sizeof(char) * 16 + strlen(ext));
  time_t ltime = time(NULL);
  struct tm *tm;
  tm = localtime(&ltime);

  sprintf(filename, "%s%04d%02d%02d%02d%02d%02d%s", name, tm->tm_year+1900,
	  tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, ext);
  
  return filename;
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

