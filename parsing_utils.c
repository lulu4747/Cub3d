/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:50:29 by lfourage          #+#    #+#             */
/*   Updated: 2020/03/12 11:37:28 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	spr(t_spr *spr, int x, int y)
{
	while (spr->next != NULL)
		spr = spr->next;
	spr = spr->next;
	if (!(spr = malloc(sizeof(t_spr))))
		return (0);
	spr->x = x + 0.5;
	spr->y = y + 0.5;
	spr->r = 0;
	spr->next = NULL;
	return (1);
}

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

int	checkone(char c, int x, int y, t_cub *t)
{
	if (ft_check_object(c, "NSEW") == SUCCESS)
		return (1);
	if (c == '2')
	{
		if (t->spr == NULL)
		{
			if (!(t->spr = malloc(sizeof(t_spr))))
				ft_error(ERR_MALLOC, t);
			t->spr->x = x + 0.5;
			t->spr->y = y + 0.5;
			t->spr->r = 0;
			t->spr->d = 1;
			t->spr->next = NULL;
			return (0);
		}
		else
		{
			if (spr(t->spr, x, y) == 0)
				ft_error(ERR_MALLOC, t);
			t->spr->d += 1;
		}
		return (0);
	}
	if (ft_check_object(c, "0123") == ERROR)
		ft_error(UKN_OBJ, t);
	return (0);
}

static int	opnchecknd(t_cub *t, char **m, int x, int y)
{
	int bl;

	bl = 0;
	if (m[y][x] == '3')
	{
		if (y != 0 && (m[y - 1][x] == '0' || m[y - 1][x] == '2'))
		{
			m[y - 1][x] = '3';
			bl++;
		}
		if (x != 0 && (m[y][x - 1] == '0' || m[y][x - 1] == '2'))
		{
			m[y][x - 1] = '3';
			bl++;
		}
		if (m[y + 1] && (m[y + 1][x] == '0' || m[y + 1][x] == '2'))
		{
			m[y + 1][x] = '3';
			bl++;
		}
		if (m[y][x + 1] && (m[y][x + 1] == '0' || m[y][x + 1] == '2'))
		{
			m[y][x + 1] = '3';
			bl++;
		}
	}
	return (bl);
}

static void	opncheck(t_cub *t, char **m, int x, int y)
{
	m[y][x] = '3';
	while (m[y])
	{
		while (m[y][x])
		{
			if (m[y][x] == '3' && y != 0 && x != 0 
				&& m[y + 1] && m[y][x + 1])
			{
				if (opnchecknd(t, m, x, y) == 0)
					x++;
				else
				{
					x = 0;
					y = 0;
				}
			}
			else if (m[y][x] == '3')
			{
				printf("%d, %d\n", x, y);
				ft_error(OPN_MAP, t);
			}
			else
				x++;
		}
		y++;
		x = 0;
	}
}

int	ft_map_browser(t_cub *t, int len)
{
	int spawn;
	int y;
	int x;
	int bl;

	bl = 0;
	spawn = 0;
	y = 1;
	while (t->map[y])
	{
		x = 0;
		while (t->map[y][x])
		{
			spawn += checkone(t->map[y][x], x, y, t);
			if (spawn == SUCCESS && bl == 0)
			{
				spawnloc(t, t->ca, x, y);
				opncheck(t, t->map, t->ca->sqposx, t->ca->sqposy);
				bl++;
			}
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
	int rw;
	int ln;

	rw = 0;
	ln = 0;
	if ((rw = ft_map_browser(t)) == ERROR)
		return (ERROR);
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
