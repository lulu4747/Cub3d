/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 18:27:24 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/05 15:18:50 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_return(char *dst, const char *src, size_t size)
{
	unsigned long	i;
	int				s;
	int				t;

	i = 0;
	s = 0;
	t = 0;
	while (dst[i])
		i++;
	while (src[s])
		s++;
	s = s + i;
	if (i > size)
	{
		t = i - size;
		s = s - t;
	}
	return (s);
}

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned long	i;
	int				s;
	int				t;
	int				p;

	p = 0;
	i = 0;
	t = 0;
	s = ft_return(dst, src, size);
	while (dst[i])
		i++;
	if (size != 0)
	{
		while (i < size - 1 && src[p])
		{
			dst[i] = src[t];
			i++;
			t++;
			p++;
		}
		dst[i] = 0;
	}
	return (s);
}
