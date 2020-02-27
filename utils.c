/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:23:06 by lfourage          #+#    #+#             */
/*   Updated: 2020/02/27 11:45:23 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	jump(t_ray *r, float time)
{
	if (time <= 100 && time <= 350)
		time = 100;
	else if (time > 350)
		time = 350 - time - 10;
	r->wallstart += time;
	r->wallend += time;
}

static	void	walldrawer(t_cub *t, t_ray *r, int x)
{
	int	y;

	if (t->jump == TRUE)
		jump(r, t->time);
	y = r->wallend;
	while (y > r->wallstart)
	{
		t->tdata[x + y * t->r[X] - 1] = 0x50188c;
		y--;
	}
}

static	t_ray	*get_drawparams(t_cub *t, t_cam *c, t_ray *r)
{
	if (r->side == EW)
		r->lenght = (r->x - c->posx + (1 - c->stepx) / 2) / r->dirx;
	else
		r->lenght = (r->y - c->posy + (1 - c->stepy) / 2) / r->diry;
	r->height = (int)(t->r[Y] / r->lenght);
	r->wallstart = -r->height / 2 + t->r[Y] / 2;
	r->wallstart < 0 ? r->wallstart = 0 : 0;
	r->wallend = r->height / 2 + t->r[Y] / 2;
	r->wallend >= t->r[Y] ? r->wallend = t->r[Y] - 1 : 0;
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
			r->side = EW;
		}
		else
		{
			r->sdisy += r->ddisy;
			r->y += c->stepy;
			r->side = NS;
		}
		r->hit = t->map[r->y][r->x] == WALL ? TRUE : FALSE;
	}
	r = get_drawparams(t, c, r);
	return (r);
}

static	int		raysweep(t_cub *t, t_cam *c, t_ray *r, int x)
{
	if (!(r = malloc(sizeof(t_ray))))
		return (ERROR);
	if (x < t->r[X])
	{
		r->camx = (2 * x / (float)t->r[X] - 1);
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
			r->sdisx = (c->sqposx + 1 - c->posx) * r->ddisx;
		}
		if (r->diry < 0)
		{
			c->stepy = -1;
			r->sdisy = (c->posy - c->sqposy) * r->ddisy;
		}
		else
		{
			c->stepy = 1;
			r->sdisy = (c->sqposy + 1 - c->posy) * r->ddisy;
		}
		r = dda(t, c, r);
		walldrawer(t, r, x);
		if (raysweep(t, c, r->next, x + 1) == ERROR)
			return (ERROR);
	}
	free(r);
	return (SUCCESS);
}

void	raycasting(t_cub *t, t_cam *c)
{
	raysweep(t, c, c->r, 0) == ERROR ? ft_error(ERR_MALLOC, t) : 0;
}

void	gomove(t_cub *t)
{
	t->keyone != NONE ? rotate(t->keyone, t->ca) : 0;
	t->keytwo != NONE ? move(t->keytwo, t->map, t->ca) : 0;
	t->keythree != NONE ? straff(t->keythree, t->map, t->ca) : 0;
}

int		loophook(t_cub *t)
{
	drawbg(t);
	raycasting(t, t->ca);
	putimg(t, t->bg, 0, 0);
	if (t->press == TRUE)
		gomove(t);
	if (t->jump == TRUE)
	{
		t->time == 450 ? t->jump = FALSE : 0;
		t->time += 10;
	}
//	if (t->minmap == TRUE)
		//minimap(t);
	return (SUCCESS);
}

t_cam	*cam_setup(t_cam *c)
{
	if (!(c = malloc(sizeof(t_cam))))
		return(NULL);
	c->posx = 0;
	c->posy = 0;
	c->sqposx = 0;
	c->sqposy = 0;
	c->dirx = 0;
	c->diry = 0;
	c->planex = 0;
	c->planey = 0;
	c->now = 0;
	c->before = 0;
	c->stepx = 0;
	c->stepy = 0;
	c->r = NULL;
	return (c);
}

t_mmap	*mm_setup(t_mmap *m)
{
	if (!(m = malloc(sizeof(t_mmap))))
		return (NULL);
	m->mnmap = NULL;
	m->mwall = NULL;
	m->grid = NULL;
	m->mdata = NULL;
	m->mwdata = NULL;
	return (m);
}

t_cub	*t_setup(t_cub *t)
{
	if (!(t = malloc(sizeof(t_cub))))
		ft_error(ERR_MALLOC, t);
	t->r = NULL;
	t->no = NULL;
	t->we = NULL;
	t->ea = NULL;
	t->so = NULL;
	t->s = NULL;
	t->f = -1;
	t->c = -1;
	t->map = NULL;
	t->scr = NULL;
	t->init = NULL;
	t->bg = NULL;
	t->tdata = NULL;
	t->minmap = FALSE;
	t->press = FALSE;
	t->keyone = NONE;
	t->keytwo = NONE;
	t->keythree = NONE;
	t->jump = FALSE;
	t->time = 0;
	if (!(t->m = mm_setup(t->m)))
		ft_error(ERR_MALLOC, t);
	if (!(t->ca = cam_setup(t->ca)))
		ft_error(ERR_MALLOC, t);
	t->g = NULL;
	return (t);
}

void	putimg(t_cub *t, void *target, int x, int y)
{
	mlx_put_image_to_window(t->init, t->scr, target, x , y);
}

void	ft_loop(t_cub *t)
{
	mlx_hook(t->scr, KEY_PRESS, 0, &key, t);
	mlx_hook(t->scr, KEY_RELEASE, 0, &release, t);
	mlx_loop(t->init);
}

void	freeray(t_ray *r)
{
	r->next != NULL ? freeray(r->next) : 0;
	free(r);
}

void	freecam(t_cub *t, t_cam *c)
{
	c->r != NULL ? freeray(c->r) : 0;
}

void	freemmap(t_cub *t, t_mmap *m)
{
	m->grid != NULL ? free(m->grid) : 0;
	m->mnmap != NULL ? mlx_destroy_image(t->init, m->mnmap) : 0;
	m->mwall != NULL ? mlx_destroy_image(t->init, m->mwall) : 0;
}

void	freeall(t_cub *t)
{
	int i;

	i = -1;
	freecam(t, t->ca);
	freemmap(t, t->m);
	t->r != NULL ? free(t->r) : 0;
	t->no != NULL ? free(t->no) : 0;
	t->we != NULL ? free(t->we) : 0;
	t->ea != NULL ? free(t->ea) : 0;
	t->so != NULL ? free(t->so) : 0;
	t->s != NULL ? free(t->s) : 0;
	if (t->map != NULL)
	{
		while (t->map[++i])
			free(t->map[i]);
		free(t->map);
	}
	t->scr != NULL ? mlx_destroy_window(t->init, t->scr) : 0;
	t->init != NULL ? free(t->init) : 0;
	free(t);
}

void	kill(t_cub *t)
{
	freeall(t);
	exit (0);
}
