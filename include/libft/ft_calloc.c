/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <jcid-gon@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:50:33 by jcid-gon          #+#    #+#             */
/*   Updated: 2021/06/01 12:05:47 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc (size_t n, size_t size)
{
	void	*ret;

	ret = malloc (n * size);
	if (ret == NULL)
		return (NULL);
	ft_bzero (ret, n * size);
	return (ret);
}
