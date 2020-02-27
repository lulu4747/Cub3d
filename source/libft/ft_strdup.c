/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/12 13:59:33 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/16 15:56:37 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*r;

	i = 0;
	len = ft_strlen((char *)s1) + 1;
	if ((r = malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	while (i < len)
	{
		r[i] = s1[i];
		i++;
	}
	return (r);
}
