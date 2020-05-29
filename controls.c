/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 09:41:56 by lfourage          #+#    #+#             */
/*   Updated: 2020/03/10 11:40:43 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

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
/*	if (key == SPACE && t->time == 0)
	{
		t->jump = TRUE;
		t->time = 10;
	}*/
	printf("%d\n", key);
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

