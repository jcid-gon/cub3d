/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <jcid-gon@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 10:23:58 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/05/28 10:23:59 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	index;

	index = 0;
	while (str[index] != c && str[index] != '\0')
	{
		index++;
	}
	if (str[index] == c)
		return (&((char *)str)[index]);
	else
		return (NULL);
}
