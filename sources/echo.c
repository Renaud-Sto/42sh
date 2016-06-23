/*
** echo.c for echo in /home/jabbar_y/rendu/42sh/NE_PAS_TOUCHER
**
** Made by Jabbari Yassir
** Login   <jabbar_y@epitech.net>
**
** Started on  Tue May 31 15:15:24 2016 Jabbari Yassir
** Last update Mon Jun  6 22:06:32 2016 
*/

#include	"42sh.h"

int		echo_n(char **tab)
{
  int		i;

  i = 2;
  if (tab[i])
    {
      while (tab[i])
	{
	  my_putstr(tab[i]);
	  if (tab[i + 1])
	    my_putstr(" ");
	  i++;
	}
    }
  return (0);
}

void		custom_putstr(char **tab, int i, int j)
{
  if (tab[i][1] && tab[i][0] == '\"' && tab[i][1] == '\"')
    return;
  if (tab[i])
    {
      while (tab[i][j])
	{
	  if (tab[i][j] == 34)
	    j++;
	  if (tab[i][j] != '\0')
	    my_putchar(tab[i][j++]);
	}
      (tab[i + 1] != NULL ? my_putchar(' ') : (void)0);
    }
}

int		check_quote(char **tab, char **env)
{
  int		i;
  int		j;
  int		h;

  i = 1;
  (void)env;
  h = 0;
  while (tab[i])
    {
      j = 0;
      while (tab[i][j])
	{
	  if (tab[i][j] == '\"')
	    h++;
	  j++;
	}
      i++;
    }
  if ((h % 2) != 0)
    return (-1);
  return (0);
}

int		error_quote()
{
  dprintf(2, "Unmatched \".\n");
  return (0);
}

int		echo(t_plist *plist, char **tab, char **env)
{
  int		j;
  int		i;
  t_list	*list;

  list = plist->begin;
  i = 1;
  j = 0;
  if (tab[i] && ((my_strcmp("-n", tab[i])) == 0))
    echo_n(tab);
  else if (tab[i] && (tab[i][0] == '$'))
    echo_valuenv(tab, list);
  else
    {
      while (tab[i])
	{
	  if (check_quote(tab, env) == -1)
	    return (error_quote());
	  custom_putstr(tab, i, j);
	  i++;
	  j = 0;
	}
      my_putchar('\n');
    }
  return (0);
}
