/*
** pre_parsing.c for pre_parsing in /home/gastal_r/rendu/42sh/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Wed Jun  1 16:13:24 2016 
** Last update Wed Jun  1 16:15:02 2016 
*/

#include		"42sh.h"

void                    pre_parsing_check(char *prompt, int *check,
					  int *space, int i)
{
  if (prompt[i] != '\0' && prompt[i] == ';')
    *check = 1;
  else
    *check = 0;
  if (prompt[i] != '\0' && prompt[i] == ' ')
    *space = 1;
  else
    *space = 0;
}

char                    *pre_parsing(char *prompt, int i, int j)
{
  char                  *buff;
  int                   check;
  int                   space;

  space = 0;
  check = 0;
  buff = malloc(sizeof(char) * (my_strlen(prompt) + 1));
  while (prompt[i])
    {
      while (prompt[i] && ((check == 1 ? prompt[i] == ';' : 0)
			   || (space == 1 ? prompt[i] == ' ' : 0)))
	i++;
      buff[++j] = prompt[i];
      pre_parsing_check(prompt, &check, &space, i);
      if (prompt[i] != '\0' && prompt[i] == '\t')
	{
	  buff[j] = ' ';
	  while (prompt[i] != '\0' && prompt[i] == '\t')
	    i++;
	}
      else
	(prompt[i] != '\0' ? i++ : 0);
    }
  buff[j + 1] = '\0';
  return (buff);
}
