/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:18:56 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/22 13:58:12 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_gnl_find_nl(size_t i, char *buf, int *rt)
{
	while (i < (size_t)BUFFER_SIZE && buf[i])
	{
		if (buf[i] == 10)
		{
			*rt = 1;
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

char	*ft_gnl_free(char **buf, char *line, char cs)
{
	if (cs == -1)
	{
		free (line);
		free (*buf);
		*buf = NULL;
		return (NULL);
	}
	else
	{
		free (*buf);
		*buf = NULL;
		return (line);
	}
}

char	*ft_gnl_generate_line(char **line, size_t r, size_t i, char **buf)
{
	char	*tmp;
	size_t	len;
	size_t	size;

	len = ft_strlen (*line);
	if (len > SIZE_MAX - (i - r) || (len + i - r) > SIZE_MAX - 1)
		return (ft_gnl_free (line, NULL, -1));
	size = len + i - r + 1;
	if (size && SIZE_MAX / size < sizeof * tmp)
		return (ft_gnl_free (line, NULL, -1));
	tmp = malloc (size * sizeof * tmp);
	if (!tmp)
		return (ft_gnl_free (line, NULL, -1));
	if (*line)
	{
		ft_memcpy(tmp, *line, len);
		tmp[len] = 0;
		free(*line);
	}
	*line = tmp;
	ft_memcpy(*line + len, *buf + r, i - r);
	(*line)[len + i - r] = 0;
	return (tmp);
}

char	*ft_gnl_get_line(t_buffer *buffer, int fd, int rt)
{
	size_t	r;
	ssize_t	rd;
	char	*line;

	line = NULL;
	while (!rt)
	{
		r = buffer->i;
		if (!(buffer->i && buffer->i < (size_t)BUFFER_SIZE && 
				buffer->buf[buffer->i]))
		{
			r = 0;
			buffer->i = 0;
			rd = read (fd, buffer->buf, BUFFER_SIZE);
			if (rd == -1 || rd == 0)
				return (ft_gnl_free (&(buffer->buf), line, rd));
			if (rd < BUFFER_SIZE)
				buffer->buf[rd] = 0;
		}
		buffer->i = ft_gnl_find_nl (buffer->i, buffer->buf, &rt);
		line = ft_gnl_generate_line (&line, r, buffer->i, &(buffer->buf));
		if (!line)
			return (ft_gnl_free(&(buffer->buf), line, -1));
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer[OPEN_MAX];

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd].buf)
	{
		if (SIZE_MAX / BUFFER_SIZE < sizeof(char))
			return (NULL);
		buffer[fd].buf = malloc (sizeof(char) * BUFFER_SIZE);
		if (!buffer[fd].buf)
			return (NULL);
	}
	return (ft_gnl_get_line (&buffer[fd], fd, 0));
}
