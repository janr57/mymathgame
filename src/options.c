/*
 * options.c
 * Deal with the options which are input from the user.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "options.h"

/*
 * getstropts
 * Arguments:
 * pargc <- Pointer to the 'argc' number of arguments passed to the program.
 * argv <- Actual array of arguments passed to the program.
 * optsstrnums -> String of numbers separated by commas.
 *            The numbers we want to add/substract/multiply/divide.
 * strtotal-> String number.
 *            The result of the basic operations on the numbers in strnums.
 * Returns:
 * -1: error
 *  0: Ok
 */
int getstropts(int *pargc, char **argv, str_options *opts)
{
  /* Expect at least four arguments */
  if (*pargc != 5) {
    usage(argv[0]);
  }

  int nflags = 0, tflags = 0;
  int ch;

  while ((ch = getopt(*pargc, argv, "n:t:")) != -1) {
    switch (ch) {
    case 'n':
      nflags++;
      opts->strnums = malloc(1 + strlen(optarg));	
      strncpy(opts->strnums, optarg, strlen(optarg));
      break;
    case 't':
      tflags++;
      opts->strtotal = optarg;
      break;
    default:
      usage(argv[0]);
    }
  }
  *pargc -= optind;
  argv += optind;
  
  if ((nflags == 0) && (tflags == 0)) {
    fprintf(stderr, "%s\n", ERR_00);
    return -1;
  } else if ((nflags > 1) && (tflags == 0)) {
    fprintf(stderr, "%s\n", ERR_10);
    return -1;
  } else if ((nflags == 0) && (tflags > 1)) {
    fprintf(stderr, "%s\n", ERR_01);
    return -1;
  } else if ((nflags > 1) && (tflags > 1)) {
    fprintf(stderr, "%s\n", ERR_11);
    return -1;
  } else if (nflags == 0) {
    fprintf(stderr, "%s\n", ERR_0X);
    return -1;
  } else if (nflags > 1) {
    fprintf(stderr, "%s\n", ERR_1X);
    return -1;
  } else if (tflags == 0) {
    fprintf(stderr, "%s\n", ERR_X0);
    return -1;
  } else if (tflags > 1) {
    fprintf(stderr, "%s\n", ERR_X1);
    return -1;
  }

  return 0;
}

int get_nums_total(str_options *opts)
{
  //int errcode;

  opts->numcount = count_numbers(opts->strnums);
  opts->pnums = malloc(opts->numcount * sizeof(long));

  /* Convert the list of strings to numbers */
  int len = strlen(opts->strnums);
  char *strcopy = malloc(len + 1);
  strncpy(strcopy, opts->strnums, len);
  char *token;
  char *rest = strcopy;

  /* Fill the opts->pnums array provided 'strnums' has only digits and commas*/
  
  char ch;
  char *pstr;
  long *p = opts->pnums;
  pstr = opts->strnums;
  ch = *opts->strnums;
  if (!isdigit(ch)) {
    fprintf(stderr, "%s %s\n", ERR_FIRST_NUMS, opts->strnums);
  }

  for (int i = 0; i < len; i++) {
    ch = *pstr;
    if ((!isdigit(ch) && (ch != ','))) {
      fprintf(stderr, "%s: %c in %s\n", ERR_CHAR_NUMS, ch, opts->strnums);
    }
  }
  
  while ((token = strtok_r(rest, ",", &rest))) {
    pstr = token;
    while ((ch = *pstr++) != '\0') {
      if (!isdigit(ch)) {
	fprintf(stderr, "%s: %s\n", ERR_NUMS, token);
	return -1;
      }
    }
    *p++ = atol(token);
  }

  pstr = opts->strtotal;
  // Convert 'strtotal' to long, provided it contains only digits
  while ((ch = *pstr++) != '\0') {
    if (!isdigit(ch)) {
      fprintf(stderr, "%s: %s\n", ERR_TOTAL, opts->strtotal);
      return -1;
    }
  }
  opts->total = atol(opts->strtotal);

  return 0;
}

int usage(char *progname) {
  if (strlen(progname) == 1) {
    fprintf(stderr, "%s %s\n", ERR_PROGNAME, progname);
    return -1;
  }

  printf("%s %s %s\n", MSG_USAGE_1, progname, MSG_USAGE_2);

  return 0;
}

int count_numbers(char *string)
{
// Count comma character occurrences in string
  int len = strlen(string);
  int nums = 1;
  for (int i = 1; i < len; i++) {
    if (string[i] == ',') {
      nums++;
    }
  }
  
  return nums;
}

void free_opts_memory(str_options *opts)
{
  free(opts->strnums);
  free(opts->strtotal);
  free(opts->pnums);  
}


