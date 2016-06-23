/*
** alias.c for alias in /home/gastal_r/rendu/42sh/sources
**
** Made by
** Login   <gastal_r@epitech.net>
**
** Started on  Thu Jun  2 01:35:59 2016
** Last update	Fri Jun 03 16:19:01 2016 Full Name
*/

#include		"42sh.h"

char			**test_alias(t_plist *plist, char **cmd)
{
  t_alias		*alias;
  t_alias_cmd		*alias_cmd;

  alias_cmd = plist->begin_acmd;
  while (alias_cmd)
  {
    if (my_strcmp(alias_cmd->alias, cmd[0]) == 0)
      return (alias_arg(alias_cmd->cmd, cmd));
    alias_cmd = alias_cmd->next;
  }
  alias = plist->begin_a;
  if (alias == NULL)
    return (NULL);
  while (my_strcmp(alias->alias, cmd[0]) != 0)
    {
      alias = alias->next;
      if (alias == NULL)
      	return (NULL);
    }
  return (alias_arg(alias->cmd, cmd));
}

void			add_alias(t_plist *list, char *alias, char *cmd)
{
  t_alias               *new;

  new = list->begin_a;
  if (!list)
    return;
  if ((new = malloc(sizeof(t_list))) == NULL)
    return;
  new->alias = my_strdup(alias);
  new->cmd = order_args(my_str_to_wordtab(cmd), -1, 2);
  new->prev = NULL;
  new->next = NULL;
  if (list->begin_a == NULL)
    {
      list->begin_a = new;
      list->end_a = new;
    }
  else
    {
      list->end_a->next = new;
      new->prev = list->end_a;
      list->end_a = new;
    }
}

void			add_alias_cmd_list(t_plist *list, char *alias, char *cmd)
{
  t_alias_cmd           *new;

  if (check_exist(list, alias, cmd) == 1)
    return;
  new = list->begin_acmd;
  if (!list)
    return;
  if ((new = malloc(sizeof(t_list))) == NULL)
    return;
  new->alias = my_strdup(alias);
  new->cmd = order_args(my_str_to_wordtab(cmd), -1, 2);
  new->prev = NULL;
  new->next = NULL;
  if (list->begin_acmd == NULL)
    {
      list->begin_acmd = new;
      list->end_acmd = new;
    }
  else
    {
      list->end_acmd->next = new;
      new->prev = list->end_acmd;
      list->end_acmd = new;
    }
    list->size++;
}

int			check_alias(char *alias, char **env)
{
  int			i;
  int			e;

  (void)env;
  e = 0;
  i = -1;
  if (alias[my_strlen(alias) - 1] != '\'')
  {
    free(alias);
    return (1);
  }
  while (alias[++i])
    if (alias[i] == '=' && alias[i + 1] == '\'')
      e = 1;
  if (e == 0)
    {
      free(alias);
      return (1);
    }
  return (0);
}

int			add_alias_cmd(t_plist *list, char **tab, char **env)
{
  char			*alias;
  char			*cmd;
  int			i;

  if (tab[1] == NULL)
    return (show_alias(list));
  alias = my_strdup(tab[1]);
  i = 1;
  while (tab[++i])
  {
    alias = my_strcat(alias, " ", -1, -1);
    alias = my_strcat(alias, tab[i], -1, -1);
  }
  if (check_alias(alias, env) == 1)
    return (1);
  i = -1;
  while (alias[++i] != '\'');
  cmd = (char *)alias + i + 1;
  alias[i - 1] = '\0';
  i = -1;
  while (cmd[++i]);
  cmd[i - 1] = '\0';
  add_alias_cmd_list(list, alias, cmd);
  free(alias);
  return (1);
}
