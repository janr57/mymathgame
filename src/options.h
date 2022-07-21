/*
 * options.h
 */

#ifndef OPTIONS_H___
#define OPTIONS_H___

typedef struct _Options {
  char *str_nums;
  char *str_total;
  char *str_mathops;
  char *str_filename;
  size_t str_nums_len;
  size_t str_total_len;
  size_t str_mathops_len;
  size_t str_filename_len;
  long *nums;
  long total;
  char *mathops;
  char *filename;
  size_t nums_len;
  size_t mathops_len;
  size_t filename_len;
} options_t;

static char *valid_mathops = "+-*/";
static size_t max_nums_len = 20;

int get_options(int *pargc, char **argv, options_t *opts);
int get_str_options(int *pargc, char **argv, options_t *opts);
void usage(char *progname);
size_t count_numbers(char *string);
int get_real_options(options_t *opts);
void print_nums(long *nums, size_t nums_len);
void print_mathops(char *mathops);
int print_options_summary(options_t *opts);
void free_options(options_t *opts);

#endif /* OPTIONS_H___ */

