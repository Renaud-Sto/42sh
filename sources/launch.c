/*
** launch.c for 42 in
**
** Made by Juliani Renaud
** Login   <julian_r@epitech.net>
**
** Started on  Sat May 28 16:01:27 2016 Juliani Renaud
** Last update	Fri Jun 03 14:15:54 2016 Full Name
*/

#include	"42sh.h"

void		move_tmp(t_cmd **tmp, int i, t_sep **sep)
{
  if (!(*sep) && *tmp)
    {
      (*tmp) = (*tmp)->next;
      return;
    }
  if (*sep && my_strcmp((*sep)->sep, "&&") == 0)
    {
      (*tmp) = (*tmp)->next;
       if ((*tmp) && i != 0)
      	(*tmp) = (*tmp)->next;
    }
  else if (*sep && my_strcmp((*sep)->sep, "||") == 0)
    {
      (*tmp) = (*tmp)->next;
      if ((*tmp) && i == 0)
	(*tmp) = (*tmp)->next;
    }
  else if (*tmp)
    (*tmp) = (*tmp)->next;
  (*sep ? (*sep) = (*sep)->next : 0);
  return ;
}

int		count_pipe(t_sep **sep)
{
  int		i;

  i = 0;
  while ((*sep) && my_strcmp((*sep)->sep, "|") == 0)
    {
      i++;
      (*sep) = (*sep)->next;
    }
  return (i);
}

int		check_nb_arg(int nb_pipe, t_cmd *cmd)
{
  int		i;
  t_cmd		*tmp;

  i = 0;
  tmp = cmd;
  while ((i < (nb_pipe + 1)) && tmp)
    {
      tmp = tmp->next;
      i++;
    }
  if (i == (nb_pipe + 1))
    return (0);
  else
    return (1);
}

int		check_pipe(t_env *env, t_plist *envlist,
			   t_cmd **tmp, t_sep **tmp_sep)
{
  int		nb_pipe;

  if (*tmp_sep != NULL && my_strcmp((*tmp_sep)->sep, "|") == 0)
    if ((*tmp)->next == NULL)
      return (check_invalid_cmd());
  if (*tmp_sep != NULL && (*tmp)->next != NULL
      && my_strcmp((*tmp_sep)->sep, "|") == 0)
    {
      envlist->pipe = 1;
      nb_pipe = count_pipe(tmp_sep);
      if ((check_nb_arg(nb_pipe, *tmp)) == 1)
	return (check_invalid_cmd());
      envlist->exit_value = pipe_inf(envlist, *tmp, nb_pipe + 1, env->env);
      while (nb_pipe-- - 1 >= 0)
      	*tmp = (*tmp)->next;
      return (1);
    }
  return (0);
}

int		launch(t_env *env, t_plist *envlist, t_cmd *tmp, t_sep *tmp_sep)
{
  int		check;

  check = 0;
  while (tmp)
    {
      if (my_strcmp(tmp->cmd[0], "exit") == 0)
	{
	  my_putstr("exit\n");
	  if (tmp->cmd[1] != NULL && tmp->cmd[1][0] >= '0'
	      && tmp->cmd[1][0] <= '9')
	    return (exit_end(envlist, my_getnbr(tmp->cmd[1])));
	  else
	    return (exit_end(envlist, 1));
	}
      if ((check = check_pipe(env, envlist, &tmp, &tmp_sep)) == -1)
	return (0);
      if (check != 1 && tmp_sep != NULL && my_strcmp(tmp_sep->sep, "&") == 0)
	background(envlist, tmp->cmd, env->env);
      else if (check != 1)
	envlist->exit_value = check_action(tmp->cmd, env->env, envlist);
      move_tmp(&tmp, envlist->exit_value, &tmp_sep);
      env->env = init_env(env->env, envlist);
    }
  return (0);
}
