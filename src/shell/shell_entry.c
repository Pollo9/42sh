/*
** main.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Mon Apr 10 23:57:28 2006 Seblu
** Last update Fri Aug 25 12:24:50 2006 Seblu
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
ts_shell *shell = NULL;

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
  ts_ast_node	*ast;
  ts_parser	*parser;

  // shell initialization
  shell = shell_init(argv[0]);
  // parse argv
  option_parser(shell->options, argc, argv);
  // shell parser init
  parser = parser_init(stdin);
  // parse and execute stdin stream
  do
  {
    ast = parse(parser);
    if (!parser->error)
      exec_ast(ast);
    ast_destruct(ast);
  }
  while (!parser->lexer->eof);
  if (!isinteractive())
    fprintf(stderr, "exit\n");
  return shell->status;
}
