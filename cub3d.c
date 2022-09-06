/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:25:32 by jcid-gon          #+#    #+#             */
/*   Updated: 2022/09/06 14:32:22 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//UTILS

void	error_message(char *str)
{
	printf("Error\n%s\n", str);
	exit (1);
}

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	display_background(t_map *map)
{
	int	y;
	int	x;

	map->bg.img = mlx_new_image(map->mlx, 1920, 1080);
	map->bg.addr = mlx_get_data_addr(map->bg.img, &map->bg.bits_per_pixel, &map->bg.line_length,&map->bg.endian);
	y = 0;
	while(y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			if (y < 540)
				pixel_put(&map->bg, x, y, map->c_ceiling);
			else
				pixel_put(&map->bg, x, y, map->c_floor);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->bg.img, 0, 0);
}

//MAP READER

int	map_size(char *argv)
{
	char	**line;
	int		i;
	int		fd;

	i = 0;
	line = malloc(sizeof(char) * 2);
	fd = open(argv, O_RDONLY);
	if (fd <= 0)
		error_message("Map couldn't be opened");
	while (get_next_line(fd, &line[0]))
		i++;
	free(line[0]);
	close(fd);
	return(i);
}

void	format_check(char *argv)
{
	int		i;
	int		j;
	char	**str;

	i = 0;
	j = 0;
	while(argv[i])
	{
		if(argv[i] == '.')
			j++;
		i++;
	}
	if (j != 1)
		error_message("Invalid map format");
	str = ft_split(argv, '.');
	if (str[1] == NULL || ft_strncmp(str[1], "cub", 3) != 0)
		error_message("Invalid map format");
}

void	get_sides(t_map *map)
{
	int		i;
	int		pos;
	char	**str;

	i = 0;
	pos = 0;
	while (i < 6 && pos < map->size)
	{
		if(map->line[pos])
		{
			str = ft_split(map->line[pos], ' ');
			if(str[0] != NULL)
			{
				if (ft_strncmp(str[0], "NO", 2) == 0)
					map->north.rp = ft_strdup(str[1]);
				else if (ft_strncmp(str[0], "SO", 2) == 0)
					map->south.rp = ft_strdup(str[1]);
				else if (ft_strncmp(str[0], "WE", 2) == 0)
					map->west.rp = ft_strdup(str[1]);
				else if (ft_strncmp(str[0], "EA", 2) == 0)
					map->east.rp = ft_strdup(str[1]);
				else if (ft_strncmp(str[0], "F", 1) == 0)
					map->floor = ft_strdup(str[1]);
				else if (ft_strncmp(str[0], "C", 1) == 0)
					map->ceiling = ft_strdup(str[1]);
				else
					error_message("Incorrect map file, missing arguments");
				i++;
			}
		}
		pos++;
	}
	if (i < 6)
		error_message("Incorrect map file, missing arguments");
	while(map->line[pos][0] == '\0')
		pos++;
	printf("POS=%d\n", pos);
	map->start = pos;
}

void	check_walls(t_map *map)
{
	int	i;
	int	j;

	j = map->start;
	map->max_len = 0;
	printf("START= %i\n", map->start);
	while (j < map->size)
	{
		if (map->line[j][0] != '\0')
		{
			i = 0;
			while (map->line[j][i] == ' ')
				i++;
			if (map->line[j][i] != '1')
				error_message("Incorrect map file, map not covered with walls");
			while(map->line[j][i] != '\0')
			{
				if (map->line[j][i] == ' ')
				{
					if (map->line[j][i - 1] != '1')
						error_message("Incorrect map file, map not covered with walls");
					while(map->line[j][i] == ' ')
						i++;
					if (map->line[j][i] != '1' && map->line[j][i] != '\0')
						error_message("Incorrect map file, map not covered with walls");
				}
				i++;
			}
			if (i == (int) ft_strlen(map->line[j]) && map->line[j][i - 1] != ' ' && map->line[j][i - 1] != '1')
				error_message("Incorrect map file, map not covered with walls");
		}
		if (map->max_len < ft_strlen(map->line[j]))
				map->max_len = ft_strlen(map->line[j]);
		j++;
	}	
	printf("Sides Correct!\n");
	printf("LEN= %zu\n", map->max_len); 

	i = 0;
	while (i < (int) map->max_len)
	{
		j = map->start;
		while(map->line[j][i] == ' ')
			j++;
		if (map->line[j][i] != '1')
			error_message("Incorrect map file, map not covered with walls");
		while(j < map->size)
		{
			if (map->line[j][i] == ' ' || !map->line[j][i])
			{
				if (map->line[j - 1][i] != '1')
					error_message("Incorrect map file, map not covered with walls");
				while(j < map->size && (map->line[j][i] == ' ' || !map->line[j][i]))
					j++;
				if (j < map->size && map->line[j][i] != '1')
					error_message("Incorrect map file, map not covered with walls");
			}
		j++;
		}
		if (i < (int) ft_strlen(map->line[j - 1]) && map->line[j - 1][i] > 2 && map->line[j - 1][i] != ' ' && map->line[j - 1][i] != '1')
			error_message("Incorrect map file, map not covered with walls");
		i++;
	}
	printf("Colums correct!\n");
}

void map_reader(t_map *map, char *argv)
{
	int	fd;
	int i;

	i = 0;
	format_check(argv);
	map->size = map_size(argv);
	printf("SIZE=%i\n", map->size);
	map->line = malloc(sizeof(char *) * (map->size + 1));
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		error_message("Map couldn't be opened");
	while(get_next_line(fd, &map->line[i]) == 1)
	{
		printf("%s\n", map->line[i]);
		i++;
	}
	printf("\n");
	close (fd);
	get_sides(map);
	check_walls(map);
	printf("NORTH = %s\n", map->north.rp);
	printf("SOUTH = %s\n", map->south.rp);
	printf("WEST = %s\n", map->west.rp);
	printf("EAST = %s\n", map->east.rp);
	printf("FLOOR = %s\n", map->floor);
	printf("CEILING = %s\n", map->ceiling);
}

void	player_starter(t_map *map)
{
	int	y;
	int	x;
	int	is;

	map->player.dir[0] = -1;
	map->player.dir[1] = 0;
	map->player.plane[0] = 0;
	map->player.plane[1] = 0.66;
	is = 0;
	y = map->start;
	while (y < map->size)
	{
		if (map->line[y][0] != '\0')
		{
			x = 0;
			while (x < (int) ft_strlen(map->line[y]))
			{
				if (map->line[y][x] == 'N')
				{
					map->player.pos[0] = x;
					map->player.pos[1] = y;
					is++;
				}
				else if (map->line[y][x] != '0' && map->line[y][x] != '1' && map->line[y][x] != ' ')
					error_message("Unknown element on map");
			x++;
			}
		}
		y++;
	}
	if (is == 0)
		error_message("Player not found");
	else if (is > 1)
		error_message("More than one player");
	printf("PLAYER_POS=%.2f, %.2f\n", map->player.pos[0], map->player.pos[1]);
}

//INITALIZATION

void	image_init(t_map *map)
{
	map->mlx = mlx_init();
	map->mlx_win = mlx_new_window(map->mlx, 1920, 1080, "cub3d");
}

int	get_colors(char *str)
{
	char	**index;
	int		*ret;
	int		i;

	index = ft_split(str, ',');
	ret = malloc(sizeof(int) * 4);
	i = 0;
	while(i < 3)
	{
		ret[i] = ft_atoi(index[i]);
		if (ret[i] < 0 || ret[i] > 255)
			error_message("Incorrect RGB numbers");
		i++;
	}
	return(0 << 24 | ret[0] << 16 | ret[1] << 8 | ret[2]);
}

void put_background(t_map *map)
{
	map->c_floor = get_colors(map->floor);
	printf("C_FLOOR=%x\n", map->c_floor);
	map->c_ceiling = get_colors(map->ceiling);
	printf("C_CEILING=%x\n", map->c_ceiling);
	display_background(map);	
}

void	sprite_assignor(t_map *map, t_sprite *sprite)
{
	sprite->img = mlx_xpm_file_to_image(map->mlx, sprite->rp, &sprite->dim[0], &sprite->dim[1]);
	if (sprite->img == NULL)
		error_message("Image could not be read");
}

void	assing_sprites(t_map *map)
{
	sprite_assignor(map, &map->north);
	sprite_assignor(map, &map->south);
	sprite_assignor(map, &map->west);
	sprite_assignor(map, &map->east);
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->north.img, 128, 0);
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->south.img, 0, 128);
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->west.img, 256, 128);
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->east.img, 128, 256);
}

//MAIN

int main (int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		error_message("Invalid number of arguments");
	map_reader(&map, argv[1]);
	player_starter(&map);
	image_init(&map);
	put_background(&map);
	assing_sprites(&map);
	mlx_loop(map.mlx);
	return (0);
}
