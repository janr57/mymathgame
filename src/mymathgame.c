/*
 * mymathgame.c
 * Get a certain number by doing any + - * / operation on some others.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "options.h"
#include "mathops.h"

int main(int argc, char **argv)
{
  str_Options opts;
  int errcode;

  /* Deal with options passed as program arguments */
  if ((errcode = get_options(&argc, argv, &opts)) == -1) {
    return -1;
  }
  print_options_summary(&opts);

  if ((errcode = try_mathops(opts.total, opts.numslen, opts.nums)) == -1) {
    return -1;
  }
  
  return 0;
}
