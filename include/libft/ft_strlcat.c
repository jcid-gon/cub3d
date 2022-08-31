/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <jcid-gon@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 10:20:07 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/06/01 12:38:23 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*dest;
	char	*source;
	size_t	dst_length;
	size_t	remaining;

	dest = dst;
	source = (char *)src;
	remaining = dstsize;
	while (remaining-- != 0 && *dest != '\0')
		dest++;
	dst_length = dest - dst;
	remaining = dstsize - dst_length;
	if (remaining == 0)
		return (dst_length + ft_strlen(source));
	while (*source != '\0')
	{
		if (remaining > 1)
		{
			*dest++ = *source;
			remaining--;
		}
		source++;
	}
	*dest = '\0';
	return (dst_length + (source - src));
}
