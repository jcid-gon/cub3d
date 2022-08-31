/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <jcid-gon@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 11:42:00 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/06/04 11:42:01 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_trimmer(char const c, char const *set)
{
	size_t	index;

	index = 0;
	while (set[index] != '\0')
	{
		if (set[index] == c)
			return (0);
		index++;
	}
	return (1);
}

char	*ft_strtrim (char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	len = ft_strlen(s1);
	while (ft_trimmer(s1[start], set) == 0)
		start++;
	if (start == len)
	{
		str = ft_strdup("");
		return (str);
	}
	while (ft_trimmer(s1[len - 1], set) == 0)
		len--;
	str = ft_substr(s1, start, len - start);
	return (str);
}
