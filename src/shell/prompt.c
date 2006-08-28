/*
** prompt.c for 42sh in /home/seblu
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 02:27:59 2006 Seblu
** Last update Tue Aug 29 00:47:41 2006 Seblu
*/

#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "../common/macro.h"

/*!
** Return a prompt given by PS1, PS2, PS4 or the default if not set
**
** @param type
**
** @return
*/
const char	*get_prompt(e_prompt pty)
{
  static char	prompt[80];
  //fixme
  if (pty == PROMPT_PS1) {
    strncpy(prompt, shell->name, 78);
    strcpy(prompt + strlen(shell->name), "$ ");
  }
  else if (pty == PROMPT_PS2)
    strcpy(prompt, "> ");
  else if (pty == PROMPT_PS4)
    return strcpy(prompt, "");
  return prompt;
}

//todo gestion des variables !
void		show_prompt(e_prompt pty)
{
  char		*prompt;

  if (!isinteractive())
    return;
  switch (pty) {
  case PROMPT_PS1:
    prompt = "42sh ";
    break;
  case PROMPT_PS2:
    prompt = "> ";
    break;
  case PROMPT_PS4:
    prompt = "+";
    break;
  }
  fflush(stderr);
  fprintf(stderr, "%s", prompt);
  fflush(stderr);
}
