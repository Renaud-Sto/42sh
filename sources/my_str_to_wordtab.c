/*
** my_str_to_wordtab.c for my_str_to_wordtab in /home/gastal_r/rendu/PSU_2015/PSU_2015_minishell2/sources
** 
** Made by remi gastal_r
** Login   <gastal_r@epitech.net>
** 
** Started on  Mon Apr  4 11:00:20 2016 remi gastal_r
** Last update Sat May 28 12:11:10 2016 
*/

#include "42sh.h"

int	my_count_word(char *str)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (str[i] != '\0' && (str[i]) == ' ')
    i++;
  while (str[i] != '\0')
    {
      if ((str[i]) != ' ')
	{
	  j++;
	  while (str[i] && str[i] != ' ')
	    i++;
	  if (str[i] == '\0')
	    j--;
	  i--;
	}
      i++;
    }
  return (j + 1);
}

char	**init_tab(char *str)
{
  char	**tab;

  if ((tab = malloc(sizeof(char *) * (my_count_word(str) + 1))) == NULL)
    return (0);
  return (tab);
}

char	**my_str_to_wordtab(char *str)
{
  int	i;
  int	n;
  int	x;
  char	**tab;

  i = -1;
  n = 0;
  x = 0;
  tab = init_tab(str);
  while (++i != my_count_word(str))
    {
      tab[i] = malloc(sizeof(char) * my_strlen(str) + 1);
      while (str[n] != '\0' && str[n] == ' ')
	n++;
      while (str[n] != '\0' && str[n] != ' ')
	{
	  tab[i][x] = str[n];
	  n++;
	  x++;
	}
      tab[i][x] = '\0';
      x = 0;
    }
  tab[i] = NULL;
  return (tab);
}
