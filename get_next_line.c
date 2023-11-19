/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:18:56 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/19 16:51:26 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>


size_t	ft_strlen(const char *s)
{
	char	*ptr;

	ptr = (char *)s;
	while (ptr && *ptr)
		ptr++;
	return (ptr - s);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n--)
		*str++ = '\0';
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (!src && !dst)
		return (NULL);
	s = src;
	d = dst;
	while (n--)
		*d++ = *s++;
	return (dst);
}

size_t ft_gnl_find_nl(size_t i, char *buf, int *rt)
{
    while (i < BUFFER_SIZE && buf[i])
    {
        if (buf[i] == 10)
        {
            *rt = 1;
            i++;
            break;
        }
        i++;
    }
    return (i);
}

char    *ft_gnl_free(char **buf, char *line)
{
    free (line);
    free (*buf);
    *buf = NULL;
    return (NULL);
}

char    *ft_gnl_generate_line(char *line, size_t r, size_t i, size_t *size)
{
    char    *tmp;
    int     len;

    len = ft_strlen(line);
    if (r && line)
        *size += len + i + 1;
    else
        *size += i - r + 1;
    tmp = malloc(*size * sizeof *tmp);
    if (!tmp)
        return (NULL);
    if (line)
    {
        ft_memcpy(tmp, line, len);
        tmp[len] = 0;
        free(line);
    }
    return (tmp);
}

char    *ft_gnl_allocat(int fd, char *buf)
{
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!buf)
    {
        buf = malloc(sizeof *buf * BUFFER_SIZE);
        if (!buf)
            return (NULL);
        ft_bzero(buf, BUFFER_SIZE);
    }
    return (buf);
}

char *get_next_line(int fd)
{
    static char    *buf;
    ssize_t  rd;
    static size_t  i;
    size_t  r;
    char    *line;
    int rt;
    size_t size;
    int len;

    buf = ft_gnl_allocat(fd, buf);
    if (!buf)
        return (NULL);
    line = NULL;
    size = 0;
    rt = 0;
    while (!rt)
    {
        if (i && i < BUFFER_SIZE && buf[i])
        {
            r = i;
            i = ft_gnl_find_nl(i, buf, &rt);
        }
        else
        {
            r = 0;
            i = 0;
            rd = read(fd, buf, BUFFER_SIZE);
            if (rd == -1)
                return (ft_gnl_free(&buf, line));
            else if (rd == 0)
            {
                free (buf);
                buf = NULL;
                return (line);
            }
            if (rd < BUFFER_SIZE)
                buf[rd] = 0;
            i = ft_gnl_find_nl(i, buf, &rt);
        }
        len = ft_strlen(line);
        line = ft_gnl_generate_line(line, r, i, &size);
        if (!line)
            return (ft_gnl_free(&buf, line));
        ft_memcpy(line + len, buf + r, i - r);
        line[len + i - r] = 0;
    }
    return (line);
}

// int main()
// {
//     int i = open("file",  O_RDONLY | O_CREAT);
//     char *h;
//     // h = get_next_line(i);
//     // printf("%s", h);
//     // free(h);
//     // h = get_next_line(i);
//     // printf("%s", h);
//     // free(h);
//     // h = get_next_line(i);
//     // printf("%s", h);
//     // free(h);
//     // h = get_next_line(i);
//     // printf("%s", h);
//     // free(h);
//     // h = get_next_line(i);
//     // printf("%s", h);
//     // free(h);
//     // h = get_next_line(i);
//     // printf("%s", h);
//     // free(h);
//     while (1)
//     {
//         h = get_next_line(i);
//         if (!h)
//             break;
//         printf("%s", h);
//         free(h);
//     }
// }

