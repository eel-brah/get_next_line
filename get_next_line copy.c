/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:18:56 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/17 19:20:26 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

size_t	ft_strlen(const char *s)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
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

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			s;

	// if (count > 0 && SIZE_MAX / count < size)
	// 	return (NULL);
	s = count * size;
	p = malloc(s);
	if (!p)
		return (NULL);
	ft_bzero((void *)p, s);
	return ((void *)p);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize < 1)
		return (src_len);
	while (*src && --dstsize > 0)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	len;

	dst_len = 0;
	if (dst)
		dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize > dst_len)
		len = dst_len + src_len;
	else
		len = dstsize + src_len;
	if (dstsize < 1)
		return (len);
	dst += dst_len;
	while (*src && dst_len++ < dstsize - 1)
		*dst++ = *src++;
	*dst = '\0';
	return (len);
}

// int get_next_line_loop(int fd , char *buf)
// {
//     int  rd;
//     int  i;

//     rd = 1;
//     i = 0;
//     while (BUFFER_SIZE > i)
//     {
//         rd = read(fd, (buf + i), 1);
//         if (buf[i] == 10)
//             return (++i);
//         else if (rd == 0 && i != 0)
//             return (++i);
//         else if (rd == 0 && i == 0)
//             return (0);
//         else if (rd == -1)
//             return (-1);
//         i++;
//     }
//     return (i);
// }

char *get_next_line(int fd)
{

    char    *buf;
    int     k;
    int     i;
    char    *result;
    char    *tmp;
    int  rd;
    int j;

    i = 0;
    j = 0;
    rd = 0;
    k = 0;
    if (fd < 0 || BUFFER_SIZE <= 0) // fd <= 0
        return (NULL);
    buf = malloc(sizeof *buf * BUFFER_SIZE);
    if (!buf)
        return NULL;
    result = NULL;
    while (1)
    {
        //k = get_next_line_loop(fd, buf);
        j = 0;
        ft_bzero(buf, BUFFER_SIZE);
        while (BUFFER_SIZE > j)// 4 - 2
        {
            rd = read(fd, (buf + j), 1);
            if (buf[j] == '\n')
            {
                k = 2;
                //j++;
                break;
            }
            else if (rd == 0 && j != 0)
            {
                k = 2;
                break;
            }
            else if (rd == 0 && j == 0)
            {
                k = 1;
                break;
            }
            else if (rd == -1)
            {
                k = -1;
                break;
            }
            j++;
        }
        if (k == -1)
        {
            free (buf);
            return (NULL);
        }
        if (k == 1)
        {
            free (buf);
            return (result);
        }
        tmp = ft_calloc((BUFFER_SIZE * ++i + 1), sizeof *result);
        if (!tmp)
            return (NULL);
        if (result)
        {
            ft_strlcpy(tmp, result, BUFFER_SIZE * i + 1);
            free(result);
        }
        result = tmp;
        int x = 0;
        while (result[x])
            x++;
        int y = 0;
        //printf("%i\n", j);
        while (y <= j && y != BUFFER_SIZE)
        {
            result[x] = buf[y];
            y++;
            x++;
        }
        //printf("%i %i %i %s\n", j, x, y, result);
        //ft_strlcat(result, buf, BUFFER_SIZE * i + 1); // if buf wasn't full
        if (k == 2)
        {
            free(buf);
            return (result);
        }
    }
    return (NULL);
}

// int main()
// {
//     int i = open("file",  O_RDONLY | O_CREAT);
//     char *h;
//     //char *h = get_next_line(i);
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
