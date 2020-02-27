/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/11 16:47:22 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/21 16:47:11 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_c(const char *str, int c)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_join(char *dst, const char *src, size_t len)
{
	unsigned long	dstlen;
	char			*ret;
	unsigned long	srclen;

	dstlen = ft_strlen_c(dst, 0);
	srclen = 0;
	if (!(ret = malloc(sizeof(char) * (dstlen + len + 1))))
		return (NULL);
	while (srclen <= dstlen)
	{
		ret[srclen] = dst[srclen];
		srclen++;
	}
	srclen = 0;
	while (srclen < len)
	{
		ret[dstlen] = src[srclen];
		dstlen++;
		srclen++;
	}
	ret[dstlen] = 0;
	return (ret);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned long	i;
	char			*r;

	if (!s)
		return ((char *)s);
	i = 0;
	if (!(r = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (ft_strlen_c(s, 0) < start)
		return (r);
	while (i < len)
	{
		r[i] = s[start + i];
		i++;
	}
	r[i] = 0;
	return (r);
}

t_list	*ft_lstcat(t_list **statik, t_list **first)
{
	t_list	*cat;

	if ((*statik)->next)
	{
		cat = (*statik)->next;
		free((*statik)->content);
		(*statik)->content = NULL;
		free(*statik);
		*statik = cat;
	}
	else if (*first)
	{
		free((*first)->content);
		free(*first);
		(*first)->content = NULL;
		*first = NULL;
	}
	return (*first);
}

char	*ft_fill_line(char **statik, char **line, size_t len)
{
	char	*to_free;
	size_t	statiklen;

	to_free = *statik;
	statiklen = ft_strlen_c(*statik + len, 0) - 1;
	if (!(*line = ft_substr(*statik, 0, len)))
		return (NULL);
	if (!(*statik = ft_substr(*statik, len + 1, statiklen)))
		return (NULL);
	free(to_free);
	return (*line);
}
