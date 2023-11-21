/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:18:53 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/21 20:10:30 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	char	*ptr;

	ptr = (char *)s;
	while (ptr && *ptr)
		ptr++;
	return (ptr - s);
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
