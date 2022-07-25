/*
 * freqtable.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "algorithms.h"
#include "freqtable.h"

int main(int argc, char **argv)
{
  /* Expect two arguments */
  if (argc != 5) {
    usage(argv[0]);
    return -1;
  }

  int fflags = 0;
  int oflags = 0;
  size_t input_len = 0;
  size_t output_len = 0;
  char *input_file = NULL;
  char *output_file = NULL;
  FILE *fin = NULL;
  FILE *fout = NULL;
  int ch;

  while ((ch = getopt(argc, argv, "f:o:")) != -1) {
    switch (ch) {
      case 'f':
	fflags ++;
	input_len = strlen(optarg);
	input_file = malloc(1 + input_len);
	strncpy(input_file, optarg, input_len);
	printf("Input file: %s\n", input_file);
	fin = fopen(input_file, "r");
	break;
      case 'o':
	oflags ++;
	output_len = strlen(optarg);
	output_file = malloc(1 + output_len);
	strncpy(output_file, optarg, output_len);
	printf("Output file: %s\n", output_file);
	fout = fopen(output_file, "w");
	break;
    default:
      usage(argv[0]);
      break;
    }
  }

  // Remaining command-line arguments (not needed)
  argc -= optind;
  argv += optind;
  
  if ((fin == NULL) && (fout == NULL)) {
    fprintf(stderr, "Error: Both files unreadable.\n");
    return -1;
  } else if (fin == NULL) {
    fprintf(stderr, "Error, input file is unreadable.\n");
    fclose(fout);
    return -1;
  } else if (fout == NULL) {
    fprintf(stderr, "Error, output file is unreadable.\n");
    fclose(fin);
    return -1;
  }
  
  char str1[20], str2[20], str3[20], str4[20], str5[20];
  for (size_t i = 0; i < 20; i++) {
    str1[i] = str2[i] = str3[i] = str4[i] = str5[i] = '\0';
  }
  // Read header
  fscanf(fin, "%s\t%s\t%s\t%s\t%s\n", str1, str2, str3, str4, str5);
  // Count registers whose 'result' field is an integer
  size_t count = 0;
  int pos = -1;
  while (!feof(fin)) {
    fscanf(fin, "%s\t%s\t%s\t%s\t%s\n", str1, str2, str3, str4, str5);
    if ((pos = find_string(str5, '.')) == -1) {
      count++;
    }
  }

  printf("Count: %lu\n", count);
  long *results = malloc(count * sizeof(long));
  memset(results, 999999999, count * sizeof(long));
  long *nums = malloc(count * sizeof(long));
  memset(nums, 999999999, count * sizeof(long));
  long *stats = malloc(count * sizeof(long));
  memset(stats, 0, count * sizeof(long));

  size_t i = 0;
  rewind(fin);
  // Read header
  fscanf(fin, "%s\t%s\t%s\t%s\t%s\n", str1, str2, str3, str4, str5);
  while (!feof(fin)) {
    fscanf(fin, "%s\t%s\t%s\t%s\t%s\n", str1, str2, str3, str4, str5);
    if ((pos = find_string(str5, '.')) == -1) {
      results[i++] = atol(str5);
    }
  }

  first_lnums_permutation(results, count);  

  size_t index = 0;
  long prev_num = results[index];
  nums[index] = prev_num;
  stats[index] = 1;
  for (size_t i = 1; i < count; i++) {
    if (results[i] == prev_num) {
      stats[index]++;
    } else {
      index++;
      prev_num = results[i];
      nums[index] = prev_num;
      stats[index] = 1;
    }
  }

  i = 0;
  count = 0;
  while (stats[i] != 0) {
    i++;
    count++;
  }

  printf("Stats table len: %lu\n", count);

  for (size_t i = 0; i < count; i++) {
    if (stats[i] != 0) {
      fprintf(fout, "%ld\t%zu\n", nums[i], stats[i]);
    }
  }
  
  free(results);
  free(nums);
  free(stats);
  fclose(fin);
  fclose(fout);
  
  return 0;
}

void usage(char *progname)
{
  printf("%s %s %s\n", MSG_USAGE_1, progname, MSG_USAGE_2);
}


