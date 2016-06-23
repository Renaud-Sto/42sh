/*
** order_args.c for order_args in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Mon May 30 10:16:07 2016 
** Last update Mon Jun  6 01:48:51 2016 
*/

#include		"42sh.h"

int			get_prompt_length(char **prompt)
{
  int			i;

  i = 0;
  while (prompt[i] != NULL)
    i++;
  return (i);
}

char			**order_args(char **promp, int i, int j)
{
  char			**buff;

  if (get_prompt_length(promp) <= 2
      || (my_strcmp(">", promp[0]) == 0 || my_strcmp(">>", promp[0]) == 0)
      || (my_strcmp("<", promp[0]) == 0 || my_strcmp("<<", promp[0]) == 0))
    return (promp);
  while (promp[++i] != NULL)
    {
      if ((my_strcmp(">", promp[i]) == 0 || my_strcmp(">>", promp[i]) == 0)
	  || (my_strcmp("<", promp[i]) == 0 || my_strcmp("<<", promp[i]) == 0))
	{
	  buff = malloc(sizeof(char *) * (get_prompt_length(promp) + 1));
	  buff[0] = my_strdup(promp[i]);
	  buff[1] = my_strdup(promp[i + 1]);
	  while (j - 2 < i)
	    {
	      buff[j] = my_strdup(promp[j - 2]);
	      j++;
	    }
	  buff[j] = NULL;
	  free_tab(promp);
	  return (buff);
	}
    }
  return (promp);
}
