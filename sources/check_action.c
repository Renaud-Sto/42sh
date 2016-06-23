/*
** check_action.c for check_action in /home/gastal_r/rendu/42sh/sources
**
** Made by
** Login   <gastal_r@epitech.net>
**
** Started on  Mon Jun  6 00:15:02 2016
** Last update Mon Jun  6 18:48:53 2016 
*/

#include		"42sh.h"

int			ptr_check_action(int i, char **cmd, char **env, t_plist *plist)
{
  int			(*ptrtab[12])(t_plist *, char**,  char **);

  ptrtab[0] = history_main;
  ptrtab[1] = show_list;
  ptrtab[2] = set_env;
  ptrtab[3] = unset_env;
  ptrtab[4] = cd_main;
  ptrtab[5] = echo;
  ptrtab[6] = red_right;
  ptrtab[7] = double_red_right;
  ptrtab[8] = red_left;
  ptrtab[9] = double_red_left;
  ptrtab[10] = add_alias_cmd;
  ptrtab[11] = pop_alias_cmd;
  plist->exit_value = ptrtab[i](plist, cmd, env);
  (plist->pipe == 1 ? exit(plist->exit_value) : (void)0);
  return (plist->exit_value);
}

char			**init_flag(char *flag[13])
{
  flag[0] = "history";
  flag[1] = "env";
  flag[2] = "setenv";
  flag[3] = "unsetenv";
  flag[4] = "cd";
  flag[5] = "echo";
  flag[6] = ">";
  flag[7] = ">>";
  flag[8] = "<";
  flag[9] = "<<";
  flag[10] = "alias";
  flag[11] = "unalias";
  flag[12] = NULL;
  return (flag);
}

int			check_action(char **cmd, char **env, t_plist *plist)
{
  int			i;
  char			*flag[13];
  int			status;
  char			**buff;

  buff = NULL;
  init_flag(flag);
  i = 0;
  status = 0;
  if ((buff = test_alias(plist, cmd)) != NULL)
    return (launch_alias(plist, buff, env));
  while (flag[i] != NULL && my_strcmp(cmd[0], flag[i]) != 0)
    if (flag[++i] == NULL)
      {
	if ((plist->exit_value = exec_fonc(plist, cmd, env, status)) == 1)
	  plist->exit_value = system_fonc(plist, cmd, env);
	(plist->pipe == 1 ? exit(plist->exit_value) : (void)0);
	return (plist->exit_value);
      }
  return (ptr_check_action(i, cmd, env, plist));
}

int			exit_end(t_plist *list, int i)
{
  list->exit_value = i;
  return (-1);
}

int			check_invalid_cmd()
{
  dprintf(2, "Invalid null command. \n");
  return (-1);
}
