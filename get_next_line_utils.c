/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:34:45 by jcaron            #+#    #+#             */
/*   Updated: 2022/12/10 12:22:55 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *dest, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (j < n)
	{
		dest[i + j] = src [j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
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
