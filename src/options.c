/*
 * options.c
 * Deal with the options which are input from the user.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#include "messages.h"
#include "algorithms.h"
#include "options.h"

int get_options(int *argc, char **argv, options_st *opts)
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
int get_str_options(int *argc, char **argv, options_st *opts)
{
  /* Expect at least four arguments */
  if ((*argc != 5) && (*argc != 7) && (*argc != 9)) {
    usage(argv[0]);
    return -1;
  }

  int nflags, tflags, oflags, fflags;
  nflags = tflags = oflags = fflags = 0;
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
      break;
      case 'f':
      fflags ++;
      opts->str_filename_len = strlen(optarg);
      opts->str_filename = malloc(1 + opts->str_filename_len);
      strncpy(opts->str_filename, optarg, opts->str_filename_len);
    default:
      usage(argv[0]);
      break;
    }
  }

  // Remaining command-line arguments (not needed)
  *argc -= optind;
  argv += optind;
  
  if ((nflags == 0) && (tflags == 0)) {
    fprintf(stderr, "%s\n", ERR_00);
    free_options(opts);
    return -1;
  } else if ((nflags > 1) && (tflags == 0)) {
    fprintf(stderr, "%s\n", ERR_10);
    free_options(opts);
    return -1;
  } else if ((nflags == 0) && (tflags > 1)) {
    fprintf(stderr, "%s\n", ERR_01);
    free_options(opts);
    return -1;
  } else if ((nflags > 1) && (tflags > 1)) {
    fprintf(stderr, "%s\n", ERR_11);
    free_options(opts);
    return -1;
  } else if (nflags == 0) {
    fprintf(stderr, "%s\n", ERR_0X);
    free_options(opts);
    return -1;
  } else if (nflags > 1) {
    fprintf(stderr, "%s\n", ERR_1X);
    free_options(opts);
    return -1;
  } else if (tflags == 0) {
    fprintf(stderr, "%s\n", ERR_X0);
    free_options(opts);
    return -1;
  } else if (tflags > 1) {
    fprintf(stderr, "%s\n", ERR_X1);
    free_options(opts);
    return -1;
  }

  return 0;
}

int get_real_options(options_st *opts)
{
  int ret;
  
  if ((ret = get_real_nums(opts)) == -1) {
    return -1;
  }

  if ((ret = get_real_total(opts)) == -1) {
    return -1;
  }

  if ((ret = get_real_mathops(opts)) == -1) {
    return -1;
  }

    if ((ret = get_real_filename(opts)) == -1) {
    return -1;
  }
  
  return 0;
}

int get_real_nums(options_st *opts)
{
  // Create opts->nums structure
  opts->nums_len = count_numbers(opts->str_nums);
  opts->nums = malloc(opts->nums_len * sizeof(long));
  memset(opts->nums, 0, opts->nums_len * sizeof(long));
  
  // Make sure that the first and last character of opts->str_nums is a digit
  // (a comma cannot appear at any one of both ends of the string)
  char ch = *opts->str_nums;
  if ((!isdigit(ch)) && (ch != '+') && (ch != '-')) {
    fprintf(stderr, "%s %s\n", ERR_FIRST_NUMS, opts->str_nums);
    free_options(opts);
    return -1;
  }

  ch = *(opts->str_nums + (opts->str_nums_len - 1));
  if (!isdigit(ch)) {
    fprintf(stderr, "%s %s\n", ERR_LAST_NUMS, opts->str_nums);
    free_options(opts);
    return -1;
  }
  
  // We've already tested the first and last character, so we begin from the
  // second.
  // Digits  and commas are permitted.
  // Furthermore, positive and negagive signs are permitted:
  // - As a first character of the string.
  // - As a character following a comma.
  // No zeros are allowed.

  // Make sure that opts->str_nums has only digits, commas or '+' or '-' signs
  char *pstr = opts->str_nums;
  for (size_t i = 1; i < opts->str_nums_len - 1; i++) {
    ch = pstr[i];
    if ((!isdigit(ch)) && (ch != ',') && (ch != '+') && (ch != '-')) {
      fprintf(stderr, "%s: %c in %s\n", ERR_CHAR_NUMS, ch, opts->str_nums);
      free_options(opts);
      return -1;
    }
  }

  // Search for '+' and '-' signs
  for (size_t i = 1; i < opts->str_nums_len; i++) {
    ch = pstr[i];
    if (((ch == '+') || (ch == '-')) && pstr[i] != ',') {
      fprintf(stderr, "%s: %c in %s\n", ERR_SIGN_NUMS, ch, opts->str_nums);
      free_options(opts);
      return -1;
    } 
  }

  long *p = opts->nums;
  //Convert the list of strings to numbers
  // Make a copy of opts->str_nums
  // extracting tokens from the string, changes the string.
  char *str_nums_copy = malloc(1 + opts->str_nums_len);
  strncpy(str_nums_copy, opts->str_nums, opts->str_nums_len);
  char *rest = str_nums_copy;
  char *token;
  while ((token = strtok_r(rest, ",", &rest))) {
    pstr = token;
    if ((*pstr == '+') || (*pstr == '-')) {
      pstr++;
    }
    while ((ch = *pstr++) != '\0') {
      if (!isdigit(ch)) {
	fprintf(stderr, "%s: %s\n", ERR_NUMS, token);
	free_options(opts);
	free(str_nums_copy);
	return -1;
      }
    }
    *p++ = atol(token);
  }
  free(str_nums_copy);

  // No zeros allowed
  for (size_t i = 0; i < opts->nums_len; i++) {
    if (opts->nums[i] == 0) {
      fprintf(stderr, "%s\n", ERR_ZERO_NUMS);
    }
  }

  return 0;
}

