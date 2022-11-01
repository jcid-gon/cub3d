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

void	pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	display_background(t_map *map)
{
	int	y;
	int	x;

	map->bg.img = mlx_new_image(map->dis.mlx, map->dis.dim[0], map->dis.dim[1]);
	map->bg.addr = mlx_get_data_addr(map->bg.img, &map->bg.bits_per_pixel, &map->bg.line_length,&map->bg.endian);
	y = 0;
	while(y < map->dis.dim[1])
	{
		x = 0;
		while (x < map->dis.dim[0])
		{
			if (y < map->dis.dim[1] / 2)
				pixel_put(&map->bg, x, y, map->c_ceiling);
			else
				pixel_put(&map->bg, x, y, map->c_floor);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->dis.mlx, map->dis.mlx_win, map->bg.img, 0, 0);
	mlx_destroy_image(map->dis.mlx, map->bg.img);
}

void	print_screen(t_map *map, int *start_height, int *end_height, unsigned int color[4000][4000])
{
	int y;
	int x;

	x = 0;
	color = NULL;
	map->walls.img = mlx_new_image(map->dis.mlx, map->dis.dim[0], map->dis.dim[1]);
	map->walls.addr = mlx_get_data_addr(map->walls.img, &map->walls.bits_per_pixel, &map->walls.line_length, &map->walls.endian);
	while(x < map->dis.dim[0])
	{
		y = 0;
		while (y < map->dis.dim[1])
		{
			if (y > start_height[x] && y < end_height[x])
			{
				//printf("color %d\n", color[x][y]);
				pixel_put(&map->walls, x, y, 0);
			}
			else if (y < map->dis.dim[1] / 2)
				pixel_put(&map->walls, x, y, map->c_ceiling);
			else
				pixel_put(&map->walls, x, y, map->c_floor);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(map->dis.mlx, map->dis.mlx_win, map->walls.img, 0, 0);
	mlx_destroy_image(map->dis.mlx, map->walls.img);
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
					map->textures[0].rp = ft_strdup(str[1]);
				else if (ft_strncmp(str[0], "SO", 2) == 0)
					map->textures[1].rp = ft_strdup(str[1]);
				else if (ft_strncmp(str[0], "WE", 2) == 0)
					map->textures[2].rp = ft_strdup(str[1]);
				else if (ft_strncmp(str[0], "EA", 2) == 0)
					map->textures[3].rp = ft_strdup(str[1]);
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
	printf("NORTH = %s\n", map->textures[0].rp);
	printf("SOUTH = %s\n", map->textures[1].rp);
	printf("WEST = %s\n", map->textures[2].rp);
	printf("EAST = %s\n", map->textures[3].rp);
	printf("FLOOR = %s\n", map->floor);
	printf("CEILING = %s\n", map->ceiling);
}

void	player_starter(t_map *map)
{
	int	y;
	int	x;
	int	is;

	map->player.dir[0] = 1;
	map->player.dir[1] = 1;
	map->player.plane[0] = -0.5;
	map->player.plane[1] = 0.5;
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
	map->dis.mlx = mlx_init();
	map->dis.mlx_win = mlx_new_window(map->dis.mlx, map->dis.dim[0], map->dis.dim[1], "cub3d");
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
	sprite->img = mlx_xpm_file_to_image(map->dis.mlx, sprite->rp, &sprite->dim[0], &sprite->dim[1]);
	if (sprite->img == NULL)
		error_message("Image could not be read");
	else
		sprite->ptr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel, &sprite->line_length, &sprite->endian);
}

void	assing_sprites(t_map *map)
{
	sprite_assignor(map, &map->textures[0]);
	sprite_assignor(map, &map->textures[1]);
	sprite_assignor(map, &map->textures[2]);
	sprite_assignor(map, &map->textures[3]);
	//mlx_put_image_to_window(map->dis.mlx, map->dis.mlx_win, map->north.img, 128, 0);
	//mlx_put_image_to_window(map->dis.mlx, map->dis.mlx_win, map->south.img, 0, 128);
	//mlx_put_image_to_window(map->dis.mlx, map->dis.mlx_win, map->west.img, 256, 128);
	//mlx_put_image_to_window(map->dis.mlx, map->dis.mlx_win, map->east.img, 128, 256);
}

//RAY CASTING

void	raycast(t_map *map)
{
	double	cameraX;
	double	raydir[2];
	double	sidedist[2];
	double	deltadist[2];
	double	texStep;
	double	wallX;
	double	textPos;
	float	prepwalldist;
	int	step[2];
	int	pos_map[2];
	int	hit;
	int	side[map->dis.dim[0]];
	int	x;
	int	lineheight;
	int	drawstart[map->dis.dim[0]];
	int	drawend[map->dis.dim[0]];
	int	y;
	int 	wall_side;
	int	tex[2];
	unsigned int	color[map->dis.dim[0]][map->dis.dim[1]];

	x = 0;
	//color = malloc(sizeof(int) * (map->dis.dim[0] + 1));
	while (x < map->dis.dim[0])
	{
		//color[x] = malloc (sizeof(int) * (map->dis.dim[1] + 1));
		pos_map[0] = (int)map->player.pos[0];
		pos_map[1] =  (int)map->player.pos[1];
		hit = 0;
		//CALCULATE RAYDIR
		cameraX = 2 * x / (double)(map->dis.dim[0]) - 1;
		raydir[0] = map->player.dir[0] + map->player.plane[0] * cameraX;
		raydir[1] = map->player.dir[1] + map->player.plane[1] * cameraX;
		//printf("CAMERAX %f, RAYDIR %f, %f\n", cameraX, raydir[0], raydir[1]);
		//CALCULATE DELTADIST
		if (raydir[0] == 0)
			deltadist[0] = 1e30;
		else
			deltadist[0] = 1 / raydir[0];
		if (deltadist[0] < 0)
			deltadist[0] *= -1;
		if (raydir[1] == 0)
			deltadist[1] = 1e30;
		else
			deltadist[1] = 1 / raydir[1];
		if (deltadist[1] < 0)
			deltadist[1] *= -1;
		//printf("DELTADIS %f, %f\n", deltadist[0], deltadist[1]);
		//CALCULATE SIDEDIST
		if (raydir[0] < 0)
		{
			step[0] = -1;
			sidedist[0] = (map->player.pos[0] - pos_map[0]) * deltadist[0];
		}
		else
		{
			step[0] = 1;
			sidedist[0] = (pos_map[0] + 1.0 - map->player.pos[0]) * deltadist[0];
		}
		if (raydir[1] < 0)
		{
			step[1] = -1;
			sidedist[1] = (map->player.pos[1] - pos_map[1]) * deltadist[1];
		}
		else
		{
			step[1] = 1;
			sidedist[1] = (pos_map[1] + 1.0 - map->player.pos[1]) * deltadist[1];
		}
		//printf("SIDEDIST %f, %f\n", sidedist[0], sidedist[1]);
		//HIT CHECK
		while (hit == 0)
		{
			if (sidedist[0] < sidedist[1])
			{
				sidedist[0] += deltadist[0];
				pos_map[0] += step[0];
				side[x] = 0;
			}
			else
			{
				sidedist[1] += deltadist[1];
				pos_map[1] += step[1];
				side[x] = 1;
			}
			if (map->line[pos_map[1]][pos_map[0]] == '1')
				hit = 1;
		}
		//printf("SIDEDIST%d %f, %f\n", side[x], sidedist[0], sidedist[1]);
		//CALCULATE WALLDIST
		if (side[x] == 0)
			prepwalldist = (sidedist[0] - deltadist[0]);
		else
			prepwalldist = (sidedist[1] - deltadist[1]);
		//printf("WALLDIST %f\n", prepwalldist);
		//CALCULATE LINEHEIGHT
		lineheight = (int) (map->dis.dim[1] / prepwalldist);
		//printf("HEIGTH %d\n", lineheight);
		//CALCULATE PIXELS
		drawstart[x] = -lineheight / 2 + map->dis.dim[1] / 2;
		if (drawstart[x] < 0)
			drawstart[x] = 0;
		drawend[x] = lineheight / 2 + map->dis.dim[1] / 2;
		if (drawend[x] >= map->dis.dim[1])
			drawend[x] = map->dis.dim[1] - 1;
		//printf("DRAWSTART %d, DRAWUEN %d\n", drawstart[x], drawend[x]);
		//Value of Wall X
		if (side[x] == 0)
			wallX = map->player.pos[1] + prepwalldist * raydir[1];
		else
			wallX = map->player.pos[0] + prepwalldist * raydir[0];
		//Side we are hitting
		if (side[x] == 0 && map->player.pos[1] < pos_map[1])
			wall_side = 0;
		else if (side[x] == 0 && map->player.pos[1] > pos_map[1])
			wall_side = 1;
		else if (side[x] == 1 && map->player.pos[0] > pos_map[0])
			wall_side = 2;
		else if (side[x] == 1 && map->player.pos[0] < pos_map[0])
			wall_side = 3;
		//x Coordinate of de texture
		tex[0] = (int) (wallX * (double) (map->textures[wall_side].dim[0]));
		//How much to increase the texture coordinate per screen pixel
		texStep = 1.0 * map->textures[wall_side].dim[1] / lineheight;
		//Start getting the color
		textPos =  (double)(drawstart[x] - map->dis.dim[1] / 2 + lineheight / 2) * texStep;
		y = drawstart[x];
		while(y < drawend[x])
		{
			tex[1] = (int)(textPos) & (map->textures[wall_side].dim[1] - 1);
			textPos += texStep;
			if (tex[1] > map->textures[wall_side].dim[1])
				tex[1] = map->textures[wall_side].dim[1] - 1;
			if (tex[0] >= 0 && tex[0] < map->textures[wall_side].dim[0] && tex[1] >= 0 && tex[1] < map->textures[wall_side].dim[1])
				color[x][y] =  (*(int *)(map->textures[wall_side].ptr + (tex[1] * map->textures[wall_side].line_length) + 
						(tex[0] * map->textures[wall_side].bits_per_pixel / 8)));
			//printf("color = %d\n", color[x][y]);
			y++;
		}
		x++;
	}
	printf("LLEGO\n");
	print_screen(map, drawstart, drawend, color);
}

//PLAYER_MOVEMENT

int	player_movement(int keycode, t_map *map)
{
	double movespeed;
	double rotspeed;
	double oldirX;
	double oldplaneX;

	movespeed = 0.05;
	rotspeed = 0.05;
	if (keycode == 119)
	{
		map->player.pos[0] += map->player.dir[0] * movespeed;
		map->player.pos[1] += map->player.dir[1] * movespeed;
	}
	if (keycode == 115)
	{
		map->player.pos[0] -= map->player.dir[0] * movespeed;
		map->player.pos[1] -= map->player.dir[1] * movespeed;
	}
	if (keycode == 97)
	{
		oldirX = map->player.dir[0];
		map->player.dir[0] = map->player.dir[0] * cos(-rotspeed) - map->player.dir[1] * sin(-rotspeed);
		map->player.dir[1] = oldirX * sin(-rotspeed) + map->player.dir[1] * cos(-rotspeed);
		oldplaneX = map->player.plane[0];
		map->player.plane[0] = map->player.plane[0] * cos(-rotspeed) - map->player.plane[1] * sin(-rotspeed);
		map->player.plane[1] = oldplaneX * sin(-rotspeed) + map->player.plane[1] * cos(-rotspeed);
	}
	if (keycode == 100)
	{
		oldirX = map->player.dir[0];
		map->player.dir[0] = map->player.dir[0] * cos(rotspeed) - map->player.dir[1] * sin(rotspeed);
		map->player.dir[1] = oldirX * sin(rotspeed) + map->player.dir[1] * cos(rotspeed);
		oldplaneX = map->player.plane[0];
		map->player.plane[0] = map->player.plane[0] * cos(rotspeed) - map->player.plane[1] * sin(rotspeed);
		map->player.plane[1] = oldplaneX * sin(rotspeed) + map->player.plane[1] * cos(rotspeed);
	}
	raycast(map);
	return (0);
}

//MAIN

int main (int argc, char **argv)
{
	t_map	map;

	map.dis.dim[0] = 1440;
	map.dis.dim[1] = 900;
	if (argc != 2)
		error_message("Invalid number of arguments");
	map_reader(&map, argv[1]);
	player_starter(&map);
	image_init(&map);
	put_background(&map);
	assing_sprites(&map);
	raycast(&map);
	mlx_hook(map.dis.mlx_win, 2, 1L << 0, player_movement, &map);
	mlx_loop(map.dis.mlx);
	return (0);
}
