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

int get_options(int *pargc, char **argv, str_Options *popts)
{
  int errcode;
  
  // Get 'opts.strnums' and 'opts.strtotal' from the program arguments.
  if ((errcode = getstropts(pargc, argv, popts)) == -1) {
    return -1;
  }

  if ((errcode = get_nums_total(popts)) == -1) {
    return -1;
  }

  return 0;
}

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
int getstropts(int *pargc, char **argv, str_Options *popts)
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
      popts->strnums = malloc(1 + strlen(optarg));	
      strncpy(popts->strnums, optarg, strlen(optarg));
      break;
    case 't':
      tflags++;
      popts->strtotal = optarg;
      break;
    default:
      usage(argv[0]);
    }
  }
  *pargc -= optind;
  argv += optind;
  
  if ((nflags == 0) && (tflags == 0)) {
    fprintf(stderr, "%s\n", ERR_00);
    free(popts->strnums);
    return -1;
  } else if ((nflags > 1) && (tflags == 0)) {
    fprintf(stderr, "%s\n", ERR_10);
    free(popts->strnums);
    return -1;
  } else if ((nflags == 0) && (tflags > 1)) {
    fprintf(stderr, "%s\n", ERR_01);
    free(popts->strnums);
    return -1;
  } else if ((nflags > 1) && (tflags > 1)) {
    fprintf(stderr, "%s\n", ERR_11);
    free(popts->strnums);
    return -1;
  } else if (nflags == 0) {
    fprintf(stderr, "%s\n", ERR_0X);
    free(popts->strnums);
    return -1;
  } else if (nflags > 1) {
    fprintf(stderr, "%s\n", ERR_1X);
    free(popts->strnums);
    return -1;
  } else if (tflags == 0) {
    fprintf(stderr, "%s\n", ERR_X0);
    free(popts->strnums);
    return -1;
  } else if (tflags > 1) {
    fprintf(stderr, "%s\n", ERR_X1);
    free(popts->strnums);
    return -1;
  }

  return 0;
}

int get_nums_total(str_Options *popts)
{
  //int errcode;

  popts->numcount = count_numbers(popts->strnums);
  popts->pnums = malloc(popts->numcount * sizeof(long));

  /* Convert the list of strings to numbers */




  /* Fill the opts->pnums array provided 'strnums' has only digits and commas*/
  
  char ch;
  char *pstr;
  long *p = popts->pnums;
  pstr = popts->strnums;
  ch = *popts->strnums;
  if (!isdigit(ch)) {
    fprintf(stderr, "%s %s\n", ERR_FIRST_NUMS, popts->strnums);
    free(popts->strnums);
    free(popts->pnums);
    return -1;
  }
  
  int len = strlen(popts->strnums);
  for (int i = 0; i < len; i++) {
    ch = *pstr;
    if ((!isdigit(ch) && (ch != ','))) {
      fprintf(stderr, "%s: %c in %s\n", ERR_CHAR_NUMS, ch, popts->strnums);
      free(popts->strnums);
      free(popts->pnums);
      return -1;
    }
  }

  char *strcopy = malloc(len + 1);
  strncpy(strcopy, popts->strnums, len);
  char *rest = strcopy;
  char *token;
  while ((token = strtok_r(rest, ",", &rest))) {
    pstr = token;
    while ((ch = *pstr++) != '\0') {
      if (!isdigit(ch)) {
	fprintf(stderr, "%s: %s\n", ERR_NUMS, token);
	free(popts->strnums);
	free(popts->pnums);
	free(strcopy);
	return -1;
      }
    }
    *p++ = atol(token);
  }

  pstr = popts->strtotal;
  // Convert 'strtotal' to long, provided it contains only digits
  while ((ch = *pstr++) != '\0') {
    if (!isdigit(ch)) {
      fprintf(stderr, "%s: %s\n", ERR_TOTAL, popts->strtotal);
      free(popts->strnums);
      free(popts->pnums);
      free(strcopy);
      return -1;
    }
  }
  popts->total = atol(popts->strtotal);

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

int print_options_summary(str_Options *popts)
{
  printf("Count: %d\n", popts->numcount);
  printf("Numbers: ");
  for (int i = 0; i < popts->numcount; i++) {
    printf("%ld ", *(popts->pnums + i));
  }
  printf("\n");
  printf("Total: %ld\n", popts->total);

  return 0;
}

