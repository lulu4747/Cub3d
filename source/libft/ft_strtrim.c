/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 15:15:38 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 19:51:14 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_count(char *s1, char *set)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (set[j] != s1[i])
			j++;
		if (set[j] == s1[i])
		{
			i++;
			j = 0;
		}
		if (s1[i] == 0)
			return (-1);
	}
	return (i);
}

int		ft_count_rev(char *s1, char *set)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	j = ft_strlen(s1) - 1;
	while (set[i])
	{
		if (set[i] != s1[j])
			i++;
		if (set[i] == s1[j])
		{
			j--;
			count++;
			i = 0;
		}
	}
	return (count);
}

char	*ft_returnnull(char *str)
{
	if (!(str = malloc(sizeof(char))))
		return (NULL);
	str[0] = 0;
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	int		c;
	char	*str;

	if (!s1 || !set)
		return ((char *)s1);
	i = 0;
	str = NULL;
	if (s1[0] == 0)
		return ((char *)s1);
	if ((c = ft_count((char *)s1, (char *)set)) == -1)
		return (ft_returnnull(str));
	len = ft_count_rev((char *)s1, (char *)set);
	len = ft_strlen((char *)s1) - len - c;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = 0;
	while (i < len)
		str[i++] = s1[c++];
	return (str);
}
