/*
** history.c for mysh in 
** 
** Made by Juliani Renaud
** Login   <julian_r@epitech.net>
** 
** Started on  Thu Jun  2 13:34:44 2016 Juliani Renaud
** Last update Wed Jun  8 13:12:43 2016 
*/

#include	"42sh.h"

char		*add_to_history(t_plist *list)
{
  int		fd;
  t_history	*tmp;

  tmp = list->begin_h;
  if ((fd = open(list->pwd_42, O_RDWR | O_CREAT, 0666)) == -1)
    {
      dprintf(2, "Error with open\n");
      return (NULL);
    }
  while (tmp)
    {
      if ((write(fd, tmp->cmd, my_strlen(tmp->cmd))) == -1)
	{
	  dprintf(2, "Error with write\n");
	  return (NULL);
	}
      if ((write(fd, "\n", my_strlen("\n"))) == -1)
	{
	  dprintf(2, "Error with write\n");
	  return (NULL);
	}
      tmp = tmp->next;
    }
  close (fd);
  return ("OK");
}

char		*open_history(t_plist *list, int fd)
{
  char		*buff;

  if ((fd = open(list->pwd_42, O_RDWR | O_CREAT, 0666)) == -1)
    {
      dprintf(2, "Error with open\n");
      return (NULL);
    }
  while ((buff = get_next_line(fd)))
    {
      cmd_to_history(list, buff);
      free(buff);
    }
  return ("OK");
}

char		*check_cmd_history(t_plist *list, char *str, int i, int j)
{
  char		*str2;

  while (str[i] == '!')
    i++;
  while (str[i] != '\0' && ((str[i] >= 'a' && str[i] <= 'z')
			    || (str[i] >= 'A' && str[i] <= 'Z')))
    i++;
  if (str[i] == '\0')
    return (str);
  else
    {
      if ((str2 = malloc(sizeof(char) * (my_strlen(&str[i]) + 1))) == NULL)
	{
	  dprintf(2, "Error with malloc\n");
	  return (NULL);
	}
      while (str[i])
	str2[j++] = str[i++];
      str2[j] = '\0';
      cmd_to_history(list, str2);
      add_to_history(list);
    }
  free(str2);
  return (str);
}

void                    cmd_to_history(t_plist *list, char *cmd)
{
  t_history		*new;

  if (!list)
    return;
  if ((new = malloc(sizeof(t_history))) == NULL)
    return;
  new->prev = NULL;
  new->next = NULL;
  if (list->begin_h == NULL)
    {
      new->cmd = my_strdup(cmd);
      new->ligne = 1;
      list->begin_h = new;
      list->end_h = new;
    }
  else
    {
      new->cmd = my_strdup(cmd);
      new->prev = list->end_h;
      list->end_h->next = new;
      list->end_h = new;
      if (new->prev != NULL)
	new->ligne = new->prev->ligne + 1;
    }
}
