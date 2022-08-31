/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <jcid-gon@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 10:25:52 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/06/01 11:33:24 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	index;

	index = ft_strlen(str);
	while (str[index] != c && index != 0)
	{
		index--;
	}
	if (str[index] == c)
		return (&((char *)str)[index]);
	else
		return (NULL);
}
