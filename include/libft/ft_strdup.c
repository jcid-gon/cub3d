/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <jcid-gon@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:23:58 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/05/28 12:34:23 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup (const char *src)
{
	char	*dst;

	dst = malloc(ft_strlen(src) + 1);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, src, ft_strlen(src) + 1);
	return (dst);
}
