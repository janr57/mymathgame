/*
 * options.h
 */

#ifndef OPTIONS_H___
#define OPTIONS_H___

typedef struct {
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
} options_st;

static char *valid_mathops = "+-*/";
static size_t max_nums_len = 20;

int get_options(int *pargc, char **argv, options_st *opts);
int get_str_options(int *pargc, char **argv, options_st *opts);
int get_real_options(options_st *opts);
int get_real_nums(options_st *opts);
int get_real_total(options_st *opts);
int get_real_mathops(options_st *opts);
int get_real_filename(options_st *opts);
void usage(char *progname);
size_t count_numbers(char *string);

void print_nums(long *nums, size_t nums_len);
void print_mathops(char *mathops);
int print_options_summary(options_st *opts);
void free_options(options_st *opts);

#endif /* OPTIONS_H___ */

