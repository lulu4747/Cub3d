/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 14:13:53 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/21 16:53:50 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_ret(char **statik, char **line, size_t len, int rd)
{
	char	*tmp;
	int		eof;

	tmp = *statik;
	eof = 0;
	if (rd > 0)
	{
		if (tmp[len] != '\n')
			eof++;
		if (!(*line = ft_fill_line(statik, line, len)))
			return (-1);
		if ((tmp = *statik) && tmp[0] == 0 && eof > 0)
			return (0);
		return (1);
	}
	else if (tmp && tmp[0] != 0)
	{
		if (!(*line = ft_fill_line(statik, line, len)))
			return (-1);
		return (rd);
	}
	if (!(*line = malloc(sizeof(char))))
		return (-1);
	*line[0] = 0;
	return (rd);
}

char	*ft_fill_statik(char *buf, char *statik, int rd)
{
	char	*to_free;

	if (!statik)
	{
		if (!((statik) = ft_substr(buf, 0, rd)))
			return (NULL);
	}
	else
	{
		to_free = statik;
		if (!(statik = ft_join(statik, buf, rd)))
			return (NULL);
		free(to_free);
	}
	return (statik);
}

int		get_one_line(char **statik, char **line, size_t len, int fd)
{
	char		*buf;
	char		*tmp;
	int			rd;

	buf = NULL;
	tmp = *statik;
	rd = BUFFER_SIZE;
	while (!*statik || (tmp[len] != '\n' && rd == BUFFER_SIZE))
	{
		if (!(buf = malloc(sizeof(char) * BUFFER_SIZE + 1)))
			return (-1);
		buf[BUFFER_SIZE] = 0;
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd <= 0)
		{
			free(buf);
			return (ft_ret(statik, line, len, rd));
		}
		if (!(*statik = ft_fill_statik(buf, *statik, rd)))
			return (-1);
		len = ft_strlen_c(*statik, '\n');
		tmp = *statik;
		free(buf);
	}
	return (ft_ret(statik, line, len, rd));
}

t_list	*get_statik(int fd, t_list **first)
{
	t_list	*finder;

	if (!*first)
	{
		if (!(*first = malloc(sizeof(t_list))))
			return (NULL);
		(*first)->index = fd;
		(*first)->next = NULL;
		(*first)->content = NULL;
	}
	finder = *first;
	while (finder->index != fd)
	{
		if (!finder->next)
		{
			if (!(finder->next = malloc(sizeof(t_list))))
				return (NULL);
			finder->next->index = fd;
			finder->next->next = NULL;
			finder->next->content = NULL;
		}
		finder = finder->next;
	}
	return (finder);
}

int		get_next_line(int fd, char **line)
{
	static t_list	*first;
	t_list			*statik;
	size_t			len;
	int				ret;

	*line = NULL;
	len = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || line == NULL)
		return (-1);
	if (!(statik = get_statik(fd, &first)))
		return (ft_ret(NULL, NULL, 0, -1));
	if (statik->content)
		len = ft_strlen_c(statik->content, '\n');
	ret = get_one_line(&statik->content, line, len, fd);
	if (ret <= 0 && statik->content)
		first = ft_lstcat(&statik, &first);
	return (ret);
}
