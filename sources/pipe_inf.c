/*
** pipe_inf.c for pipe_inf in /home/gastal_r/rendu/42sh/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Sat Jun  4 22:09:08 2016 
** Last update Mon Jun  6 15:19:59 2016 
*/

#include		"42sh.h"

int			loop_pipe(t_plist *plist, int *in_out, char **cmd, char **env)
{
  pid_t			pid;

  if ((pid = fork ()) == 0)
    {
      if (in_out[0] != 0)
	{
	  dup2(in_out[0], 0);
	  close(in_out[0]);
	}
      if (in_out[1] != 1)
	{
	  dup2(in_out[1], 1);
	  close(in_out[1]);
	}
      return (check_action(cmd, env, plist));
    }
  return (pid);
}

int			init_loop(t_plist *plist, t_cmd *cmd, int n, char **env)
{
  int			i;
  int			fd[2];
  int			in_out[2];

  in_out[0] = 0;
  i = -1;
  while (++i < n -1)
    {
      pipe(fd);
      in_out[1] = fd[1];
      loop_pipe(plist, in_out, cmd->cmd, env);
      cmd = cmd->next;
      close (fd[1]);
      in_out[0] = fd[0];
    }
  if (in_out[0] != 0)
    dup2(in_out[0], 0);
  return (check_action(cmd->cmd, env, plist));
}

int			pipe_inf(t_plist *plist, t_cmd *cmd, int n, char **env)
{
  int			pid;
  int			status;

  plist->pipe = 1;
  if ((pid = fork()) == 0)
    init_loop(plist, cmd, n, env);
  else
    waitpid(pid, &status, 0);
  plist->pipe = 0;
  if (WIFEXITED(status) == 1)
    if (WEXITSTATUS(status))
      return (plist->exit_value = 1);
  return (0);
}
