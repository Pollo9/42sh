/*
** exec_cmd.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Apr  8 07:38:48 2006 Seblu
** Last update Tue Nov 14 13:50:59 2006 seblu
*/

#define DEBUG_EXEC 0

#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../shell/shell.h"
#include "../ast/ast.h"
#include "exec.h"
#include "../builtin/builtin.h"

/* #define rederror(prompt) do { perror(prompt); return 0; } while (0) */

/* struct			s_reds_context */
/* { */
/*   int			old; */
/*   int			save; */
/*   int			end; */
/* }; */


static int		exec_forked(s_cmd_node *cmd);
static void		exec_argv(char **argv);
static void		exec_prefix(char **prefix, int glob);
static void		cmd_debugger(s_cmd_node *cmd);

void			exec_cmd(s_cmd_node *cmd)
{
  assert(cmd);
  if (DEBUG_EXEC)
    cmd_debugger(cmd);
  //FIXME: expansions here
  if (!cmd->argv) {
    if (cmd->prefix) exec_prefix(cmd->prefix, 0);
    return;
  }
  if (is_a_builtin(cmd->argv[0]))
    shell->status = exec_builtin(cmd);
  else
    shell->status = exec_forked(cmd);
}

static int		exec_forked(s_cmd_node *cmd)
{
  pid_t			pid;
  int			status;

  if ((pid = fork()) == -1) {
    fprintf(stderr, "%s: Cannot fork\n", shell->name);
    return ERROR_FORK;
  }
  if (pid) {
    waitpid(pid, &status, 0);
    return WEXITSTATUS(status);
  }
  if (cmd->prefix)
    exec_prefix(cmd->prefix, 1);
  exec_argv(cmd->argv);
  assert(0);
}

static void		exec_argv(char **argv)
{
  assert(argv && argv[0]);
  execvp(argv[0], argv);
  if (errno == ENOENT)
    if (strchr(argv[0], '/') == NULL)
      fprintf(stderr, "%s: %s: command not found\n", shell->name, argv[0]);
    else
      fprintf(stderr, "%s: %s: No such file or directory\n",
	      shell->name, argv[0]);
  else
    perror(shell->name);
  exit((errno == ENOENT) ? 127 : 126);
}

static void		exec_prefix(char **prefix, int glob)
{
  char			*value;

  assert(prefix);
  for (int i = 0; prefix[i]; ++i) {
    if (!(value = strchr(prefix[i], '=')))
      assert(0);
    *value++ = 0;
    if (glob)
      var_setenv(prefix[i], value, !0);
    else
      var_set(sh->vars, prefix[i], value, !0);
  }
}


/* /\*! */
/* ** Execute a command in a pipeline. This call preserve for too many system call fork */
/* ** Take care, this must be called after a fork */
/* ** */
/* ** @param cmd cmd to execute */
/* ** @param sh sh structure */
/* *\/ */
/* void			exec_piped_cmd(struct s_cmd *cmd, struct s_42sh *sh) */
/* { */
/*   assert(cmd && sh); */
/*   if (DEBUG_EXEC) */
/*      cmd_debugger(cmd); */
/*   word_expansion(&cmd->argv, sh); */
/*   if (!apply_reds(cmd->redirs)) */
/*      exit(RED_ERROR); */
/*   if (is_a_builtin(cmd->argv[0], sh)) */
/*     sh->last_status = exec_builtin(cmd, sh); */
/*   else */
/*   { */
/*     parse_prefix(cmd->prefix, 1, sh); */
/*     launch_cmd(cmd); */
/*   } */
/* } */

/* /\*! */
/* ** Set redirection for builtin */
/* ** */
/* ** @param reds redirection informations */
/* ** */
/* ** @return save of all fd permutations */
/* *\/ */
/* static struct s_reds_context	*save_reds_context(struct s_redir **reds) */
/* { */
/*   struct s_reds_context		*context; */
/*   register int			i; */

/*   for (i = 0; reds[i]; ++i) */
/*     ; */
/*   secmalloc(context, (i + 1) * sizeof (struct s_reds_context)); */
/*   for (i = 0; reds[i]; ++i) */
/*   { */
/*     context[i].old = reds[i]->fd; */
/*     context[i].save = dup(reds[i]->fd); */
/*     context[i].end = 0; */
/*   } */
/*   context[i].end = 1; */
/*   return context; */
/* } */

/* static void		restore_reds_context(struct s_reds_context *context) */
/* { */
/*   register int		i; */