int get_real_total(options_st *opts)
{
  char *pstr;
  char ch;
  // Convert 'str_total' to long, provided it contains only digits,
  // although it can start with '+' and '-', as well as digits
  pstr = opts->str_total;
  if ((*pstr == '-') || (*pstr == '+')) {
    pstr++;
  }
  
  while ((ch = *pstr++) != '\0') {
    if (!isdigit(ch)) {
      fprintf(stderr, "%s: %s\n", ERR_TOTAL, opts->str_total);
      free_options(opts);
      return -1;
    }
  }
  opts->total = atol(opts->str_total);

  return 0;
}

int get_real_mathops(options_st *opts)
{
  char *pstr;
  char ch;    
  // Check opts->str_mathops.
  pstr = opts->str_mathops;
  if (pstr != NULL) {
    char *pstr2;
    char ch2;
    int i;
    while ((ch = *pstr++) != '\0') {
      // ch character must be one of valid_mathops
      i = find_string(valid_mathops, ch);
      if (i == -1) {
	fprintf(stderr, "%s: %c\n", ERR_INVALID_OP, ch);
	free_options(opts);
	return -1;
      }
      // ch is a valid mathop
      // ch must not be more than once in opts->str_mathops
      pstr2 = pstr;
      while ((ch2 = *pstr2++) != '\0') {
	if (ch == ch2) {
	  fprintf(stderr, "%s: %c\n", ERR_REPEATED_OP, ch);
	  free_options(opts);
	  return -1;
	}
      }
    }
  }
  
  // All valid mathops in opts->mathops in case the user does not specify them
  if (opts->str_mathops == NULL) {
    opts->mathops = malloc(1 + strlen(valid_mathops));
    strncpy(opts->mathops, valid_mathops, strlen(valid_mathops));
  } else {
    opts->mathops = malloc(1 + opts->str_mathops_len);
    strncpy(opts->mathops, opts->str_mathops, opts->str_mathops_len);
  }
  opts->mathops_len = strlen(opts->mathops);  
  
  return 0;
}

int get_real_filename(options_st *opts)
{
  // Check whether the user asked for a particular file name or not
  if (opts->str_filename_len == 0) {
    opts->filename = file_with_timestamp(base_filename, base_extension);
  }
  opts->filename_len = strlen(opts->filename);

  return 0;
}

/*
 Returns the current time.
*/
char *file_with_timestamp(char *name, char *ext)
{
  char *filename = malloc(1 + (strlen(name) + sizeof(char) * 16 + strlen(ext)));
  time_t ltime = time(NULL);
  struct tm *tm;
  tm = localtime(&ltime);

  sprintf(filename, "%s%04d%02d%02d%02d%02d%02d%s", name, tm->tm_year+1900,
	  tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, ext);
  
  return filename;
}

void usage(char *progname) {
  if (strlen(progname) == 1) {
    fprintf(stderr, "%s %s\n", ERR_PROGNAME, progname);
  }
  printf("%s %s %s %s\n", MSG_USAGE_1, progname, MSG_USAGE_2, MSG_USAGE_3);
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
  printf("[");
  for (size_t i = 0; i < nums_len; i++) {
    printf("%ld", nums[i]);
    if (i != nums_len - 1) {
      printf(",");
    }
  }
  printf("]");
}

void print_mathops(char *mathops)
{
  printf("%s\n", mathops);
}

int print_options_summary(options_st *opts)
{
  printf("Numbers count: %zu\n", opts->nums_len);
  printf("Numbers: ");
  for (size_t i = 0; i < opts->nums_len; i++) {
    printf("%ld ", *(opts->nums + i));
  }
  printf("\n");
  printf("Total: %ld\n", opts->total);

  return 0;
}

void free_options(options_st *opts)
{
  free(opts->str_nums);
  free(opts->str_total);
  free(opts->str_mathops);
  free(opts->nums);
  free(opts->mathops);
}

