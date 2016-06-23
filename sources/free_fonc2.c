/*
** free_fonc2.c for free_fonc2 in /home/gastal_r/rendu/42sh/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Fri Jun  3 17:25:17 2016 
** Last update Mon Jun  6 15:53:40 2016 
*/

#include		"42sh.h"

void                    free_alias_cmd(t_plist *list)
{
  t_alias_cmd           *tmp;
  int			i;

  while ((tmp = list->begin_acmd) != NULL)
    {
      i = -1;
      list->begin_acmd = list->begin_acmd->next;
      free(tmp->alias);
      while (tmp->cmd[++i])
	free(tmp->cmd[i]);
      free(tmp->cmd);
      free(tmp);
    }
}
