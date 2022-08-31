/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <jcid-gon@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 11:06:06 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/06/04 11:06:07 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*array;
	unsigned int	index;

	if (!s)
		return (NULL);
	array = malloc(ft_strlen(s) + 1);
	index = 0;
	if (array == NULL)
		return (NULL);
	while (s[index] != '\0')
	{
		array[index] = f(index, s[index]);
		index++;
	}
	array[index] = '\0';
	return (array);
}
