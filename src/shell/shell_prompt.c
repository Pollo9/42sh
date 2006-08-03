/*
** shell_prompt.c for 42sh in /home/seblu
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 02:27:59 2006 Seblu
** Last update Thu Aug  3 11:10:46 2006 Seblu
*/

#include <stdio.h>
#include <string.h>
#include "shell.h"

static char prompt[80];

/*!
** Return a prompt given by PS1, PS2, PS4 or the default if not set
**
** @param type
**
** @return
*/
const char *get_prompt(te_prompt_type pty)
{
  //fixme
  if (pty == TYPE_PS1) {
    strncpy(prompt, shell->name, 78);
    strcpy(prompt + strlen(shell->name), "$ ");
  }
  else if (pty == TYPE_PS2)
    strcpy(prompt, "> ");
  else if (pty == TYPE_PS4)
    return strcpy(prompt, "");
  return prompt;
}
