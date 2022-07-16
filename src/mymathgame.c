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
  strct_options opts;
  int errcode;
  /* Deal with options passed as program arguments */
  if ((errcode = get_options(&argc, argv, &opts)) == -1) {
    return -1;
  }
  print_options_summary(&opts);

  strct_mathgame mg;
  mg.total = opts.total;
  mg.nums = opts.nums;
  mg.mathops = opts.mathops;
  mg.nums_len = opts.nums_len;
  mg.mathops_len = opts.mathops_len;
  if ((errcode = try_mathops(&mg)) == -1) {
    return -1;
  }
  
  return 0;
}

