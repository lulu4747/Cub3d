/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 15:02:14 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 17:36:17 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned long	i;
	unsigned char	*dt;
	unsigned char	*sc;

	dt = (unsigned char *)dst;
	sc = (unsigned char *)src;
	i = -1;
	if (&*dt < &*sc)
		while (++i < len)
			dt[i] = sc[i];
	else if (&*dt > &*sc)
		while (len-- > 0 && &dt[len] >= &dt[0])
			dt[len] = sc[len];
	return (dst);
}
