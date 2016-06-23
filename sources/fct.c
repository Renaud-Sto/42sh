/*
** fct.c for mysh in 
** 
** Made by Juliani Renaud
** Login   <julian_r@epitech.net>
** 
** Started on  Thu Jun  2 14:18:41 2016 Juliani Renaud
** Last update Thu Jun  2 14:19:00 2016 Juliani Renaud
*/

#include "42sh.h"

void		my_putnbr(int nb)
{
  int		div;

  div = 1;
  if (nb < 0)
    {
      my_putchar('-');
      nb = nb * -1;
    }
  while ((nb / div) >= 10)
    div = div * 10;
  while (div >= 1)
    {
      my_putchar((nb / div) % 10 + 48);
      div = div / 10;
    }
}
