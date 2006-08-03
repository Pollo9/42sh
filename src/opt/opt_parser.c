/*
** opt_parser.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 03:28:26 2006 Seblu
** Last update Thu Aug  3 05:22:32 2006 Seblu
*/

#include <stdio.h>
#include "opt.h"
#include "../common/common.h"

/*!
** Parse the command line
**
** @param argc program argc
** @param argv program argv
** @param opt shell opt structure to set with options
*/
void opt_parser(int argc, char **argv, ts_opt *opt)
{
#ifdef DEBUG42
  printf("* Option Parser\n");
#endif
  if (argc == 1)
    return;
  for (int i = 1; i < argc; ++i)
    {
#ifdef DEBUG42
      printf("argv[%d]=%s\n", i, argv[i]);
#endif
      const char *copt = argv[i];
      if (*copt == '-')
	{
	  if (copt[1] == 'c')
	    {
	      opt->command = strvmerge((const char**)argv + i + 1);
#ifdef DEBUG42
	      printf("option c: %s\n", opt->command);
#endif
	      break;
	    }
	}
    }
}
