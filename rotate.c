/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:03:40 by lfourage          #+#    #+#             */
/*   Updated: 2020/02/27 11:45:28 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	move(int key, char **map, t_cam *c)
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

void	straff(int key, char **map, t_cam *c)
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

void	rotate(int key, t_cam *c)
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
