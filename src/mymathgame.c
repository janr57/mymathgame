/*
 * mymathgame.c
 * Get a certain number by doing any + - * / operation on some others.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "algorithms.h"
#include "options.h"
#include "jobs.h"

void fill_mathgame_struct(mathgame_t *mg, options_t *opts)
{
  mg->total = opts->total;
  mg->nums = opts->nums;
  mg->mathops = opts->mathops;
  mg->nums_len = opts->nums_len;
  mg->mathops_len = opts->mathops_len;
}

int main(int argc, char **argv)
{
  options_t opts;
  int retcode;
  /* Deal with options passed as program arguments */
  if ((retcode = get_options(&argc, argv, &opts)) == -1) {
    return -1;
  }
  print_options_summary(&opts);

  mathgame_t mg;
  fill_mathgame_struct(&mg, &opts);
  if ((retcode = produce_jobs(&mg)) == -1) {
    return -1;
  }

  //free_mathgame(&mg);
  free_options(&opts);
  
  return 0;
}

