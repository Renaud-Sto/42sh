/*
** set_env.c for set_env in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Sat May 28 19:38:28 2016 
** Last update Mon Jun  6 01:20:19 2016 
*/

#include		"42sh.h"

int			check_env(t_plist *plist, char **cmd)
{
  t_list	        *tmp;

  tmp = plist->begin;
  while (my_strcmp(tmp->name, cmd[1]) != 0)
    {
      tmp = tmp->next;
      if (tmp == NULL)
	return (-1);
    }
  free(tmp->data);
  tmp->data = my_strdup(cmd[2]);
  return (0);
}

int			check_env_nothing(t_plist *plist, char **cmd)
{
  t_list		*tmp;

  tmp = plist->begin;
  while (tmp && my_strcmp(tmp->name, cmd[1]) != 0)
    {
      tmp = tmp->next;
      if (tmp == NULL)
        return (-1);
    }
  free(tmp->data);
  tmp->data = NULL;
  return (0);
}

int			set_env_nothing(t_plist *plist, char **cmd)
{
  char			*new_env;

  new_env = NULL;
  if (check_env_nothing(plist, cmd) == -1)
    {
      new_env = my_strcat(new_env, cmd[1], -1, -1);
      new_env = my_strcat(new_env, "=", -1, -1);
      env_to_list(plist, new_env);
    }
  free(new_env);
  return (0);
}

int			set_env(t_plist *plist, char **cmd, char **env)
{
  char			*new_env;

  (void)env;
  new_env = NULL;
  if (cmd[1] == NULL)
    {
      show_list(plist, NULL, NULL);
      return (0);
    }
  if (cmd[2] == NULL)
    return (set_env_nothing(plist, cmd));
  if (check_env(plist, cmd) == -1)
    {
      new_env = my_strcat(new_env, cmd[1], -1, -1);
      new_env = my_strcat(new_env, "=", -1, -1);
      new_env = my_strcat(new_env, cmd[2], -1, -1);
      env_to_list(plist, new_env);
    }
  free(new_env);
  return (0);
}
