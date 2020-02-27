/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/13 13:02:15 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 19:42:52 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*r;

	if (!s1 || !s2)
		return ((char *)s1);
	i = -1;
	j = ft_strlen((char *)s1);
	len = j + ft_strlen((char *)s2) + 1;
	if ((r = malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	while (s1[++i])
		r[i] = s1[i];
	i = 0;
	while (s2[i])
	{
		r[j] = s2[i];
		i++;
		j++;
	}
	r[j] = 0;
	return (r);
}
