/*
** main.c for 42sh in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/sources
**
** Made by
** Login   <gastal_r@epitech.net>
**
** Started on  Thu May 26 21:45:20 2016
** Last update Wed Jun  8 13:08:28 2016 
*/

#include		"42sh.h"

void			init_path(t_plist *plist)
{
  t_list		*list;

  list = plist->begin;
  while (my_strcmp(list->name, "PATH") != 0)
    {
      list = list->next;
      if (list == NULL)
	{
	  env_to_list(plist, "PATH=/usr/local/sbin:/usr/local/bin:\
/usr/bin:/usr/lib/jvm/default/bin:/usr/bin/site_perl:/usr/bin/vendor_perl:\
/usr/bin/core_perl:/bin:/opt/bin:/usr/lib/jvm/default/bin:/usr/bin/site_perl:\
/usr/bin/vendor_perl:/usr/bin/core_perl");
	  return;
	}
    }
}

int			main(int ac, char **av, char **env)
{
  int			i;
  t_plist		plist;
  t_env			my_env;

  (void)ac;
  (void)av;
  my_env.env = NULL;
  if (env[0] == NULL)
    return (0);
  if (init_list(&plist) == -1)
    return (0);
  i = -1;
  while (env[++i] != NULL)
    env_to_list(&plist, env[i]);
  init_path(&plist);
  plist.exit_value = 0;
  if ((my_env.env = init_env(my_env.env, &plist)) == NULL)
    return (0);
  alias(&plist);
  init_history_path(&plist);
  open_history(&plist, 0);
  prompt(&my_env, &plist);
  add_to_history(&plist);
  free_list(&plist);
  return (plist.exit_value);
}
