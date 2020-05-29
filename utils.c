/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:23:06 by lfourage          #+#    #+#             */
/*   Updated: 2020/03/12 12:19:10 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static void	spawndir(int ch, t_cam *c)
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

int		loophook(t_cub *t)
{
	//drawbg(t);
	raycasting(t, t->ca);
	putimg(t, t->all->img, 0, 0);
	if (t->press == TRUE)
		gomove(t);
	if (t->minmap == TRUE)
	{
		putimg(t, t->we->img->img, 0, 0);
		putimg(t, t->we->img->img, t->we->x, 0);
	}
	return (SUCCESS);
}

t_ray	*r_setup(t_ray *r)
{
	if (!(r = malloc(sizeof(t_ray))))
		return (NULL);
	r->walltxt = NULL;
	r->hit = FALSE;
	r->side = FALSE;
	return (r);
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
	c->stepx = 0;
	c->stepy = 0;
	if (!(c->r = r_setup(c->r)))
		return (NULL);
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

t_img	*img_setup(t_img *i)
{
	if (!(i = malloc(sizeof(t_img))))
		return (NULL);
	i->img = NULL;
	i->data = NULL;
	i->bpp = FALSE;
	i->end = FALSE;
	return (i);
}

t_txt	*txt_setup(t_txt *txt)
{
	if (!(txt = malloc(sizeof(t_txt))))
		return (NULL);
	txt->path = NULL;
	txt->x = 0;
	txt->y = 0;
	if (!(txt->img = img_setup(txt->img)))
		return (NULL);
	return (txt);
}

t_cub	*t_setup(t_cub *t)
{
	if (!(t = malloc(sizeof(t_cub))))
		ft_error(ERR_MALLOC, t);
	if (!(t->no = txt_setup(t->no)))
		ft_error(ERR_MALLOC, t);
	if (!(t->we = txt_setup(t->we)))
		ft_error(ERR_MALLOC, t);
	if (!(t->ea = txt_setup(t->ea)))
		ft_error(ERR_MALLOC, t);
	if (!(t->so = txt_setup(t->so)))
		ft_error(ERR_MALLOC, t);
	if (!(t->s = txt_setup(t->s)))
		ft_error(ERR_MALLOC, t);
	t->f = -1;
	t->c = -1;
	t->map = NULL;
	t->scr = NULL;
	t->init = NULL;
	if (!(t->all = img_setup(t->all)))
		ft_error(ERR_MALLOC, t);
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
	mlx_hook(t->scr, KEY_PRESS, (1L << 0), &key, t);
	mlx_hook(t->scr, KEY_RELEASE, (1L << 1), &release, t);
	mlx_loop(t->init);
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
