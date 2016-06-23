/*
** my_getnbr.c for my_getnbr in /home/gastal_r/rendu/Piscine_C_J07/lib/my
** 
** Made by remi gastaldi
** Login   <gastal_r@epitech.net>
** 
** Started on  Wed Oct  7 03:44:54 2015 remi gastaldi
** Last update Fri Apr  8 15:54:27 2016 remi gastal_r
*/

#include <stdio.h>

int	my_getnbr(char *str)
{
  int	i;
  int	nbr;

  if (str == NULL)
    return (0);
  i = 0;
  if (str[i] == '-')
    {
      str[i] = '0';
      return (0);
    }
  nbr = 0;
  while (str[i] >= '0' && str[i] <= '9')
    {
      nbr = nbr * 10;
      nbr = nbr + (str[i] - '0');
      i = i + 1;
    }
  return (nbr);
}
