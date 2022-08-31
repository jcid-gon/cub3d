/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <jcid-gon@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 11:10:23 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/06/04 11:10:24 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd (int n, int fd)
{
	long	number;

	number = n;
	while (number < 0)
	{
		ft_putchar_fd ('-', fd);
		number = number * -1;
	}
	if (number >= 10)
		ft_putnbr_fd (number / 10, fd);
	ft_putchar_fd ((number % 10) + '0', fd);
}
