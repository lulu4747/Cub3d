/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:38:31 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 17:56:57 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_checkneedle(const char *haystack, const char *needle, int i)
{
	int t;

	t = 0;
	while (needle[t])
	{
		if (needle[t] == haystack[i])
		{
			t++;
			i++;
		}
		else
			return (0);
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned long	i;
	int				t;
	char			*r;

	if (needle[0] == 0)
	{
		r = (char *)haystack;
		return (r);
	}
	i = 0;
	t = 0;
	while (i < len)
	{
		if (haystack[i] == needle[t]
		&& (ft_strlen((char *)needle) + i <= len))
		{
			if (ft_checkneedle(haystack, needle, i) == 1)
			{
				r = (char *)haystack + i;
				return (r);
			}
		}
		i++;
	}
	return (NULL);
}
