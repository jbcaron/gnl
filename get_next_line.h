/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:34:45 by jcaron            #+#    #+#             */
/*   Updated: 2022/12/08 19:38:15 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif

typedef struct s_buffer
{
	size_t	id;
	size_t	len;
	char	buf[BUFFER_SIZE];
}	t_buffer;

typedef struct s_line
{
	size_t	len;
	char	*str;
}	t_line;

char	*get_next_line(int fd);
size_t	strlenn(t_buffer *buf);
void	*ft_free(void *ptr);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncat(char *dest, const char *src, size_t n);
char	*strcatalloc(t_line *line, t_buffer *buf);
ssize_t	ft_read(t_buffer *buf, int fd);

#endif
