/*
 * options.h
 */

#ifndef OPTIONS_H___
#define OPTIONS_H___

static const char *ERR_PROGNAME = "Invalid program name: %s.";
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

typedef struct options {
	char *strnums;
	char *strtotal;
	long **nums;
	long total;
} str_options;

int getstropts(int *pargc, char **argv, str_options *opts);
int usage(char *progname);

#endif /* OPTIONS_H___ */

