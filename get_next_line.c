/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:34:45 by jcaron            #+#    #+#             */
/*   Updated: 2022/12/10 12:22:54 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer	buf = {.id = 0, .len = 0};
	t_line			line;

	line.str = NULL;
	line.len = 0;
	while (1)
	{
		if (buf.id == buf.len || buf.len == 0)
		{
			if (ft_read(&buf, fd) < 0)
				return (ft_free(line.str));
			if (buf.len == 0)
				return (line.str);
		}
		line.str = strcatalloc(&line, &buf);
		if (line.str == NULL)
			return (NULL);
		if (buf.buf[buf.id - 1] == '\n')
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
