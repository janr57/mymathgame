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
  int result;

  // Get 'opts.strnums' and 'opts.strtotal' from the program arguments.
  if ((result = getstropts(&argc, argv, &opts)) == -1) {
    return -1;
  }

  printf("Numbers: %s\n", opts.strnums);
  printf("Total: %s\n", opts.strtotal);
  
  return 0;
}

