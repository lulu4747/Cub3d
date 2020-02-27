/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 13:50:26 by lfourage          #+#    #+#             */
/*   Updated: 2020/02/27 11:45:25 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	drawbg(t_cub *t)
{
	int				x;
	int				y;
	int				line;
	unsigned int	color;

	x = 0;
	y = 0;
	line = -1;
	color = mlx_get_color_value(t->init, t->c);
	while (x < (t->r[X] * t->r[Y]))
	{
		while (++line < t->r[X])
		{
			t->tdata[x] = color;
			x++;
		}
		line = -1;
		y == (t->r[Y] / 2) ? color = mlx_get_color_value(t->init, t->f) : 0;
		y ++;
	}
}

void	makebg(t_cub *t)
{
	t->bg = mlx_new_image(t->init, t->r[X], t->r[Y]);
	t->tdata = (int *)mlx_get_data_addr(t->bg, &t->tbpp, &t->ts_l, &t->tend);
	drawbg(t);
}

void	spawndir(int ch, t_cam *c)
{
	if (ch == 'N')
	{
		c->diry = -1;
		c->planex = 0.66;
	}
	if (ch == 'W')
	{
		c->dirx = -1;
		c->planey = -0.66;
	}
	if (ch == 'E')
	{
		c->dirx = 1;
		c->planey = 0.66;
	}
	if (ch == 'S')
	{
		c->diry = 1;
		c->planex = -0.66;
	}
}

void	spawnloc(t_cub *t, t_cam *c, int x, int y)
{
	t->g = g_setup(t, t->g, t->map);
	c->sqposx = x;
	c->sqposy = y;
	c->posx = x + 0.5;
	c->posy = y + 0.5;
	spawndir(t->map[y][x], c);
	t->map[y][x] = EMPTY;
}

int		key(int key, t_cub *t)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (key == ESC)
		kill(t);
	if (key == MINIMAP)
		t->minmap = (t->minmap == FALSE) ? TRUE : FALSE;
	if (key == LOOK_L || key == LOOK_R)
	{
		t->press = TRUE;
		t->keyone = key;
	}
	if (key == FORWARD || key == BACKWARD)
	{
		t->press = TRUE;
		t->keytwo = key;
	}
	if (key == STRAFF_L || key == STRAFF_R)
	{
		t->press = TRUE;
		t->keythree = key;
	}
	if (key == SPACE && t->jump == FALSE)
	{
		t->jump = TRUE;
		t->time = 10;
	}
//	printf("%d\n", key);
	return (SUCCESS);
}

int		release(int key, t_cub *t)
{
	if (key == LOOK_L || key == LOOK_R)
		t->keyone = NONE;
	if (key == FORWARD || key == BACKWARD)
		t->keytwo = NONE;
	if (key == STRAFF_L || key == STRAFF_R)
		t->keythree = NONE;
	if (t->keyone == NONE && t->keytwo == NONE && t->keythree == NONE)
		t->press = FALSE;
	return (SUCCESS);
}

int		ft_start(t_cub *t)
{
	if (!(t->init = mlx_init()))
		return (ERR_INIT);
	if (!(t->scr = mlx_new_window(t->init, t->r[X], t->r[Y], "Cub3d")))
		return (ERR_NWIN);
	makebg(t);
	raycasting(t, t->ca);
	mlx_key_hook(t->scr, &key, t);
	mlx_loop_hook(t->init, &loophook, t);
	return (SUCCESS);
}

void	mapparams(t_cub *t)
{
	int i;

	i = 0;
	printf("R  : x|%d|y|%d|\nNO : |%s|\nWE : |%s|\nEA : |%s|\nSO : |%s|\nS  : |%s|\nF  : |%x|\nC  : |%x|\nMap :\n", t->r[0], t->r[1], t->no, t->we, t->ea, t->so, t->s, t->f, t->c);
	while (t->map[i])
	{
		printf("%s\n", t->map[i]);
		i++;
	}
	printf("\n\nPlayer spawning pos :\nX[%f]Y[%f]\n", t->ca->posx, t->ca->posy);
}

int		main(int ac, char **av)
{
	t_cub	*t;
	int		check;
	int		fd;

	check = 1;
	t = t_setup(t);
	if (ac == 1)
		ft_error(ERR_NOPARAMS, t);
	while (ac > 1)
	{
		if ((fd = open(av[check], O_RDONLY)) == ERROR)
			ft_error(ERR_OPEN, t);
		if (ft_parsing(t, fd) != SUCCESS)
			kill(t);
		ac--;
		check++;
	}
	check = ft_start(t);
	mapparams(t);
	if (check == SUCCESS)
		ft_loop(t);
	else
		ft_error(check, t);
	return (0);
}