/*   for (i = 0; !context[i].end; ++i) */
/*      dup2(context[i].save, context[i].old); */
/* } */





/* /\*! */
/* ** Apply redirections whitout save of file descriptors */
/* ** */
/* ** @param reds list of redirections */
/* *\/ */
/* static int		apply_reds(struct s_redir **reds) */
/* { */
/*    int			fd; */
/*    int			i; */
/*    char			*filename; */

/*    assert(reds); */
/*    for (i = 0; reds[i]; ++i) */
/*    { */
/*       switch (reds[i]->type) */
/*       { */
/* 	 case R_LESS: */
/* 	    if ((fd = open(reds[i]->file, O_RDONLY)) == -1) */
/* 	       rederror("42sh"); */
/* 	    dup2(fd, reds[i]->fd); */
/* 	    break; */
/* 	 case R_DLESSDASH: */
/* 	 case R_DLESS: */
/* 	    if ((fd = mkstemp(filename = strdup("42sh.heredocs.XXXXXX"))) == -1) */
/* 	       rederror("42sh"); */
/* 	    write(fd, reds[i]->file, strlen(reds[i]->file)); */
/* 	    lseek(fd, 0, SEEK_SET); */
/* 	    unlink(filename); */
/* 	    free(filename); */
/* 	    dup2(fd, STDIN_FILENO); */
/* 	    close(fd); */
/* 	    break; */
/* 	 case R_GREAT: */
/* 	 case R_CLOBBER: */
/* 	    if ((fd = open(reds[i]->file, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) */
/* 	       rederror("42sh"); */
/* 	    dup2(fd, reds[i]->fd); */
/* 	    break; */
/* 	 case R_DGREAT: */
/* 	    if ((fd = open(reds[i]->file, O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1) */
/* 	       rederror("42sh"); */
/* 	    dup2(fd, reds[i]->fd); */
/* 	    break; */
/* 	 case R_GREATAND: */
/* 	 case R_LESSAND: */
/* 	    if ((fd = get_filedes(reds[i]->file)) == -1) */
/* 	       return 0; */
/* 	    if (fd == -2) */
/* 	       close(reds[i]->fd); */
/* 	    else */
/* 	       dup2(fd, reds[i]->fd); */
/* 	    break; */
/* 	 default: */
/* 	    return 0; */
/*       } */
/*    } */
/*    return 1; */
/* } */

/* /\*! */
/* ** Retrieve an fd from and redirect words */
/* ** */
/* ** @param txt fd in string */
/* ** */
/* ** @return -1 if fail, -2 for close fd else fd */
/* *\/ */
/* static int		get_filedes(const char *txt) */
/* { */
/*    long			fd; */
/*    char			*endbuf; */

/*    assert(txt); */
/*    if (txt[0] == '-' && txt[1] == 0) */
/*       return -2; */
/*    fd = strtol(txt, &endbuf, 10); */
/*    if (endbuf == txt || *endbuf != 0) */
/*    { */
/*       fprintf(stderr, "42sh: %s: ambiguous redirect\n", txt); */
/*       return -1; */
/*    } */
/*    if (-1 == fcntl(fd, F_GETFL)) */
/*    { */
/*       endbuf = strmerges(2, "42sh: ", txt); */
/*       perror(endbuf); */
/*       free(endbuf); */
/*       return -1; */
/*    } */
/*    return 0; */
/* } */

/*!
** Debug execution
**
** @param cmd command
*/
static void		cmd_debugger(s_cmd_node *cmd)
{
   int			i;

   fprintf(stderr, "-----------------------------------\n");
   fprintf(stderr, "exec command\n");
   for (i = 0; cmd->argv && cmd->argv[i]; ++i)
      fprintf(stderr, "argv[%d]   : %-15s\n", i, cmd->argv[i]);
   for (i = 0; cmd->prefix && cmd->prefix[i]; ++i)
      fprintf(stderr, "prefix[%d] : %-15s\n", i, cmd->prefix[i]);
/*    for (i = 0; cmd->redirs && cmd->redirs[i]; ++i) */
/*    { */
/*       fprintf(stderr, "reds[%d]   : type : %d\n", i, cmd->redirs[i]->type); */
/*       fprintf(stderr, "            : fd   : %d\n", cmd->redirs[i]->fd); */
/*       fprintf(stderr, "            : file : %s\n", cmd->redirs[i]->file); */
   }
   fprintf(stderr, "-----------------------------------\n");
}
