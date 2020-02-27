/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 15:54:53 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/29 13:47:05 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbc(char *s, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			x++;
			while (s[i + 1] != c && s[i + 1] != 0)
			{
				i++;
			}
		}
		i++;
	}
	return (x);
}

int		ft_linelen(char const *s, char c)
{
	int	i;
	int r;

	r = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		i++;
		r++;
	}
	return (r);
}

char	*ft_line(const char *s1, int x, char c)
{
	int		i;
	char	*r;

	i = 0;
	if ((r = malloc(sizeof(char) * x)) == NULL)
		return (NULL);
	while (i < x)
	{
		r[i] = s1[i];
		i++;
		if (s1[i] == c)
		{
			r[i] = 0;
			return (r);
		}
	}
	r[i] = 0;
	return (r);
}

char	*ft_findnext(char *s, char c, int x)
{
	int	i;

	i = 0;
	if (x == 0)
	{
		while (s[i] == c)
			i++;
		s = s + i;
		return (s);
	}
	while (s[i] && s[i] != c)
		i++;
	while (s[i] && s[i] == c)
		i++;
	s = s + i;
	return (s);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	*p;
	char	**r;

	r = NULL;
	if (!s)
		return (r);
	i = 0;
	j = ft_nbc((char *)s, c);
	if ((r = malloc(sizeof(char*) * (j + 1))) == NULL)
		return (NULL);
	r[j] = 0;
	p = ft_findnext((char *)s, c, i);
	while (i < j)
	{
		if (!(r[i] = ft_line(p, ft_linelen(p, c), c)))
		{
			free(r);
			return (NULL);
		}
		i++;
		p = ft_findnext(p, c, i);
	}
	return (r);
}
