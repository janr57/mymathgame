/*
 * options.c
 * Deal with the options which are input from the user.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "algorithms.h"
#include "options.h"

int get_options(int *argc, char **argv, options_t *opts)
{
  int errcode;
  
  // Get 'opts.str_nums', 'opts.str_total' and 'opts.str_mathops' from the program
  // arguments.
  if ((errcode = get_str_options(argc, argv, opts)) == -1) {
    return -1;
  }

  if ((errcode = get_real_options(opts)) == -1) {
    return -1;
  }

  return 0;
}

/*
 * Function: get_str_options
 * Arguments:
 * argc: Pointer to the 'argc' number of arguments passed to the program.
 * argv: Actual array of arguments passed to the program.
 * opts->str_nums: String of numbers separated by commas.
 *                 The numbers we want to add/substract/multiply/divide.
 * opts->str_total: String number.
 *                  The desired result of the basic operations on the numbers.
 * Returns:
 * -1: error
 *  0: Ok
 */
int get_str_options(int *argc, char **argv, options_t *opts)
{
  /* Expect at least four arguments */
  if ((*argc != 5) && (*argc != 7)) {
    usage(argv[0]);
    return -1;
  }

  int nflags = 0, tflags = 0, oflags = 0;
  int ch;

  while ((ch = getopt(*argc, argv, "n:t:o:")) != -1) {
    switch (ch) {
    case 'n':
      nflags++;
      opts->str_nums_len = strlen(optarg);
      opts->str_nums = malloc(1 + opts->str_nums_len);	
      strncpy(opts->str_nums, optarg, opts->str_nums_len);
      break;
    case 't':
      tflags++;
      opts->str_total_len = strlen(optarg);
      opts->str_total = malloc(1 + opts->str_total_len);
      strncpy(opts->str_total, optarg, opts->str_total_len);
      break;
    case 'o':
      oflags++;
      opts->str_mathops_len = strlen(optarg);
      opts->str_mathops = malloc(1 + opts->str_mathops_len);
      strncpy(opts->str_mathops, optarg, opts->str_mathops_len);
    default:
      usage(argv[0]);
    }
  }

  // Remaining command-line arguments (not needed)
  *argc -= optind;
  argv += optind;
  
  if ((nflags == 0) && (tflags == 0)) {
    fprintf(stderr, "%s\n", ERR_00);
    free(opts->str_nums);
    return -1;
  } else if ((nflags > 1) && (tflags == 0)) {
    fprintf(stderr, "%s\n", ERR_10);
    free(opts->str_nums);
    return -1;
  } else if ((nflags == 0) && (tflags > 1)) {
    fprintf(stderr, "%s\n", ERR_01);
    free(opts->str_nums);
    return -1;
  } else if ((nflags > 1) && (tflags > 1)) {
    fprintf(stderr, "%s\n", ERR_11);
    free(opts->str_nums);
    return -1;
  } else if (nflags == 0) {
    fprintf(stderr, "%s\n", ERR_0X);
    free(opts->str_nums);
    return -1;
  } else if (nflags > 1) {
    fprintf(stderr, "%s\n", ERR_1X);
    free(opts->str_nums);
    return -1;
  } else if (tflags == 0) {
    fprintf(stderr, "%s\n", ERR_X0);
    free(opts->str_nums);
    return -1;
  } else if (tflags > 1) {
    fprintf(stderr, "%s\n", ERR_X1);
    free(opts->str_nums);
    return -1;
  }

  return 0;
}

