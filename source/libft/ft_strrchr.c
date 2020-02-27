/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrchr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 16:30:03 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/18 20:22:21 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p;

	i = 0;
	if (*s == c)
		return ((char *)s);
	while (s[i++])
		p = (char *)s + i;
	i = 0;
	while (s[i])
	{
		if (*p == c)
			return (p);
		i++;
		p--;
	}
	if (*p == c)
		return (p);
	return (NULL);
}
