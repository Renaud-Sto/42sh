/*
** my_puts.c for my_puts in /home/jabbar_y/rendu/42sh
**
** Made by Jabbari Yassir
** Login   <jabbar_y@epitech.net>
**
** Started on  Thu Jun  2 13:40:21 2016 Jabbari Yassir
** Last update Mon Jun  6 17:27:49 2016 
*/

#include "42sh.h"

int                     print_command_not_found(char *cmd)
{
  write(2, cmd, my_strlen(cmd));
  write(2, ": Command not found.", 20);
  write(2, "\n", 1);
  return (1);
}

void		my_puts(char *str)
{
  my_putstr(str);
  my_putchar('\n');
}

void    my_putchar(char c)
{
  write (1, &c, 1);
}
