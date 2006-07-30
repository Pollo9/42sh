/*
** opt.h for 42sh
**
** Made by Seblu
** Login  <seblu@epita.fr>
**
** Started on  Tue Mar 21 18:50:03 2006 Seblu
** Last update Sun Jul 30 03:51:48 2006 Seblu
*/

#ifndef OPT_H_
# define OPT_H_

#define NBR_OPT 8

typedef struct
{
  signed char	item[NBR_OPT];
  char		*command;
} ts_opt;

ts_opt *opt_init(void);
void opt_parser(int argc, char *argv[], ts_opt *opt);
int opt_set(const char *name, ts_opt *shopt);
int opt_unset(const char *name, ts_opt *shopt);
int opt_isset(const char *name, const ts_opt *shopt);
const char **opt_get(void);

#endif /* ! OPT_H_ */
