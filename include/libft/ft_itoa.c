/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <jcid-gon@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 11:40:32 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/06/04 11:40:33 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_size (long number)
{
	size_t	size;

	size = 0;
	if (number < 0)
	{
		number = number * -1;
		size++;
	}
	while (number >= 10)
	{
		number = number / 10;
		size++;
	}
	return (size + 1);
}

char	*ft_itoa(int n)
{
	long	number;
	char	*array;
	size_t	size;

	number = n;
	size = ft_size(number);
	array = malloc((size + 1) * sizeof(char));
	if (array == NULL)
		return (NULL);
	while (number < 0)
	{
		array[0] = '-';
		number = number * -1;
	}
	array[size] = '\0';
	while (number >= 10)
	{
		array[(size--) - 1] = (number % 10) + '0';
		number = number / 10;
	}
	array[size - 1] = number + '0';
	return (array);
}
