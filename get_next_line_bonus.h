/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:34:45 by jcaron            #+#    #+#             */
/*   Updated: 2022/12/09 19:20:01 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif

typedef struct s_buffer
{
	int				fd;
	char			padding[4];
	struct s_buffer	*next;
	size_t			id;
	size_t			len;
	char			buf[BUFFER_SIZE];
}					t_buffer;

typedef struct s_line
{
	size_t	len;
	char	*str;
}	t_line;

char		*get_next_line(int fd);

char		*strcatalloc(t_line *line, t_buffer *buf);
size_t		strlenn(t_buffer *buf);
void		*ft_free(void *ptr);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strncat(char *dest, const char *src, size_t n);
ssize_t		ft_read(t_buffer *buf, int fd);
ssize_t		is_return(t_buffer *buf);

/*
 * buffer functions
 */

t_buffer	*get_buf(t_buffer **start_buf, int fd);
t_buffer	*add_buf(t_buffer **buf, int fd);
void		*del_buf(t_buffer **start_buf, int fd);

#endif