int get_real_options(options_t *opts)
{
  //int errcode;
  opts->nums_len = count_numbers(opts->str_nums);
  opts->nums = malloc(opts->nums_len * sizeof(long));

  //Convert the list of strings to numbers
  // Make sure that opts->str_nums has only digits and commas
  // Fill the opts->nums array from opts->str_nums
  char *pstr = opts->str_nums;
  long *p = opts->nums;
  //pstr = opts->str_nums;
  // Make sure that the first character of opts->str_nums is a digit
  // (a comma cannot appear as a first character)
  char ch = *opts->str_nums;
  if (!isdigit(ch)) {
    fprintf(stderr, "%s %s\n", ERR_FIRST_NUMS, opts->str_nums);
    free(opts->str_nums);
    free(opts->nums);
    return -1;
  }
  
  //int len = strlen(opts->str_nums);
  // We've already tested the first character, so we begin at the second
  // digits and commas are permitted
  for (int i = 1; i < opts->str_nums_len; i++) {
    ch = *pstr;
    if ((!isdigit(ch) && (ch != ','))) {
      fprintf(stderr, "%s: %c in %s\n", ERR_CHAR_NUMS, ch, opts->str_nums);
      free(opts->str_nums);
      free(opts->nums);
      return -1;
    }
  }

  // Make a copy of opts->str_nums
  // extracting tokens from the string, changes the string.
  char *str_nums_copy = malloc(1 + opts->str_nums_len);
  strncpy(str_nums_copy, opts->str_nums, opts->str_nums_len);
  char *rest = str_nums_copy;
  char *token;
  while ((token = strtok_r(rest, ",", &rest))) {
    pstr = token;
    while ((ch = *pstr++) != '\0') {
      if (!isdigit(ch)) {
	fprintf(stderr, "%s: %s\n", ERR_NUMS, token);
	free(opts->str_nums);
	free(opts->nums);
	free(str_nums_copy);
	return -1;
      }
    }
    *p++ = atol(token);
  }

  // Convert 'str_total' to long, provided it contains only digits
  pstr = opts->str_total;
  while ((ch = *pstr++) != '\0') {
    if (!isdigit(ch)) {
      fprintf(stderr, "%s: %s\n", ERR_TOTAL, opts->str_total);
      free(opts->str_nums);
      free(opts->nums);
      free(str_nums_copy);
      return -1;
    }
  }
  opts->total = atol(opts->str_total);

  // Check opts->str_mathops.
  pstr = opts->str_mathops;
  char *pstr2;
  char ch2;
  int i;
  while ((ch = *pstr++) != '\0') {
    // ch character must be one of valid_mathops
    i = find_string(valid_mathops, ch);
    if (i == -1) {
      fprintf(stderr, "%s: %c\n", ERR_INVALID_OP, ch);
      free(opts->str_nums);
      free(opts->nums);
      free(str_nums_copy);
      return -1;
    }
    // ch is a valid mathop
    // ch must not be more than once in opts->str_mathops
    pstr2 = pstr;
    while ((ch2 = *pstr2++) != '\0') {
      if (ch == ch2) {
	fprintf(stderr, "%s: %c\n", ERR_REPEATED_OP, ch);
	free(opts->str_nums);
	free(opts->nums);
	free(str_nums_copy);
	return -1;
      }
    }
  }

  // All valid mathops in opts->mathops in case the user does not specify them
  if (opts->str_mathops == NULL) {
    opts->str_mathops = malloc(1 + strlen(valid_mathops));
    strncpy(opts->str_mathops, valid_mathops, strlen(valid_mathops));
  } else {
    opts->mathops = malloc(1 + opts->str_mathops_len);
    strncpy(opts->mathops, opts->str_mathops, opts->str_mathops_len);
  }
  opts->mathops_len = strlen(opts->str_mathops);
  
  return 0;
}

int usage(char *progname) {
  if (strlen(progname) == 1) {
    fprintf(stderr, "%s %s\n", ERR_PROGNAME, progname);
    return -1;
  }
  printf("%s %s %s %s\n", MSG_USAGE_1, progname, MSG_USAGE_2, MSG_USAGE_3);

  return 0;
}

size_t count_numbers(char *string)
{
// Count comma character occurrences in string
  size_t len = strlen(string);
  size_t nums = 1;
  for (int i = 1; i < len; i++) {
    if (string[i] == ',') {
      nums++;
    }
  }
  
  return nums;
}

void print_nums(long *nums, size_t nums_len)
{
  for (size_t i = 0; i < nums_len; i++) {
    printf("%ld ", nums[i]);
  }
  printf("\n");
}

void print_mathops(char *mathops)
{
  printf("%s\n", mathops);
}

int print_options_summary(options_t *opts)
{
  printf("Numbers count: %lu\n", opts->nums_len);
  printf("Numbers: ");
  for (size_t i = 0; i < opts->nums_len; i++) {
    printf("%ld ", *(opts->nums + i));
  }
  printf("\n");
  printf("Total: %ld\n", opts->total);

  return 0;
}

