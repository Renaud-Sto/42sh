/*
** alias_arg.c for alias_arg in /home/gastal_r/rendu/42sh/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Mon Jun  6 17:33:42 2016 
** Last update Mon Jun  6 18:49:34 2016 
*/

#include		"42sh.h"

int			launch_alias(t_plist *plist, char **buff, char **env)
{
  int			i;

  i = -1;
  plist->exit_value = system_fonc(plist, buff, env);
  while (buff[++i])
    free(buff[i]);
  free(buff);
  return (plist->exit_value);
}

int			count_cmd(char **cmd)
{
  int			i;

  i = -1;
  while (cmd[++i]);
  return (i);
}

char			**alias_arg(char **alias, char **cmd)
{
  char			**buff;
  int			i;
  int			j;

  i = -1;
  j = -1;
  cmd++;
  buff = malloc(sizeof(char *) * (count_cmd(alias) + count_cmd(cmd) + 1));
  while (alias[++i])
    buff[i] = my_strdup(alias[i]);
  while (cmd[++j])
    buff[i++] = my_strdup(cmd[j]);
  buff[i] = NULL;
  return (buff);
}
