/*
** func_history.c for 42 in 
** 
** Made by Juliani Renaud
** Login   <julian_r@epitech.net>
** 
** Started on  Fri Jun  3 16:42:21 2016 Juliani Renaud
** Last update Thu Jun  9 16:49:37 2016 
*/

#include		"42sh.h"

void			clear_history(t_plist *list)
{
  t_history		*tmp;

  while ((tmp = list->begin_h) != NULL)
    {
      list->begin_h = list->begin_h->next;
      free(tmp->cmd);
      free(tmp);
    }
}

char			*clear_history_c(t_plist *list)
{
  t_history		*tmp;
  int			fd;

  while ((tmp = list->begin_h) != NULL)
    {
      list->begin_h = list->begin_h->next;
      free(tmp->cmd);
      free(tmp);
    }
  if ((fd = open(list->pwd_42, O_TRUNC | O_RDWR | O_CREAT, 0666)) == - 1)
    {
      dprintf(2, "Error with open\n");
      return (NULL);
    }
  close (fd);
  return ("OK");
}

void			show_history(t_plist *list)
{
  t_history		*tmp;
  int			space;

  tmp = list->begin_h;
  while (tmp)
    {
      space = 0;
      if (tmp->ligne < 10)
	while (space++ < 5)
	  my_putstr(" ");
      else if (tmp->ligne < 100)
	while (space++ < 4)
	  my_putstr(" ");
      else if (tmp->ligne < 1000)
	while (space++ < 3)
	  my_putstr(" ");
      else
	while (space++ < 2)
	  my_putstr(" ");
      my_putnbr(tmp->ligne);
      my_putstr("\t");
      my_putstr(tmp->cmd);
      my_putstr("\n");
      tmp = tmp->next;
    }
}

int		       history_main(t_plist *plist, char **cmd, char **env)
{
  (void)env;
  if (cmd[1] != NULL && my_strcmp(cmd[1], "-c") == 0)
    clear_history_c(plist);
  else
    show_history(plist);
  return (0);
}
