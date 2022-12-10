/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:34:45 by jcaron            #+#    #+#             */
/*   Updated: 2022/12/10 12:22:56 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_buffer	*start_buf = NULL ;
	t_buffer		*buf;
	t_line			line;

	line.str = NULL;
	line.len = 0;
	buf = get_buf(&start_buf, fd);
	if (buf == NULL)
		return (NULL);
	while (1)
	{
		if (buf->id == buf->len)
		{
			if (ft_read(buf, fd) < 0)
				return (del_buf(&start_buf, fd), ft_free(line.str));
			if (buf->len == 0)
				return (del_buf(&start_buf, fd), line.str);
		}
		line.str = strcatalloc(&line, buf);
		if (line.str == NULL)
			return (del_buf(&start_buf, fd));
		if (buf->buf[buf->id - 1] == '\n')
			return (line.str);
	}
}

/**
 * @brief	allocate and create a new string of concatenation of 'old' and 'add'
 * 			and free the pointer '*old' if is not NULL in case of error of
 * 			allocation : free '*old' and return NULL
 * @param	line	pointer to the buf element of the list
 * @param	buf		pointer to the buf element of the list
 * @return			the new pointer to the concatenated string
**/

char	*strcatalloc(t_line *line, t_buffer *buf)
{
	char	*new;
	size_t	add_len;

	add_len = strlenn(buf);
	new = malloc(sizeof(char) * (line->len + add_len + 1));
	if (!new)
		return (ft_free(line->str));
	if (line->len > 0)
		ft_strcpy(new, line->str);
	else
		new[0] = '\0';
	ft_strncat(new, &buf->buf[buf->id], add_len);
	free(line->str);
	line->len += add_len;
	buf->id += add_len;
	return (new);
}

/**
 * @brief	return the lengh of the of the string untilthe end of line or 
 * 			a '\0' include in the lengh
 * @param	buf	pointer to the buf element of the list
 * @return	the lengh
**/

size_t	strlenn(t_buffer *buf)
{
	char	*str;
	size_t	i;
	size_t	ofset;

	ofset = buf->id;
	str = buf->buf;
	i = 0;
	while (i + ofset < buf->len)
	{
		if (str[i + ofset] == '\n')
		{
			i ++;
			break ;
		}
	i++;
	}
	return (i);
}

/**
 * @ brief	free the pointer *ptr if is not NULL and return NULL
 * @ param	ptr	pointer to free
 * @ return		NULL
**/

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

/**
 * @brief	read the file descriptor and save the content in tab buf in struct
 * 			buf
 * @param	buf	pointer to the buf struct of the list
 * @param	fd	file descriptor
 * @return		the number of character added in buffer or (-1) if read failed
**/

ssize_t	ft_read(t_buffer *buf, int fd)
{
	ssize_t	ret_read;

	ret_read = read(fd, buf->buf, BUFFER_SIZE);
	if (ret_read < 0)
		return (ret_read);
	buf->len = (size_t)ret_read;
	buf->id = 0;
	return (ret_read);
}
