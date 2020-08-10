/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 13:50:26 by lfourage          #+#    #+#             */
/*   Updated: 2020/03/12 12:44:25 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	makeall(t_cub *t, t_img *i)
{
	i->img = mlx_new_image(t->init, t->r[X], t->r[Y]);
	i->data = (int *)mlx_get_data_addr(i->img, &i->bpp, &i->s_l, &i->end);
}

t_txt	*follow_path(t_cub *t, t_txt *txt)
{
	if (!(txt->img->img = mlx_xpm_file_to_image(t->init, txt->path, &txt->x, &txt->y)))
		ft_error(ERR_XPM, t);
	txt->img->data = (int *)mlx_get_data_addr(txt->img->img, &txt->img->bpp, &txt->img->s_l, &txt->img->end);
	printf("%d\n", txt->img->s_l);
	return (txt);
}

t_cub	*get_textures(t_cub *t)
{
	printf("\n\nNO : ");
	t->no = follow_path(t, t->no);
	printf("\n\nSO : ");
	t->so = follow_path(t, t->so);
	printf("\n\nWE : ");
	t->we = follow_path(t, t->we);
	printf("\n\nEA : ");
	t->ea = follow_path(t, t->ea);
//	t->s = follow_path(t, t->s, t->no->img);
	return (t);
}

int		ft_start(t_cub *t)
{
	if (!(t->init = mlx_init()))
		return (ERR_INIT);
	if (!(t->scr = mlx_new_window(t->init, t->r[X], t->r[Y], "Cub3d")))
		return (ERR_NWIN);
	makeall(t, t->all);
	t = get_textures(t);
//	raycasting(t, t->ca);
//no	mlx_key_hook(t->scr, &key, t);
//	mlx_loop_hook(t->init, &loophook, t);
	return (SUCCESS);
}

void	mapparams(t_cub *t)
{
	int i;

	i = 0;
	printf("R  : x|%d|y|%d|\nNO : |%s|\nWE : |%s|\nEA : |%s|\nSO : |%s|\nS  : |%s|\nF  : |%x|\nC  : |%x|\nMap :\n", t->r[0], t->r[1], t->no->path, t->we->path, t->ea->path, t->so->path, t->s->path, t->f, t->c);
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
//	if (check == SUCCESS)
//		ft_loop(t);
//	else
//		ft_error(check, t);
	return (0);
}
