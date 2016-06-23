/*
** alias_func.c for alias_func in /home/jabbar_y/rendu/42sh
**
** Made by Jabbari Yassir
** Login   <jabbar_y@epitech.net>
**
** Started on  Fri Jun  3 17:35:27 2016 Jabbari Yassir
** Last update Wed Jun  8 11:49:41 2016 
*/

#include "42sh.h"

int                     show_alias(t_plist *list)
{
  t_alias_cmd           *tmp;
  int			i;

  tmp = list->begin_acmd;
  while (tmp)
    {
      i = -1;
      my_putstr(tmp->alias);
      my_putstr("     ");
      while (tmp->cmd[++i])
	{
	  my_putstr(tmp->cmd[i]);
	  write(1, " ", 1);
	}
      write(1, "\n", 1);
      tmp = tmp->next;
    }
  return (0);
}

void			parser_alias_bis(t_plist *list, char *str, t_data data_alias)
{
  if (str[data_alias.i] != 39)
    return;
  data_alias.i++;
  data_alias.tmp = data_alias.i;
  data_alias.j = 0;
  while (str[data_alias.i] != 39)
    {
      data_alias.j++;
      data_alias.i++;
    }
  if ((data_alias.cmd2 = malloc(sizeof(char) * data_alias.j + 1)) == NULL)
    return;
  data_alias.j = 0;
  while (data_alias.tmp != data_alias.i)
    data_alias.cmd2[data_alias.j++] = str[data_alias.tmp++];
  data_alias.cmd2[data_alias.j] = '\0';
  add_alias(list, data_alias.cmd1, data_alias.cmd2);
  free(data_alias.cmd2);
}

void			parser_alias(t_plist *list, char *str)
{
  t_data		data_alias;

  data_alias.tmp = 0;
  data_alias.i = 0;
  data_alias.j = 0;
  if (str[data_alias.i] == 'a' && str[data_alias.i + 1] == 'l' &&
      str[data_alias.i + 2] == 'i' && str[data_alias.i + 3] == 'a' &&
      str[data_alias.i + 4] == 's' && str[data_alias.i + 5] &&
      str[data_alias.i + 6] && str[data_alias.i + 7] && str[data_alias.i + 8]
      && str[data_alias.i + 9] && str[data_alias.i + 10])
    {
      data_alias.i = data_alias.i + 5;
      data_alias.tmp = data_alias.i + 1;
      while (str[data_alias.i++] != '=')
	data_alias.j++;
      if ((data_alias.cmd1 = malloc(sizeof(char) * data_alias.j + 1)) == NULL)
	return;
      data_alias.j = 0;
      while (data_alias.i != data_alias.tmp + 1)
	data_alias.cmd1[data_alias.j++] = str[data_alias.tmp++];
      data_alias.cmd1[data_alias.j] = '\0';
      parser_alias_bis(list, str, data_alias);
      free(data_alias.cmd1);
    }
}

void			alias(t_plist *list)
{
  int			fd;
  char			*buffer;
  if ((fd = open(".42shrc", O_RDONLY)) == -1)
    {
      if ((fd = open(".42shrc", O_RDWR | O_CREAT, 0666)) == -1)
	return;
    }
  else
    {
      while ((buffer = get_next_line(fd)))
	{
	  if (buffer == NULL)
	    return;
	  parser_alias(list, buffer);
	  free(buffer);
	}
    }
}
