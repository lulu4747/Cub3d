# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2020/01/20 17:27:58 by lfourage     #+#   ##    ##    #+#        #
#    Updated: 2020/03/07 07:56:36 by lfourage         ###   ########lyon.fr    #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

all :
	gcc -framework OpenGL -framework AppKit  ./source/minilibx_opengl_20191021/libmlx.a raycasting.c controls.c ft_start.c minimap.c utils.c rotate.c Error_Management.c parsing.c parsing_utils.c source/libft/ft_putchar_fd.c source/libft/ft_atoi.c source/libft/ft_isdigit.c source/libft/ft_strdup.c source/libft/ft_split.c source/libft/ft_strjoin.c source/libft/ft_strnstr.c source/libft/ft_strlen.c source/gnl/get_next_line.c source/gnl/get_next_line_utils.c source/libft/ft_putstr_fd.c

test : all
	./a.out map.txt
