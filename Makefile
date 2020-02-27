# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2020/01/20 17:27:58 by lfourage     #+#   ##    ##    #+#        #
#    Updated: 2020/02/25 19:18:39 by lfourage         ###   ########lyon.fr    #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

all :
	gcc -framework OpenGL -framework AppKit  ./source/minilibx_opengl_20191021/libmlx.a ft_start.c minimap.c utils.c rotate.c Error_Management.c parsing.c parsing_utils.c source/libft/ft_atoi.c source/libft/ft_isdigit.c source/libft/ft_strdup.c source/libft/ft_split.c source/libft/ft_strjoin.c source/libft/ft_strnstr.c source/libft/ft_strlen.c source/gnl/get_next_line.c source/gnl/get_next_line_utils.c

test : all
	./a.out map.txt
