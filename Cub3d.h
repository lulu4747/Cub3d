/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:49:29 by lfourage          #+#    #+#             */
/*   Updated: 2020/03/12 12:08:17 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** ---------------------------------Defines-------------------------------- **
*/

# define EMPTY 48
# define WALL 49
# define OBJ 50
# define X 0
# define Y 1
# define XS 2
# define YS 3
# define XG 4
# define YG 5
# define ERROR -1
# define SUCCESS 1
# define TRUE 1
# define FALSE 0
# define NONE 6
# define NS 1
# define EW 0
# define NO_SPAWN 0
# define ERR_INIT -1
# define ERR_NWIN -2
# define ERR_OPEN -3
# define ERR_MALLOC -4
# define NO_MAP -5
# define OPN_MAP -6
# define UKN_OBJ -7
# define ERR_NOPARAMS -8
# define ERR_XPM -9
# define R 0
# define NO 1
# define SO 2
# define WE 3
# define EA 4
# define S 5
# define F 6
# define C 7
# define MAP 8
# define END 9
# define FORWARD 122
# define STRAFF_L 113
# define BACKWARD 115
# define STRAFF_R 100
# define LOOK_UP 65362
# define LOOK_L 65361
# define LOOK_DWN 65364
# define LOOK_R 65363
# define SPACE 49
# define CTRL 256
# define MINIMAP 97
# define ESC 65307
# define KEY_PRESS 2
# define KEY_RELEASE 3

/*
** --------------------------------Includes-------------------------------- **
*/

# include "source/minilibx-linux-master/mlx.h"
# include "source/libft/libft.h"
# include "source/gnl/get_next_line.h"
# include <stdio.h>
# include <stdarg.h>
# include <math.h>

/*
** ----------------------------Define Structure---------------------------- **
*/

typedef struct		s_sprite
{
	float			x;
	float			y;
	int			r;
	int			d;
	struct s_sprite		*next;
}				t_spr;

typedef struct		s_image
{
	void			*img;
	int			*data;
	int			bpp;
	int			s_l;
	int			end;
}				t_img;

typedef	struct		s_texture
{
	char			*path;
	t_img			*img;
	int			x;
	int			y;
}				t_txt;


typedef struct		s_ray
{
	int			hit;
	int			side;
	int			x;
	int			y;
	float			camx;
	float			dirx;
	float			diry;
	float			sdisx;
	float			sdisy;
	float			ddisx;
	float			ddisy;
	float			lenght;
	float			width;
	float			height;
	float			wallx;
	int			wallstart;
	int			wallend;
	t_txt			*walltxt;
	float			step;
	float			txtpos;
	int			txtx;
}				t_ray;

typedef struct		s_camera
{
	float			posx;
	float			posy;
	int			sqposx;
	int			sqposy;
	float			dirx;
	float			diry;
	float			planex;
	float			planey;
	float			ms;
	float			rs;
	int			stepx;
	int			stepy;
	t_ray			*r;
}				t_cam;

typedef struct		s_grid
{
	int			xl;
	int			yl;
	int			xc;
	int			yc;
	float			sqcx;
	float			sqcy;
	int			xsize;
	int			ysize;
}				t_grid;

typedef struct		s_minimap
{
	float			*grid;
	void			*mnmap;
	void			*mwall;
	int			*mdata;
	int			mbpp;
	int			ms_l;
	int			mend;
	int			*mwdata;
	int			mwb;
	int			mws;
	int			mwe;
}				t_mmap;

typedef	struct		s_cub
{
	void			*init;
	void			*scr;
	void			*bg;
	char			*tmp;
	int			*r;
	t_txt			*no;
	t_txt			*we;
	t_txt			*ea;
	t_txt			*so;
	t_txt			*s;
	int			f;
	int			c;
	char			**map;
	t_img			*all;
	int			minmap;
	int			press;
	int			keyone;
	int			keytwo;
	int			keythree;
	int			jump;
	float			time;
	t_cam			*ca;
	t_mmap			*m;
	t_grid			*g;
	t_txt			*test;
	t_spr			*spr;
}				t_cub;

/*
** ----------------------------------Start--------------------------------- **
*/

int				ft_start(t_cub *t);
void				ft_loop(t_cub *t);


/*
** ----------------------------------Utils--------------------------------- **
*/

int				loophook(t_cub *t);
t_cam				*cam_setup(t_cam *c);
t_mmap				*mm_setup(t_mmap *m);
t_cub				*t_setup(t_cub *t);
void				putimg(t_cub *t, void *target, int x, int y);
void				ft_loop(t_cub *t);
void				kill(t_cub *t);

/*
** ---------------------------------Parsing-------------------------------- **
*/

int				ft_resolution(t_cub *t, char *line);
int				ft_texture(t_cub *t, char *line, int type);
int				ft_color(t_cub *t, char *line, int type);
int				ft_map(t_cub *t, char *line, int fd);
int				ft_parsing(t_cub *t, int fd);
int				ft_check_object(int c, char *set);
int				ft_map_browser(t_cub *t, int len);
int				ft_check_map(t_cub *t);
int				ft_get_type(char *line, t_cub *t);
int				ft_parse_line(t_cub *t, char *line, int check, int fd);

/*
** -----------------------------Structure Setup---------------------------- **
*/

t_grid				*g_setup(t_cub *t, t_grid *g, char **map);
t_ray				*r_setup(t_ray *r);
void				r_reset(t_cam *c, t_ray *r, int x);

/*
** -------------------------------Raycasting------------------------------- **
*/

void				raycasting(t_cub *t, t_cam *c);

/*
** ----------------------------------Utils--------------------------------- **
*/

void				spawnloc(t_cub *t, t_cam *c, int x, int y);

/*
** ---------------------------------Minimap-------------------------------- **
*/

void				map_grid(t_cub *t, t_mmap *m, char **map);
void				print_mwall(t_cub *t, t_mmap *m);
void				make_minimap(t_cub *t, t_mmap *m);
void				minimap(t_cub *t);
void				putcam(t_cub *t, t_mmap *m, t_cam *c);

/*
** --------------------------------Controls-------------------------------- **
*/

int				key(int key, t_cub *t);
int				release(int key, t_cub *t);

/*
** ------------------------------Error Manager----------------------------- **
*/

int				ft_check_params(t_cub *t);
void				ft_error(int error, t_cub *t);
void				ft_identifier_error(int type);
int				ft_double_entry_check(int type, t_cub *t);

/*
** ----------------------------------End----------------------------------- **
*/

void				freecam(t_cub *t, t_cam *c);
void				freemmap(t_cub *t, t_mmap *m);
void				freeall(t_cub *t);
void				kill(t_cub *t);
int				release(int key, t_cub *t);
void				gomove(t_cub *t);

#endif
