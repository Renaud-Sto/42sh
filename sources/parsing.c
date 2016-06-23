/*
** parsing.c for parsing in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Fri May 27 15:55:40 2016 
** Last update Sun Jun  5 23:30:24 2016 
*/

#include		"42sh.h"

int			test_separator(char c)
{
  int			i;

  i = -1;
  while (SEPARATOR[++i])
    if (c == SEPARATOR[i])
      return (1);
  return (0);
}

int			calc_length(char *str, int i)
{
  if (test_separator(str[i]))
    {
      while (str[i] && test_separator(str[i]))
	i++;
      return (i);
    }
  else
    {
      while (str[i] && test_separator(str[i]) == 0)
	{
	  if (str[i] && str[i] == ' ' && test_separator(str[i + 1]))
	    return (i);
	  i++;
	}
      return (i);
    }
  return (0);
}

int			fill_list(char *str, t_pcmd *pcmd, t_psep *psep, int i)
{
  int			j;
  char			*buff;
  int			k;

  j = 0;
  while (str[i])
    {
      k = -1;
      if (str[i] == ' ')
      	i++;
      if ((buff = malloc(sizeof(char) *
			 ((calc_length(str, i) - i) + i) + 1)) == NULL)
	return (-1);
      i = (calc_length(str, i) - i) + i;
      if (str[j] == ' ')
      	j++;
      while (j < i)
	buff[++k] = str[j++];
      while (buff[k] == ' ')
	k--;
      buff[k + 1] = '\0';
      (test_separator(buff[0]) == 0 ? add_cmd(pcmd, buff) : (void)0);
      (test_separator(buff[0]) == 1 ? add_sep(psep, buff) : (void)0);
      free(buff);
    }
  return (0);
}

int			pars_prompt(t_plist *plist, t_env *env, char *st)
{
  t_pcmd		pcmd;
  t_psep		psep;

  if (init_prompt_list(&pcmd, &psep) == -1)
    return (-1);
  st = pre_parsing(st, 0, -1);
  if (fill_list(st, &pcmd, &psep, 0) == -1)
    return (-1);
  if (launch(env, plist, pcmd.begin, psep.begin) != 0)
    {
      free(st);
      free_prompt_list(&pcmd, &psep);
      return (-1);
    }
  free(st);
  free_prompt_list(&pcmd, &psep);
  return (0);
}
