/*
** option.h for 42sh
**
** Made by Seblu
** Login  <seblu@epita.fr>
**
** Started on  Tue Mar 21 18:50:03 2006 Seblu
** Last update Wed Aug 30 00:19:19 2006 Seblu
*/

#ifndef OPTION_H_
# define OPTION_H_

#define NBR_OPTION 9

#define DEBUG_OPTION 0

typedef struct options
{
  signed char	item[NBR_OPTION];
  char		*command;
} s_options;

/*
** ==============
** FILE: option.c
** ==============
*/

/*!
** Create a new options structure
**
** @return A new options structure
*/
s_options	*option_init(void);

/*!
** Set a shell option
**
** @param shopt structure to apply
** @param name name of the option to set
**
** @return 0 on failure, else 1
*/
int		option_set(s_options *shopt, const char *name);

/*!
** Unset a shell option
**
** @param shopt structure to apply
** @param name name of the option to unset
**
** @return 0 on failure, else 1
*/
int		option_unset(s_options *shopt, const char *name);

/*!
** Tell if an option is set. if option nane is not set return -1
**
** @param shopt structure where find
** @param name name to find
**
** @return 0 if unset, 1 if set and -1 if not exist
*/
int		option_isset(const s_options *shopt, const char *name);

/*!
** Return a list of know opt
**
** @return list of opt
*/
const char	**opt_get();

/*
** =====================
** FILE: getoption.c
** =====================
*/

/*!
** Parse the command line and set options
**
** @param opt shell opt structure to set with options
** @param argc program argc
** @param argv program argv
*/
void		getoptions(s_options *opt, int argc, char **argv);

#endif
