/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:34:45 by jcaron            #+#    #+#             */
/*   Updated: 2022/12/10 12:22:56 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

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
 * @brief	find the element of list which corresponds the file descriptor 
 * 			or create a new elememt
 * @param	start_buf	pointer to the first buf struct of the list
 * @param	fd			file descriptor
 * @return 				return a pointer to the corresponding element or to 
 * 						a new element
**/

t_buffer	*get_buf(t_buffer **start_buf, int fd)
{
	t_buffer	*buf;

	buf = *start_buf;
	while (buf && buf->fd != fd)
		buf = buf->next;
	if (buf == NULL)
		buf = add_buf(start_buf, fd);
	return (buf);
}

/**
 * @brief	search the buffer corresponding to the right file directory, 
 * 			delete the buffer and repair the chain
 * @param	start_buf	pointer to the first buf struct of the list
 * @param	fd			file descriptor
 * @return				NULL
**/

void	*del_buf(t_buffer **start_buf, int fd)
{
	t_buffer	*prev;
	t_buffer	*tmp;

	prev = *start_buf;
	tmp = prev->next;
	if ((*start_buf)->fd == fd)
	{
		free(*start_buf);
		*start_buf = tmp;
		return (NULL);
	}
	while (tmp)
	{
		if (tmp->fd == fd)
		{
			prev->next = tmp->next;
			free (tmp);
			return (NULL);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * @brief	create a new element t_buffer and initialize it. this element is
 * 			added at the end of the list
 * @param	start_buf	pointer to the first buf struct of the list
 * @param	fd			file descriptor
 * @return				the new initialised buf struct with the file director
**/

t_buffer	*add_buf(t_buffer **start_buf, int fd)
{
	t_buffer	*new;
	t_buffer	*buf;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	new->id = 0;
	new->len = 0;
	buf = *start_buf;
	if (*start_buf == NULL)
		*start_buf = new;
	else
	{
		while (buf->next)
			buf = buf->next;
		buf->next = new;
	}
	return (new);
}
