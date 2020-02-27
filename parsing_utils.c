/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:50:29 by lfourage          #+#    #+#             */
/*   Updated: 2020/02/25 19:18:56 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ft_check_object(int c, char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

int	ft_map_browser(t_cub *t, int len)
{
	int spawn;
	int y;
	int x;

	spawn = 0;
	y = 1;
	while (t->map[y])
	{
		x = 0;
		if (t->map[y][0] != WALL || t->map[y][len] != WALL)
			ft_error(OPN_MAP, t);
		while (x < len)
		{
			if (t->map[y][x] == 'N' || t->map[y][x] == 'S'
				|| t->map[y][x] == 'E' || t->map[y][x] == 'W')
			{
				spawn++;
				spawn == 1 ? spawnloc(t, t->ca, x, y) : 0;
			}
			if (ft_check_object(t->map[y][x], "012NSEW") == ERROR)
				ft_error(UKN_OBJ, t);
			x++;
		}
		y++;
	}
	y--;
	if (spawn != SUCCESS)
		ft_error(spawn, t);
	return (y);
}

int	ft_check_map(t_cub *t)
{
	int len;
	int rw;
	int ln;

	rw = 0;
	ln = 0;
	len = ft_strlen(t->map[rw]) - 1;
	while (t->map[rw][ln])
	{
		if (t->map[rw][ln] != WALL)
			ft_error(OPN_MAP, t);
		ln++;
	}
	if ((rw = ft_map_browser(t, len)) == ERROR)
		return (ERROR);
	ln = 0;
	while (t->map[rw][ln])
	{
		if (t->map[rw][ln] != WALL)
			ft_error(OPN_MAP, t);
		ln++;
	}
	return (SUCCESS);
}

int	ft_get_type(char *line, t_cub *t)
{
	int		ret;

	t->tmp = NULL;
	ret = R;
	while (t->tmp == NULL && ret < END)
	{
		ret == R ? t->tmp = ft_strnstr(line, "R", 1) : 0;
		ret == NO && t->tmp == NULL ? t->tmp = ft_strnstr(line, "NO", 2) : 0;
		ret == SO && t->tmp == NULL ? t->tmp = ft_strnstr(line, "SO", 2) : 0;
		ret == WE && t->tmp == NULL ? t->tmp = ft_strnstr(line, "WE", 2) : 0;
		ret == EA && t->tmp == NULL ? t->tmp = ft_strnstr(line, "EA", 2) : 0;
		ret == S && t->tmp == NULL ? t->tmp = ft_strnstr(line, "S", 1) : 0;
		ret == F && t->tmp == NULL ? t->tmp = ft_strnstr(line, "F", 1) : 0;
		ret == C && t->tmp == NULL ? t->tmp = ft_strnstr(line, "C", 1) : 0;
		ret == MAP && t->tmp == NULL ? t->tmp = ft_strnstr(line, "1", 1) : 0;
		t->tmp == NULL ? ret++ : 0;
	}
	return (ret);
}

int ft_parse_line(t_cub *t, char *line, int check, int fd)
{
	int type;

	type = check;
	check = check == R ? ft_resolution(t, t->tmp) : check;
	check = check >= NO && check <= S ? ft_texture(t, t->tmp, check) : check;
	check = check == F || check == C ? ft_color(t, t->tmp, check) : check;
	check = check == MAP ? ft_map(t, line, fd) : check;
	if (check == ERROR)
	{
		ft_identifier_error(type);
		return (ERROR);
	}
	return (SUCCESS);
}
