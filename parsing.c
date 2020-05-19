/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:50:18 by lfourage          #+#    #+#             */
/*   Updated: 2020/03/12 11:36:44 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int ft_resolution(t_cub *t, char *line)
{
	if (ft_double_entry_check(R, t) == ERROR)
		return (ERROR);
	if (!(t->r = malloc(sizeof(int) * 2)))
		ft_error(ERR_MALLOC, t);
	while (ft_isdigit(*line) != TRUE && *line)
		line++;
	if (!(*line))
	{
		write(2, "Error\nNo witdh found for ", 23);
		return (ERROR);
	}
	t->r[X] = ft_atoi(line);
	while (ft_isdigit(*line) == TRUE && *line)
		line++;
	while (ft_isdigit(*line) != TRUE && *line)
		line++;
	if (!(*line))
	{
		write(2, "Error\nNo height found for ", 24);
		return (ERROR);
	}
	t->r[Y] = ft_atoi(line);
	return (R);
}

int ft_texture(t_cub *t, char *line, int type)
{
	char	*tmp;

	tmp = NULL;
	if (ft_double_entry_check(type, t) == ERROR)
		return (ERROR);
	while (*line != '.' && *line)
		line++;
	if (!(line))
	{
		write(2, "Error\nNo path found for ", 24);
		return (ERROR);
	}
	if (!(tmp = ft_strdup(line)))
		ft_error(ERR_MALLOC, t);
	type == NO ? t->no->path = tmp : 0;
	type == SO ? t->so->path = tmp : 0;
	type == WE ? t->we->path = tmp : 0;
	type == EA ? t->ea->path = tmp : 0;
	type == S ? t->s->path = tmp : 0;
	return (type);
}

int ft_color(t_cub *t, char *line, int type)
{
	if (ft_double_entry_check(type, t) == ERROR)
		return (ERROR);
	while (ft_isdigit(*line) != TRUE && *line)
		line++;
	if (!(line))
	{
		write(2, "Error\nNo value found for ", 25);
		return (ERROR);
	}
	type == F ? t->f = ft_atoi(line) << 16 : 0;
	type == C ? t->c = ft_atoi(line) << 16 : 0;
	while (ft_isdigit(*line) == TRUE && *line)
		line++;
	while (ft_isdigit(*line) != TRUE && *line)
		line++;
	type == F ? t->f += ft_atoi(line) << 8 : 0;
	type == C ? t->c += ft_atoi(line) << 8 : 0;
	while (ft_isdigit(*line) == TRUE && *line)
		line++;
	while (ft_isdigit(*line) != TRUE && *line)
		line++;
	type == F ? t->f += ft_atoi(line) : 0;
	type == C ? t->c += ft_atoi(line) : 0;
	return (type);
}

int	ft_map(t_cub *t, char *line, int fd)
{
	char	*buf;
	int		check;

	if (!(buf = ft_strdup(line)))
		ft_error(ERR_MALLOC, t);
	if (!(buf = ft_strjoin(buf, "\n")))
		ft_error(ERR_MALLOC, t);
	while ((check = get_next_line(fd, &line)) != 0)
	{
		if (check == ERROR)
		{
			write(2, "Error\nGNL failure\n", 18);
			return (ERROR);
		}
		if (!(buf = ft_strjoin(buf, line)))
			ft_error(ERR_MALLOC, t);
		if (!(buf = ft_strjoin(buf, "\n")))
			ft_error(ERR_MALLOC, t);
	}
	if (!(t->map = ft_split(buf, '\n')))
		ft_error(ERR_MALLOC, t);
	return (ft_check_map(t));
}

int	ft_parsing(t_cub *t, int fd)
{
	char	*line;
	int		check;

	line = NULL;
	while ((check = get_next_line(fd, &line)) != 0)
	{
		if (check == ERROR)
		{
			write(2, "Error\nGNL failure\n", 18);
			return (ERROR);
		}
		check = ft_get_type(line, t);
		if ((check = ft_parse_line(t, line, check, fd)) == ERROR)
			return (ERROR);
		free(line);
		line = NULL;
	}
	check = ft_check_params(t);
	return (check);
}
