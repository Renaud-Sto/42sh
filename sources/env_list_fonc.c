/*
** env_list_fonc.c for env_list_fonc in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Fri May 27 00:54:48 2016 
** Last update Wed Jun  1 17:28:03 2016 
*/

#include		"42sh.h"

void                    pars_env_line(t_list **list, char *env)
{
  int                   i;
  int                   w;

  w = -1;
  i = -1;
  while (env[++i] != '=');
  if (((*list)->name = malloc(sizeof(char) * (i + 1))) == NULL)
    return;
  i = -1;
  while (env[++i] != '=')
    (*list)->name[i] = env[i];
  (*list)->name[i] = '\0';
  if (env[i] != '\0' && env[i + 1] == '\0')
    {
      (*list)->data= NULL;
      return;
    }
  if (((*list)->data = malloc(sizeof(char) *
			      (my_strlen(env) - i) + 1)) == NULL)
    return;
  while (env[++i])
    (*list)->data[++w] = env[i];
  (*list)->data[w + 1] = '\0';
}

void                    env_to_list(t_plist *list, char *env)
{
  t_list                *new;

  if (!list)
    return;
  if ((new = malloc(sizeof(t_list))) == NULL)
    return;
  pars_env_line(&new, env);
  new->prev = NULL;
  new->next = NULL;
  if (list->begin == NULL)
    {
      list->begin = new;
      list->end = new;
    }
  else
    {
      new->prev = list->end;
      list->end->next = new;
      list->end = new;
    }
}

char                    **list_to_env(t_list *tmp, t_list *list)
{
  int                   i;
  char                  **env;

  i = 0;
  if (tmp == NULL)
    return (NULL);
  while (tmp)
    {
      tmp = tmp->next;
      i++;
    }
  if ((env = malloc(sizeof(char *) * (i + 1))) == NULL)
    return (NULL);
  i = 0;
  while (list)
    {
      env[i] = NULL;
      env[i] = my_strcat(env[i], list->name, -1, -1);
      env[i] = my_strcat(env[i], "=", -1, -1);
      if (list->data != NULL)
	env[i] = my_strcat(env[i], list->data, -1, -1);
      list = list->next;
      i++;
    }
  env[i] = NULL;
  return (env);
}
