/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error_Management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:49:44 by lfourage          #+#    #+#             */
/*   Updated: 2020/03/07 07:42:32 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int		ft_check_params(t_cub *t)
{
	int	er;

	er = SUCCESS;
	t->r == NULL ? er = write(2, "Error\nNo resolution ", 20) : 0;
	if (er == SUCCESS && t->no == NULL)
		er = write(2, "Error\nNo path for north texture ", 32);
	if (er == SUCCESS && t->we == NULL)
		er = write(2, "Error\nNo path for west texture ", 30);
	if (er == SUCCESS && t->ea == NULL)
		er = write(2, "Error\nNo path for east texture ", 30);
	if (er == SUCCESS && t->so == NULL)
		er = write(2, "Error\nNo path for south texture ", 32);
	if (er == SUCCESS && t->s == NULL)
		er = write(2, "Error\nNo path for sprite texture ", 33);
	if (er == SUCCESS && t->f == -1)
		er = write(2, "Error\nNo color for floor ", 25);
	if (er == SUCCESS && t->c == -1)
		er = write(2, "Error\nNo color for ceiling ", 27);
	if (er == SUCCESS && t->map == NULL)
		er = write(2, "Error\nNo map ", 13);
	er != SUCCESS ? write(2, "found in map file\n", 18) : 0;
	er != SUCCESS ? er = ERROR : 0;
	return (er);
}

static void	ft_errorbis(int error, t_cub *t)
{
	if (error == ERR_XPM)
	{
		write(2, "No xpm file found for \"", 23);
		if (t->no->img == NULL)
			ft_putstr_fd(t->no->path, 2);
		else if (t->so->img == NULL)
			ft_putstr_fd(t->so->path, 2);
		else if (t->ea->img == NULL)
			ft_putstr_fd(t->ea->path, 2);
		else if (t->we->img == NULL)
			ft_putstr_fd(t->we->path, 2);
		else if (t->s->img == NULL)
			ft_putstr_fd(t->s->path, 2);
		write(2, "\"", 1);
	}
}

void	ft_error(int error, t_cub *t)
{
	write (2, "Error\n", 6);
	error == NO_SPAWN ? write(2, "No spawning point found in map\n", 31) : 0;
	error == ERR_INIT ? write(2, "init error\n", 11) : 0;
	error == ERR_NWIN ? write(2, "new_window error\n", 17) : 0;
	error == ERR_OPEN ? write(2, "Can't open map file\n", 20) : 0;
	error == ERR_MALLOC ? write(2, "malloc error\n", 13) : 0;
	error == NO_MAP ? write(2, "No map found in map file\n", 25) : 0;
	error == OPN_MAP ? write(2, "Opened map\n", 11) : 0;
	error == UKN_OBJ ? write(2, "Unknowned object in map\n", 24) : 0;
	error == ERR_NOPARAMS ? write(2, "No file found for map parameters\n", 33) : 0;
	error == ERR_XPM ? ft_errorbis(error, t) : 0;
	error > 0 ? write(2, "2 or more spawning points found in map\n", 39) : 0;
	kill(t);
}

void	ft_identifier_error(int type)
{
	type == R ? write(2, "\"R\" identifier in map file\n", 27) : 0;
	type == NO ? write(2, "\"NO\" identifier in map file\n", 28) : 0;
	type == SO ? write(2, "\"SO\" identifier in map file\n", 28) : 0;
	type == WE ? write(2, "\"WE\" identifier in map file\n", 28) : 0;
	type == EA ? write(2, "\"EA\" identifier in map file\n", 28) : 0;
	type == S ? write(2, "\"S\" identifier in map file\n", 27) : 0;
	type == F ? write(2, "\"F\" identifier in map file\n", 27) : 0;
	type == C ? write(2, "\"C\" identifier in map file\n", 27) : 0;
	return ;
}

int		ft_double_entry_check(int type, t_cub *t)
{
	int error;

	error = FALSE;
	type == R && t->r != NULL ? error-- : 0;
	type == NO && t->no->path != NULL ? error-- : 0;
	type == SO && t->so->path != NULL ? error-- : 0;
	type == WE && t->we->path != NULL ? error-- : 0;
	type == EA && t->ea->path != NULL ? error-- : 0;
	type == S && t->s->path != NULL ? error-- : 0;
	type == F && t->f != ERROR ? error-- : 0;
	type == C && t->c != ERROR ? error-- : 0;
	if (error == ERROR)
		write(2, "Error\n2 or more entries for ", 28);
	return (error);
}
