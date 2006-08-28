/*
** getoptions.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 03:28:26 2006 Seblu
** Last update Tue Aug 29 00:54:37 2006 Seblu
*/

#include <stdio.h>
#include "option.h"
#include "../common/common.h"

/*!
** Parse the command line
**
** @param argc program argc
** @param argv program argv
** @param opt shell opt structure to set with options
*/
void getoptions(s_options *opt, int argc, char **argv)
{
#if DEBUG_OPTION == 1
  printf("* Option Parser\n");
#endif
  if (argc == 1)
    return;
  for (int i = 1; i < argc; ++i)
    {
#if DEBUG_OPTION == 1
      printf("argv[%d]=%s\n", i, argv[i]);
#endif
      const char *copt = argv[i];
      if (*copt == '-')
	{
	  if (copt[1] == 'c')
	    {
	      opt->command = strvmerge((const char**)argv + i + 1);
#if DEBUG_OPTION == 1
	      printf("option c: %s\n", opt->command);
#endif
	      break;
	    }
	}
    }
}