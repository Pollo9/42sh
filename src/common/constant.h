/*
** constant.h for 42sh
**
** Made by Seblu
** Login   <Seblu@epita.fr>
**
** Started on  Fri Aug 25 03:39:03 2006 Seblu
** Last update Tue Aug 29 00:31:01 2006 Seblu
*/

#ifndef CONSTANT_H_
# define CONSTANT_H_

typedef enum error
  {
    ERROR_PARSE = 258,
    ERROR_FORK = 128,
    ERROR_REDIR = 1,
    ERROR_MEM = 42,
  } e_error;

typedef enum prompt {
  PROMPT_PS1 = 1,
  PROMPT_PS2 = 2,
  PROMPT_PS4 = 4
} e_prompt;

#endif
