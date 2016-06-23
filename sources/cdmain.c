/*
** cdmain.c for cdmain in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/sources
** 
** Made by 
** Login   <gastal_r@epitech.net>
** 
** Started on  Sat May 28 23:54:07 2016 
** Last update Tue Jun  7 18:09:08 2016 
*/

#include		"42sh.h"

int			cd_main(t_plist *plist, char **cmd, char **env)
{
  t_list		*list;

  (void)env;
  list = plist->begin;
  if (cmd[1] != NULL)
    {
      if (my_strcmp("..", cmd[1]) == 0)
        {
          while (my_strcmp("PWD", list->name) != 0)
	    {
	      list = list->next;
	      if (list == NULL)
		return (0);
	    }
          cd_prec(plist, my_strdup(list->data));
        }
      else if (my_strcmp("-", cmd[1]) == 0)
        return (cd_old(plist));
      else
        return (cd_dir(plist, cmd[1]));
    }
  else
    cd_home(plist);
  return (0);
}

int                     return_chdir(char *dir, char *newpath)
{
  my_putstr("cd: no such file or directory: ");
  my_putstr(dir);
  write(1, "\n", 1);
  free(newpath);
  return (1);
}

int			check_dir(t_plist *plist, char *newpath, char *dir)
{
  struct stat		folder;

  if (stat(dir, &folder) == 0 && S_ISDIR(folder.st_mode))
    if (folder.st_mode & S_IRGRP)
      {
	if (get_oldpwd(plist) != NULL)
	  act_oldpwd(plist, get_pwd(plist));
	act_pwd(plist, newpath);
	return (0);
      }
    else
      {
	my_putstr(dir);
	my_putstr(": Permission denied.\n");
	free(newpath);
	return (1);
      }
  else
    return (return_chdir(dir, newpath));
}
