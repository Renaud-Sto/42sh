/*
** pwd.c for pwd in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Sun May 29 00:00:44 2016 
** Last update Thu Jun  2 00:02:29 2016 
*/

#include		"42sh.h"

char			*get_pwd(t_plist *plist)
{
  t_list		*list;

  list = plist->begin;
  while (my_strcmp(list->name, "PWD") != 0)
    {
      list = list->next;
      if (list->next == NULL)
	return (NULL);
    }
  return (list->data);
}

char			*get_oldpwd(t_plist *plist)
{
  t_list		*list;

  list = plist->begin;
  while (my_strcmp(list->name, "OLDPWD") != 0)
    {
      list = list->next;
      if (list->next == NULL)
	return (NULL);
    }
  return (list->data);
}

void			act_pwd(t_plist *plist, char *path)
{
  t_list		*list;
  char			*buff;

  buff = my_strdup(path);
  list = plist->begin;
  while (list && my_strcmp("PWD", list->name) != 0)
    list = list->next;
  if (list->data != NULL)
    free(list->data);
  list->data = buff;
}

void		        act_oldpwd(t_plist *plist, char *path)
{
  t_list		*list;

  list = plist->begin;
  while (my_strcmp("OLDPWD", list->name) != 0)
    list = list->next;
  free(list->data);
  list->data = my_strdup(path);
}
