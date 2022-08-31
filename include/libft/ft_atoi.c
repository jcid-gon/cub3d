/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <jcid-gon@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 10:36:53 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/06/01 13:05:29 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_maxmin(unsigned long long number, bool is_negative)
{
	unsigned long long	index;

	index = 9223372036854775807;
	if (number > index)
	{
		if (is_negative == true && number != index++)
			number = 0;
		else
			number = -1;
	}
	return (number);
}

int	ft_atoi(const char *str)
{
	unsigned long long int		number;
	unsigned long long int		index;
	bool						is_negative;

	index = 0;
	number = 0;
	is_negative = false;
	while (str[index] == ' ' || (str[index] >= 9 && str[index] <= 13))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			is_negative = true;
		index++;
	}
	while (str[index] <= '9' && str[index] >= '0')
	{
		number = (number * 10) + (str[index] - '0');
		index++;
	}
	number = ft_maxmin(number, is_negative);
	if (is_negative == true)
		number = number * -1;
	return (number);
}
