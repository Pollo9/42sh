/*
** constant.h for 42sh
**
** Made by Seblu
** Login   <Seblu@epita.fr>
**
** Started on  Fri Aug 25 03:39:03 2006 Seblu
** Last update Fri Aug 25 07:34:15 2006 Seblu
*/

#ifndef CONSTANT_H_
# define CONSTANT_H_

typedef enum e_error
  {
    ERROR_PARSE = 258,
    ERROR_FORK = 128,
    ERROR_REDIR = 1,
    ERROR_MEM = 42,
  } te_error;

typedef enum e_prompt {
  PROMPT_PS1 = 1,
  PROMPT_PS2 = 2,
  PROMPT_PS4 = 4
} te_prompt;

#endif
