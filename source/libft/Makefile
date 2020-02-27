# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/10/13 11:32:45 by lfourage     #+#   ##    ##    #+#        #
#    Updated: 2019/11/04 15:23:37 by lfourage    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

CC=gcc
AR=ar rc
NAME=libft.a
CFLAGS=-Wall -Wextra -Werror
SRC_C=ft_isdigit.c ft_memset.c ft_strjoin.c ft_strtrim.c ft_isprint.c ft_putchar_fd.c ft_strlcat.c ft_substr.c ft_atoi.c ft_itoa.c ft_putendl_fd.c ft_strlcpy.c ft_tolower.c ft_bzero.c ft_memccpy.c ft_putnbr_fd.c  ft_strlen.c ft_toupper.c ft_calloc.c ft_memchr.c ft_putstr_fd.c ft_strmapi.c ft_isalnum.c ft_memcmp.c ft_split.c ft_strncmp.c ft_isalpha.c ft_memcpy.c ft_strchr.c ft_strnstr.c ft_isascii.c ft_memmove.c ft_strdup.c ft_strrchr.c
SRC_BONUS_C=ft_lstnew.c ft_lstdelone.c ft_lstclear.c ft_lstadd_front.c ft_lstadd_back.c ft_lstsize.c ft_lstiter.c ft_lstmap.c ft_lstlast.c
INCLUDES=libft.h
OBJ=$(SRC_C:.c=.o)
OBJ_BONUS=$(SRC_BONUS_C:.c=.o)

all:	$(NAME) $(INCLUDES)

$(OBJ):	$(INCLUDES)

$(OBJ_BONUS): $(INCLUDES)

$(NAME):	$(OBJ) $(INCLUDES)
	$(AR) $(NAME) $(OBJ)
	
bonus:	$(NAME) $(OBJ_BONUS) $(INCLUDES)
	$(AR) $(NAME) $(OBJ_BONUS)

test:	bonus	$(NAME)
	$(CC) $(CFLAGS) main.c -L. libft.a

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_BONUS)

fclean:	clean
	rm -rf $(NAME)

re:	fclean	$(NAME)

retest: fclean	test
