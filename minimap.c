/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:50:00 by lfourage          #+#    #+#             */
/*   Updated: 2020/02/25 19:18:47 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

t_grid	*g_setup(t_cub *t, t_grid *g, char **map)
{
	if (!(g = malloc(sizeof(t_grid))))
		ft_error(ERR_MALLOC, t);
	g->yl = 0;
	g->xl = ft_strlen(map[g->yl]) - 1;
	while (map[g->yl + 1])
		g->yl++;
	g->sqcx = ((g->xl - 1) % 2 != 0 ) ? 0.5 : 0;
	g->sqcy = ((g->yl - 1) % 2 != 0 ) ? 0.5 : 0;
	g->xc = (g->xl) / 2;
	g->yc = (g->yl) / 2;
	return (g);
}
