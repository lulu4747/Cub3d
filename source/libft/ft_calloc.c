/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_calloc.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/12 11:45:45 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 17:39:47 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned long		i;
	char				*t;
	void				*r;

	i = 0;
	if ((r = malloc(size * count)) == NULL)
		return (NULL);
	t = r;
	while (i < count * size)
	{
		t[i] = 0;
		i++;
	}
	return (r);
}
