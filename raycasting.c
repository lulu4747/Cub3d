/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 09:44:27 by lfourage          #+#    #+#             */
/*   Updated: 2020/03/12 12:40:22 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	jump(t_cub *t, t_ray *r)
{
	if (t->time >= 1000)
		t->jump = FALSE;
	t->time = t->jump == TRUE ? t->time + 10 : t->time - 10;
	printf(" -%f- ", t->time);
	r->height += t->time;
}

static void			walldrawer(t_cub *t, t_img *all, t_ray *r, int x)
{
	unsigned int	color;
	int				y;
	int				txty;

	r->step = 1.0 * r->walltxt->y / r->height;
	r->txtpos = (r->wallstart - t->r[Y] / 2 + r->height / 2) * r->step;
	y = -1;
	while (++y < r->wallstart)
		all->data[x + y * t->r[X] - 1] = t->f;
	while (++y < r->wallend)
	{
		txty = (int)r->txtpos & (r->walltxt->y - 1);
		r->txtpos += r->step;
		color = r->walltxt->img->data[(int)(r->walltxt->y * txty + r->txtx)];
		all->data[x + y * t->r[X] - 1] = color;
	}
	while (++y < t->r[Y] - 1)
		all->data[x + y * t->r[X] - 1] = t->c;
}

static	t_ray	*txt_param(t_cub *t, t_ray *r)
{
	r->side == NO ? r->walltxt = t->no : 0;
	r->side == SO ? r->walltxt = t->so : 0;
	r->side == WE ? r->walltxt = t->we : 0;
	r->side == EA ? r->walltxt = t->ea : 0;
	r->txtx = r->wallx * (float)r->walltxt->x;
	if (r->side == WE || r->side == SO)
		r->txtx = r->walltxt->x - r->txtx - 1;
	return (r);
}

static	t_ray	*get_drawparams(t_cub *t, t_cam *c, t_ray *r)
{
	if (r->side == EA || r->side == WE)
	{
		r->lenght = (r->x - c->posx + (1 - c->stepx) / 2) / r->dirx;
		r->wallx = c->posy + r->lenght * r->diry;
	}
	else
	{
		r->lenght = (r->y - c->posy + (1 - c->stepy) / 2) / r->diry;
		r->wallx = c->posx + r->lenght * r->dirx;
	}
	r->wallx -= (int)(r->wallx); //position x exacte du mur (x relatif au mur)
	r = txt_param(t, r);
	r->height = (int)(t->r[Y] / r->lenght);
//	if (t->time != 0)
//		jump(t, r);
	r->wallstart = -r->height / 2 + t->r[Y] / 2;
	r->wallstart < 0 ? r->wallstart = 0 : 0;
	r->wallend = r->height / 2 + t->r[Y] / 2;
	r->wallend >= t->r[Y] ? r->wallend = t->r[Y] - 1 : 0;
//	printf("%f\n", r->height);
	return (r);
}

static	t_ray	*dda(t_cub *t, t_cam *c, t_ray *r)
{
	r->x = c->sqposx;
	r->y = c->sqposy;
	while (r->hit != TRUE)
	{
		if (r->sdisx < r->sdisy)
		{
			r->sdisx += r->ddisx;
			r->x += c->stepx;
			r->side = r->dirx < 0 ? EA : WE;
		}
		else
		{
			r->sdisy += r->ddisy;
			r->y += c->stepy;
			r->side = r->diry < 0 ? SO : NO;
		}
		r->hit = t->map[r->y][r->x] == WALL ? TRUE : FALSE;
	}
	r = get_drawparams(t, c, r);
	return (r);
}

void			r_reset(t_cam *c, t_ray *r, int x)
{
	r->hit = FALSE;
	r->side = FALSE;
	r->walltxt = NULL;
	r->dirx = c->dirx + c->planex * r->camx;
	r->diry = c->diry + c->planey * r->camx;
	r->ddisx = fabsf(1 / r->dirx);
	r->ddisy = fabsf(1 / r->diry);
	if (r->dirx < 0)
	{
		c->stepx = -1;
		r->sdisx = (c->posx - c->sqposx) * r->ddisx;
	}
	else
	{
		c->stepx = 1;
		r->sdisx = (c->sqposx + 1.0 - c->posx) * r->ddisx;
	}
	if (r->diry < 0)
	{
		c->stepy = -1;
		r->sdisy = (c->posy - c->sqposy) * r->ddisy;
	}
	else
	{
		c->stepy = 1;
		r->sdisy = (c->sqposy + 1.0 - c->posy) * r->ddisy;
	}

}

static	int		raysweep(t_cub *t, t_cam *c, t_ray *r, int x)
{
	if (x < t->r[X])
	{
		r_reset(c, r, x);
		r->camx = (2 * x / (float)t->r[X] - 1);
		r = dda(t, c, r);
		walldrawer(t, t->all, r, x);
		raysweep(t, c, r, x + 1);
	}
	return (SUCCESS);
}

static t_spr	*lstsorter(t_spr *f)
{
	t_spr	*tmp;
	t_spr	*ftmp;
	t_spr	*ntmp;
	int	bl;

	tmp = f->next;
	ftmp = f;
	bl = 0;
	while (ftmp)
	{
		while (tmp)
		{
			if (ftmp->d >= tmp->d)
				tmp = tmp->next;
			else
			{
				ntmp = ftmp->next;
				ftmp->next = tmp->next;
				tmp->next = ntmp;
				bl == 0 ? f = tmp : 0;
				ftmp = f;
				tmp = f->next;
			}
		}
		bl = 1;
		ftmp = ftmp->next;
		if (ftmp)
			tmp = ftmp->next;
	}
	return (f);
}

static void	sorter(t_cam *c, t_spr *spr)
{
	int	i;
	t_spr	*f;

	i = 0;
	f = spr;
	while (i < spr->d)
	{
		spr->d = sqrt(((spr->x - c->posx) * (spr->x - c->posx)) 
				+ ((spr->y - c->posy) * (spr->y - c->posy)));
		if (spr->next)
			spr = spr->next;
		i++;
	}
	spr = lstsorter(f);
}

static void	sprites(t_cub *t, t_spr *spr, t_cam *c)
{
	sorter(c, spr);
}

static void	show(t_spr *spr)
{
	printf("|%d%d| |%d%d|\n", (int)spr->x, (int)spr->y, (int)spr->next->x, (int)spr->next->y);
}

void	raycasting(t_cub *t, t_cam *c)
{
	raysweep(t, c, c->r, 0);
	sprites(t, t->spr, c);
	show(t->spr);
}
