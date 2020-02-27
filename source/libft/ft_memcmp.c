/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 15:23:03 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 16:06:15 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned long	i;
	unsigned char	*st;
	unsigned char	*nd;

	st = (unsigned char *)s1;
	nd = (unsigned char *)s2;
	i = 0;
	if (n > 0)
		while (i < n)
		{
			if (st[i] != nd[i])
				return (st[i] - nd[i]);
			i++;
		}
	return (0);
}
