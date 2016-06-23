/*
** utils.c for utils.c in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/sources
**
** Made by
** Login   <gastal_r@epitech.net>
**
** Started on  Thu May 26 21:43:04 2016
** Last update Mon Jun  6 03:14:57 2016 
*/

#include	     	"42sh.h"

char			*my_strcat(char *dest, char *src, int i, int j)
{
  char			*tmp;
  int			len_src;
  int			len_dest;

  len_src = my_strlen(src);
  if (dest == NULL)
    {
      if ((dest = malloc((len_src + 1))) == NULL)
	return (NULL);
      while (src[++i])
	dest[i] = src[i];
      dest[i] = '\0';
      return (dest);
    }
  len_dest = my_strlen(dest);
  if ((tmp = malloc((len_src + len_dest + 1))) == NULL)
    return (NULL);
  while (dest[++j])
    tmp[j] = dest[j];
  while (src[++i])
    tmp[j++] = src[i];
  tmp[j] = '\0';
  free(dest);
  return (tmp);
}

int			my_strlen(char *str)
{
  int		       	i;

  i = 0;
  while (str[i])
    i++;
  return (i);
}

char			*my_strdup(char *str)
{
  char			*new_str;
  int			i;

  i = 0;
  if (str == NULL)
    return (NULL);
  if ((new_str = malloc(sizeof(char) * (my_strlen(str) + 1))) == NULL)
    return (NULL);
  while (str[i])
    {
      new_str[i] = str[i];
      i++;
    }
  new_str[i]= '\0';
  return (new_str);
}

void			my_putstr(char *str)
{
  write(1, str, my_strlen(str));
}

int			my_strcmp(char *s1, char *s2)
{
  int   i;

  i = 0;
  while ((s1[i] == s2[i]) && s1[i] && s2[i])
    i++;
  return (s1[i] - s2[i]);
}
