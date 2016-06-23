/*
** get_path.c for get_path in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Sat May 28 17:29:02 2016 
** Last update Fri Jun  3 00:16:00 2016 
*/

#include		"42sh.h"

int			count_path(char *path)
{
  int			i;
  int			nbr;

  nbr = 1;
  i = 0;
  while (path[i])
    {
      (path[i] == ':' ? nbr++ : 0);
      i++;
    }
  return (nbr);
}

int			path_length(char *path, int i)
{
  int			j;

  j = i;
  while (path[j] != ':' && path[j] != '\0')
    j++;
  return (j - i);
}

char			**get_path2(t_list *list, int j, int i, int nbr)
{
  char			**path;
  int			p_length;

  path = malloc(sizeof(char*) * (count_path(list->data) + 1));
  while (list->data[j])
    {
      p_length = path_length(list->data, j);
      path[nbr] = malloc(sizeof(char) * (p_length + 1));
      while (i < p_length)
	{
          path[nbr][i] = list->data[j];
          j++;
          i++;
        }
      path[nbr][i] = '\0';
      nbr++;
      i = 0;
      (j < my_strlen(list->data) ? j++ : 0);
    }
  path[nbr] = NULL;
  return (path);
}

char			**get_path(t_plist *plist)
{
  t_list		*list;

  list = plist->begin;
  while (my_strcmp("PATH", list->name) != 0)
    {
      list = list->next;
      if (list == NULL)
	return (NULL);
    }
  if (list->data == NULL)
    return (NULL);
  return (get_path2(list, 0, 0, 0));
}

char			*test_access(t_plist *plist, char *cmd)
{
  char			*buff;
  int			i;
  char			**path;

  i = -1;
  if ((path = get_path(plist)) == NULL)
    return (NULL);
  while (path[++i] != NULL)
    {
      buff = my_strdup(path[i]);
      buff = my_strcat(buff, "/", -1, -1);
      buff = my_strcat(buff, cmd, -1, -1);
      if (access(buff, X_OK) == 0)
	{
	  free_tab(path);
	  return (buff);
	}
      free(buff);
    }
  free_tab(path);
  return (NULL);
}
