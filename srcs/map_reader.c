/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <jcid-gon@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:34:09 by jcid-gon          #+#    #+#             */
/*   Updated: 2022/08/31 14:04:48 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_str_del(char **str)
{
	if (*str)
	{
		free (*str);
		*str = NULL;
	}
}

static int	ft_str_op(int fd, char **line, char **str)
{
	int		index;
	char	*temp;

	index = 0;
	while (str[fd][index] != '\n' && str[fd][index] != '\0')
		index++;
	if (str[fd][index] == '\n')
	{
		*line = ft_substr(str[fd], 0, index);
		temp = ft_strdup(str[fd] + index + 1);
		ft_str_del(&str[fd]);
		str[fd] = temp;
		if (str[fd][0] == '\0')
			ft_str_del(&str[fd]);
	}
	else
	{
		*line = ft_strdup(str[fd]);
		ft_str_del(&str[fd]);
		return (0);
	}
	return (1);
}

int	ft_return_value(int i, int fd, char **line, char **str)
{
	if (i < 0)
		return (-1);
	if (i == 0 && str[fd] == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	return (ft_str_op(fd, line, str));
}

int	get_next_line(int fd, char **line)
{
	static char	*str[10000];
	char		buff[64 + 1];
	char		*temp;
	int			i;

	if (fd < 0 || fd > 10000 || !line)
		return (-1);
	i = 1;
	while (i > 0)
	{
		i = read (fd, buff, 64);
		buff[i] = '\0';
		if (!str[fd])
			str[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(str[fd], buff);
			ft_str_del(&str[fd]);
			str[fd] = temp;
		}
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (ft_return_value(i, fd, line, str));
}
