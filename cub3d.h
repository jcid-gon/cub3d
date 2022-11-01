/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:35:14 by jcid-gon          #+#    #+#             */
/*   Updated: 2022/09/06 14:32:24 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./include/libft/libft.h"
# include "./include/mlx/mlx.h"
# include "./srcs/get_next_line_bonus.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

typedef struct	s_display {
	void	*mlx;
	void	*mlx_win;
	int	dim[2];
}				t_display;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_sprite{
	void		*img;
	void		*ptr;
	char		*rp;
	int		dim[2];
	int		x;
	int		y;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_sprite;

typedef struct s_player{
	double	pos[2];
	double	dir[2];
	double	plane[2];
}			t_player;

typedef struct s_map{
	char		**line;
	int		size;
	int		start;
	size_t		max_len;
	t_sprite	textures[4];
	char		*floor;
	char		*ceiling;
	int		c_floor;
	int		c_ceiling;
	t_data		bg;
	t_data		walls;
	t_player	player;
	t_display	dis;
}	t_map;

#endif
