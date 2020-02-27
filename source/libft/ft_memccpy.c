/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 14:14:29 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 15:19:25 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned long	i;
	unsigned char	*dt;
	unsigned char	*sc;

	dt = (unsigned char*)dst;
	sc = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		dt[i] = sc[i];
		if ((unsigned char)c == sc[i])
		{
			i++;
			return (dt + i);
		}
		i++;
	}
	return (NULL);
}
