/*
** main.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Mon Apr 10 23:57:28 2006 Seblu
** Last update Tue Aug 29 00:53:31 2006 Seblu
*/

#include <stdio.h>
#include <libgen.h>
#include "shell.h"
#include "../ast/ast.h"
#include "../parser/parser.h"
#include "../exec/exec.h"
#include "../common/macro.h"

/*
** Global shell structure
*/
s_shell *shell = NULL;

/*!
** Program entry point
**
** @param argc Argument count
** @param argv Argument vector
**
** @return return program value
*/
int		main(int argc, char *argv[])
{
  s_ast_node	*ast;
  s_parser	*parser;

  // shell initialization
  shell = shell_init(argv[0]);
  // parse argv
  getoptions(shell->options, argc, argv);
  // shell parser init
  parser = parser_init(STDIN_FILENO);
  // parse and execute stdin stream
  do
  {
    ast = parse(parser);
    if (!parser->error)
      exec_node(ast);
    ast_destruct(ast);
  }
  while (!parser->lexer->eof);
  if (!isinteractive())
    fprintf(stderr, "exit\n");
  return shell->status;
}
