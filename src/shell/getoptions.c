/*
** getoptions.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 03:28:26 2006 Seblu
** Last update Mon Sep 25 02:52:45 2006 Seblu
*/

#include <stdio.h>
#include <string.h>
#include "option.h"
#include "shell.h"
#include "../common/common.h"

/*!
** Parse the command line
**
** @param argc program argc
** @param argv program argv
** @param opt shell opt structure to set with options
*/
void	getoptions(s_options *opt, int argc, char **argv)
{
#if DEBUG_OPTION == 1
  printf("* Option Parser\n");
#endif
  if (argc == 1)
    return;
  for (int i = 1; i < argc; ++i) {
#if DEBUG_OPTION == 1
    printf("argv[%d]=%s\n", i, argv[i]);
#endif
    const char *copt = argv[i];
    if (!strcmp(copt, "-c") || !strcmp(copt, "--command")) {
      opt->command = strvmerge((const char**)argv + i + 1);
#if DEBUG_OPTION == 1
      printf("option c: %s\n", opt->command);
#endif
      break;
    }
    else if (!strcmp(copt, "--ast-print"))
      option_set(shell->options, "ast_print");
    else {
      printf("Error: Invalid option %s\n", copt);
      exit(1);
    }
  }
}
