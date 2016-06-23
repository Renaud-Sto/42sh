/*
** get_next_line.c for get_next_line in /home/gastal_r/rendu/CPE_2015/CPE_2015_getnextline
** 
** Made by remi gastaldi
** Login   <gastal_r@epitech.net>
** 
** Started on  Fri Mar  4 16:40:22 2016 remi gastaldi
** Last update Tue May 31 13:49:25 2016 
*/

#include	"42sh.h"

char		*my_realloc(char *str, int size)
{
  char		*new_str;
  int		i;

  i = 0;
  if (size == 0)
    return (str);

  if ((new_str = malloc(sizeof(char) * (size + 1))) == NULL)
    return (NULL);
  while (str[i])
    {
      new_str[i] = str[i];
      i++;
    }
  new_str[i]= '\0';
  free(str);
  return (new_str);
}

char		*return_end(char *final, int i)
{
  final[i] = '\0';
  if (my_strlen(final) == 0)
    {
      free(final);
      return (NULL);
    }
  return (final);
}

char		*get_next_line(const int fd)
{
  static int	nread;
  int		i;
  char		buff[2];
  char		*final;

  i = 0;
  if ((final = malloc(sizeof(char) * 2)) == NULL)
    return (NULL);
  while (1)
    {
      nread = read(fd, buff, 1);
      buff[1] = '\0';
      if (nread <= 0)
      	return (return_end(final, i));
      final[i] = buff[0];
      if (final[i] == '\n')
	{
	  final[i] = '\0';
	  return (final);
	}
      i++;
      final[i] = '\0';
      final = my_realloc(final, i + 1);
    }
}
