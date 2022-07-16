/*
 * options.h
 */

#ifndef OPTIONS_H___
#define OPTIONS_H___

static const char *ERR_PROGNAME = "Invalid program name: %s.";
static const char *ERR_TOTAL = "Invalid '-t' option";
static const char *ERR_FIRST_NUMS = "Invalid first number in '-n' option";
static const char *ERR_CHAR_NUMS = "Invalid character in '-n' option string";
static const char *ERR_NUMS = "Invalid '-n' option number";
static const char *ERR_INVALID_OP = "Invalid mathematical operation";
static const char *ERR_REPEATED_OP = "Repeated mathematical operation";
static const char *ERR_00 = "You must use the '-n' and '-t' options.";
static const char *ERR_10 = "You must use the '-n' option only once, "
                            "and one '-t' option.";
static const char *ERR_01 = "You must use the '-t' option only once, "
                            "and one '-n' option.";
static const char *ERR_11 = "You must use both, the '-n' and '-t' "
                            "options only once.";
static const char *ERR_0X = "You must use the '-n' option as well.";
static const char *ERR_1X = "You must use only one '-n' option, apart "
                            "from the '-t' one.";
static const char *ERR_X0 = "You must use the '-t' option as well.";
static const char *ERR_X1 = "You must use only one '-t' option, apart "
                            "from the '-n' one.";

static const char *MSG_USAGE_1 = "Usage example:";
static const char *MSG_USAGE_2 = "-n 1,2,3,4 -t 12";
static const char *MSG_USAGE_3 = "[-o +-x/]";

typedef struct _Options {
  char *str_nums;
  char *str_total;
  char *str_mathops;
  size_t str_nums_len;
  size_t str_total_len;
  size_t str_mathops_len;
  long *nums;
  long total;
  char *mathops;
  size_t nums_len;
  size_t mathops_len;
} strct_options;

static char *valid_mathops = "+-x/";

int get_options(int *pargc, char **argv, strct_options *popts);
int get_str_options(int *pargc, char **argv, strct_options *popts);
int usage(char *progname);
size_t count_numbers(char *string);
int get_real_options(strct_options *popts);
int print_options_summary(strct_options *popts);

#endif /* OPTIONS_H___ */

