/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:03:40 by lfourage          #+#    #+#             */
/*   Updated: 2020/03/10 11:40:18 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static void	move(int key, char **map, t_cam *c)
{
	int		x;
	int		y;
	float	ms;

	ms = 0.115;
	if (key == FORWARD)
	{
		x = c->posx + c->dirx * ms;
		y = c->posy + c->diry * ms;
		if (map[c->sqposy][x] == EMPTY)
			c->posx += c->dirx * ms;
		if (map[y][c->sqposx] == EMPTY)
			c->posy += c->diry * ms;
	}
	if (key == BACKWARD)
	{
		x = c->posx - c->dirx * ms;
		y = c->posy - c->diry * ms;
		if (map[c->sqposy][x] == EMPTY)
			c->posx -= c->dirx * ms;
		if (map[y][c->sqposx] == EMPTY)
			c->posy -= c->diry * ms;
	}
	c->sqposx = (int)c->posx;
	c->sqposy = (int)c->posy;
}

static void	straff(int key, char **map, t_cam *c)
{
	int		x;
	int		y;
	float	ms;

	ms = 0.119;
	if (key == STRAFF_R)
	{
		x = c->posx + c->planex * ms;
		y = c->posy + c->planey * ms;
		if (map[c->sqposy][x] == EMPTY)
			c->posx += c->planex * ms;
		if (map[y][c->sqposx] == EMPTY)
			c->posy += c->planey * ms;
	}
	if (key == STRAFF_L)
	{
		x = c->posx - c->planex * ms;
		y = c->posy - c->planey * ms;
		if (map[c->sqposy][x] == EMPTY)
			c->posx -= c->planex * ms;
		if (map[y][c->sqposx] == EMPTY)
			c->posy -= c->planey * ms;
	}
	c->sqposx = (int)c->posx;
	c->sqposy = (int)c->posy;
}

static void	rotate(int key, t_cam *c)
{
	float	oldx;
	float	oldxp;
	float	rs;
	float	prs;

	oldx = c->dirx;
	oldxp = c->planex;
	rs = key == LOOK_R ? 1.8 * (M_PI/180) : -1.8 * (M_PI/180);
	c->dirx = c->dirx * cos(rs) - c->diry * sin(rs);
	c->diry = oldx * sin(rs) + c->diry * cos(rs);
	c->planex = c->planex * cos(rs) - c->planey * sin(rs);
	c->planey =  oldxp * sin(rs) + c->planey * cos(rs);
}

static void	showmgo(t_txt *no, t_cub *t)
{
	
}

void		gomove(t_cub *t)
{
	t->keyone != NONE ? rotate(t->keyone, t->ca) : 0;
	t->keytwo != NONE ? move(t->keytwo, t->map, t->ca) : 0;
	t->keythree != NONE ? straff(t->keythree, t->map, t->ca) : 0;
//	t->minimap != FALSE ? showmgo(t->no, t) : 0;
}
