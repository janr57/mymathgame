/*
 * mymathgame.c
 * Get a certain number by doing any + - * / operation on some others,
 * produced by the user.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "algorithms.h"
#include "options.h"
#include "jobs.h"

void fill_mathgame_struct(mathgame_st *mg, options_st *opts)
{
  mg->total = opts->total;
  mg->nums = opts->nums;
  mg->mathops = opts->mathops;
  mg->filename = opts->filename;
  mg->nums_len = opts->nums_len;
  mg->mathops_len = opts->mathops_len;
  mg->filename_len = opts->filename_len;
}

int main(int argc, char **argv)
{
  options_st opts;
  int retcode;
  // Deal with options passed as program arguments
  if ((retcode = get_options(&argc, argv, &opts)) == -1) {
    return -1;
  }
  print_options_summary(&opts);

  // Build and run actual calculations
  mathgame_st mg;
  fill_mathgame_struct(&mg, &opts);
  if ((retcode = produce_jobs(&mg)) == -1) {
    return -1;
  }

  free_options(&opts);
  
  return 0;
}


