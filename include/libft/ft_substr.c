/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <jcid-gon@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 10:23:21 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/06/04 10:23:22 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	if (!s)
		return (NULL);
	dest = malloc ((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	if (start <= ft_strlen(s))
		ft_strlcpy (dest, &s[start], len + 1);
	return (dest);
}
