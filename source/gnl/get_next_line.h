/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 14:03:35 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 17:58:06 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUFFER_SIZE 32

typedef struct		s_list
{
	char			*content;
	int				index;
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);
size_t				ft_strlen_c(const char *str, int c);
char				*ft_join(char *dst, const char *src, size_t len);
char				*ft_substr(char *s, unsigned int start, size_t len);
void				ft_lstclear(t_list **lst);
t_list				*ft_lstcat(t_list **statik, t_list **first);
char				*ft_fill_line(char **statik, char **line, size_t len);
#endif
