/*
** exec_pipe.c for 42sh in /home/seblu/devel/c/42sh/src/execution
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Apr 12 01:52:31 2006 Seblu
** Last update Sat Apr 15 08:43:26 2006 Seblu
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include "execution.h"
#include "../ast/ast.h"
#include "../builtin/builtin.h"

#include "mem.h"

struct			s_pipeline
{
  int			count;
  int			last;
  pid_t			*list;
};

void			exec_piped_cmd(struct s_cmd *node, struct s_42sh *sh);
static void		init_pipeline(struct s_pipeline *pipeline);
static void		push_pid(struct s_pipeline *ls, pid_t new);
static pid_t		pop_pid(struct s_pipeline *ls);

static void		wait_controler(struct s_pipeline	*pipeline,
				       struct s_42sh		*sh,
				       int			killer);
static int		exec_pipeline(struct s_pipeline		*pipeline,
				      struct s_op		*node,
				      struct s_42sh		*sh);
static pid_t		exec_left_hand(int			p[2],
				       struct s_ast		*left,
				       struct s_pipeline	*pipeline,
				       struct s_42sh		*sh);
static pid_t		exec_right_hand(int			p[2],
					struct s_ast		*right,
					struct s_pipeline	*pipeline,
					struct s_42sh		*sh);


static const int	PIPE_ERROR = 128;

/*!
** Execute a pipe node
**
** @param node ast node pipe
** @param sh shell structure
*/
void			exec_pipe(struct s_op *node, struct s_42sh *sh)
{
  int			ret;
  struct s_pipeline	pipeline;

  assert(node && sh);
  init_pipeline(&pipeline);
  if (!(ret = exec_pipeline(&pipeline, node, sh)))
  {
    perror("42sh");
    sh->last_status = PIPE_ERROR;
  }
  wait_controler(&pipeline, sh, !ret);
  free(pipeline.list);
}

/*!
** Execute a pipe sequence
**
** @param pipeline pipeline info
** @param node pipe node to execute
** @param sh shell struct info
**
** @return 0 if pipe fail, else 1
*/
static int		exec_pipeline(struct s_pipeline		*pipeline,
				      struct s_op		*node,
				      struct s_42sh		*sh)
{
  int			p[2];
  pid_t			pid;
  int			save;
  int			ret;

  if (pipe(p))
    return 0;
  if ((pid = exec_right_hand(p, node->right, pipeline, sh)) < 0)
    return 0;
  if (node->left->type == T_PIPE)
  {
    save = dup(STDOUT_FILENO);
    dup2(p[1], STDOUT_FILENO);
    close(p[1]);
    ret = exec_pipeline(pipeline, &node->left->data.node_op, sh);
    dup2(save, STDOUT_FILENO);
    close(save);
    return ret;
  }
  return (exec_left_hand(p, node->left, pipeline, sh) < 0) ? 0 : 1;
}

/*!
** Wait process exit status
**
** @param pipeline the pipeline of process id
** @param sh  shell struct
** @param killer if true, destroy all open process
*/
static void		wait_controler(struct s_pipeline	*pipeline,
				       struct s_42sh		*sh,
				       int			killer)
{
  int			status;
  pid_t			pid;

  if (!killer)
  {
    pid = pop_pid(pipeline);
    waitpid(pid, &status, 0);
    status = WEXITSTATUS(status);
    sh->last_status = WEXITSTATUS(status);
  }
  while ((pid = pop_pid(pipeline)) != -1)
  {
    kill(pid, SIGPIPE);
    waitpid(pid, &status, 0);
    status = WEXITSTATUS(status);
  }
}

/*!
** Execute a command reader on the pipe
**
** @param p the pipe
** @param right command to execute
** @param pipeline pipeline information
** @param sh shell structure
**
** @return pid for father, exit with last_status for the son
*/
static pid_t		exec_right_hand(int			p[2],
					struct s_ast		*right,
					struct s_pipeline	*pipeline,
					struct s_42sh		*sh)
{
  int			pid;

  if ((pid = fork()) == -1)
    return -1;
  if (pid)
  {
    close(p[0]);
    push_pid(pipeline, pid);
    return pid;
  }
  dup2(p[0], STDIN_FILENO);
  close(p[1]);
  if (right->type == T_CMD)
    exec_piped_cmd(&right->data.node_cmd, sh);
  else
    exec_node(right, sh);
  exit(sh->last_status);
  return pid;
}

/*!
** Execute a command writer on the pipe
**
** @param p the pipe
** @param left command to execute
** @param pipeline pipeline information
** @param sh shell structure
**
** @return pid for father, exit with last_status for the son
*/
static pid_t		exec_left_hand(int			p[2],
				       struct s_ast		*left,
				       struct s_pipeline	*pipeline,
				       struct s_42sh		*sh)
{
  int			pid;

  if ((pid = fork()) == -1)
    return -1;
  if (pid)
  {
    close(p[1]);
    push_pid(pipeline, pid);
    return pid;
  }
  dup2(p[1], STDOUT_FILENO);
  close(p[0]);
  if (left->type == T_CMD)
    exec_piped_cmd(&left->data.node_cmd, sh);
  else
    exec_node(left, sh);
  exit(sh->last_status);
  return pid;
}

/*!
** Initialize a pipeline structure
**
** @param pipeline pipele struct to init
*/
static void		init_pipeline(struct s_pipeline *pipeline)
{
  assert(pipeline);
  pipeline->count = 0;
  pipeline->last = -1;
  pipeline->list = NULL;
}

/*!
** Push an pid to the pipeline
**
** @param pipeline list of pid
** @param new new pid to add
*/
static void		push_pid(struct s_pipeline *pipeline, pid_t new)
{
  assert(pipeline);
  if (new < 0)
    return;
  secrealloc(pipeline->list, pipeline->list, ++pipeline->count * sizeof (pid_t));
  pipeline->list[pipeline->count - 1] = new;
}

/*!
** Pop the first pid pushed (FILE)
**
** @param pipeline pipeline
**
** @return the first pid pushed
*/
static pid_t		pop_pid(struct s_pipeline *pipeline)
{
  assert(pipeline);
  if (pipeline->count <= 0 || pipeline->last + 1 >= pipeline->count)
    return -1;
  return pipeline->list[++pipeline->last];
}
