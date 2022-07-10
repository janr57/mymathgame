/*
 * mymathgame.c
 * Get a certain number by doing any + - * / operation on some others.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "options.h"

int main(int argc, char **argv)
{
  str_options opts;
  int errcode;

  // Get 'opts.strnums' and 'opts.strtotal' from the program arguments.
  if ((errcode = getstropts(&argc, argv, &opts)) == -1) {
    free_opts_memory(&opts);
    return -1;
  }

  if ((errcode = get_nums_total(&opts)) == -1) {
    free_opts_memory(&opts);
    return -1;
  }

  printf("Count: %d\n", opts.numcount);
  printf("Numbers: ");
  for (int i = 0; i < opts.numcount; i++) {
    printf("%ld ", *(opts.pnums + i));
  }
  printf("\n");
  printf("Total: %ld\n", opts.total);

  return 0;
}
