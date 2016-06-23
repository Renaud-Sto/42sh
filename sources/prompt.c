/*
** prompt.c for prompt in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Fri May 27 11:38:43 2016 
** Last update Mon Jun  6 09:29:16 2016 
*/

#include		"42sh.h"

void			get_user(t_plist *plist)
{
  t_list		*list;

  if (!plist)
    return ;
  list = plist->begin;
    while (list && my_strcmp(list->name, "USER") != 0)
      {
	list = list->next;
	if (list == NULL)
	  return ;
      }
  my_putstr(ROUGE);
  (list->data != NULL ? my_putstr(list->data) : (void)0);
  write(1, " ", 1);
  my_putstr(NORMAL);
}

char			*aff_prompt(t_env *env, t_plist *plist)
{
  char			*st;

  get_user(plist);
  my_putstr(CYANCLAIR);
  write(1, "~", 1);
  my_putstr(VERTCLAIR);
  if (get_pwd(plist) != NULL)
    my_putstr(get_pwd(plist));
  write(1, " ", 1);
  my_putstr(NORMAL);
  st = get_next_line(0);
  if (st == NULL)
    {
      free_tab(env->env);
      printf("\nexit\n");
      return (NULL);
    }
  if (st[0] != '\0' && st[0] == '!')
    {
      if ((check_cmd_history(plist, st, 0, 0)) == NULL)
  	return (NULL);
    }
  else if (st[0] != '\0' && st[0] != '!')
    cmd_to_history(plist, st);
  return (st);
}

char			*check_prompt(char *prompt)
{
  int			i;

  i = 0;
  if (my_strlen(prompt) == 0)
    return (NULL);
  while (prompt[i])
    {
      if (prompt[i] != ' ' && prompt[i] != '\t')
	return (prompt);
      i++;
    }
  return (NULL);
}

int			prompt(t_env *env, t_plist *plist)
{
  char			*st;

  while (1)
    {
      signal(SIGINT, SIG_IGN);
      if ((st = aff_prompt(env, plist)) == NULL)
	return (0);
      while (check_prompt(st) == NULL)
	{
	  free(st);
	  st = aff_prompt(env, plist);
	  if (st == NULL)
	    return (0);
	}
      signal(SIGINT, SIG_DFL);
      if (pars_prompt(plist, env, st) != 0)
	{
	  free(st);
	  free_tab(env->env);
	  return (0);
      	}
      free(st);
    }
  free_tab(env->env);
  return (0);
}
