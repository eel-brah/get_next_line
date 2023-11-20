/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:18:56 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/20 14:38:46 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_gnl_find_nl(size_t i, char *buf, int *rt)
{
	while (i < BUFFER_SIZE && buf[i])
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
	int		len;

	len = ft_strlen (*line);
	tmp = malloc ((len + i - r + 1) * sizeof * tmp);
	if (!tmp)
	{
		free (*line);
		*line = NULL;
		return (NULL);
	}
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

char	*ft_gnl_get_line(char **buf, int fd, int rt)
{
	static size_t	i;
	size_t			r;
	ssize_t			rd;
	char			*line;

	line = NULL;
	while (!rt)
	{
		r = i;
		if (!(i && i < BUFFER_SIZE && (*buf)[i]))
		{
			r = 0;
			i = 0;
			rd = read (fd, *buf, BUFFER_SIZE);
			if (rd == -1 || rd == 0)
				return (ft_gnl_free (buf, line, rd));
			if (rd < BUFFER_SIZE)
				(*buf)[rd] = 0;
		}
		i = ft_gnl_find_nl (i, *buf, &rt);
		line = ft_gnl_generate_line (&line, r, i, buf);
		if (!line)
			return (ft_gnl_free(buf, line, -1));
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buf)
	{
		buf = malloc (sizeof * buf * BUFFER_SIZE);
		if (!buf)
			return (NULL);
		ft_bzero (buf, BUFFER_SIZE);
	}
	return (ft_gnl_get_line (&buf, fd, 0));
}
