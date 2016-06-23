/*
** unset_env.c for 42sh in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Sat May 28 22:44:19 2016 
** Last update Mon Jun  6 01:21:02 2016 
*/

#include		"42sh.h"

int			unset_env(t_plist *plist, char **cmd, char **env)
{
  t_list		*list;

  (void)env;
  list = plist->begin;
  if (cmd[1] == NULL)
    return (0);
  while (my_strcmp(list->name, cmd[1]) != 0)
    {
      list = list->next;
      if (list == NULL)
        return (0);
    }
  if (list->next != NULL)
    list->next->prev = list->prev;
  else
    plist->end = list->prev;
  if (list->prev != NULL)
    list->prev->next = list->next;
  else
    plist->begin = list->next;
  free(list->name);
  free(list->data);
  free(list);
  return (0);
}
