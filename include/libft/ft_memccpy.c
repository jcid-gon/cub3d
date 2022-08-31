/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <jcid-gon@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 10:46:02 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/05/28 10:46:03 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy (void *dst, const void *src, int c, size_t n)
{
	size_t			index;
	unsigned char	chr;

	chr = c;
	index = 0;
	while (index < n)
	{
		((unsigned char *)dst)[index] = ((unsigned char *)src)[index];
		if (((unsigned char *)src)[index] == chr)
			return (dst + index + 1);
		index++;
	}
	return (NULL);
}
