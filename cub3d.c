/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcid-gon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:25:32 by jcid-gon          #+#    #+#             */
/*   Updated: 2022/09/05 15:52:38 by jcid-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//UTILS

void	error_message(char *str)
{
	printf("Error\n%s\n", str);
	exit (1);
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
					map->north = ft_strdup(str[1]);
				else if (ft_strncmp(str[0], "SO", 2) == 0)
					map->south = ft_strdup(str[1]);
				else if (ft_strncmp(str[0], "WE", 2) == 0)
					map->west = ft_strdup(str[1]);
				else if (ft_strncmp(str[0], "EA", 2) == 0)
					map->east = ft_strdup(str[1]);
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
	printf("NORTH = %s\n", map->north);
	printf("SOUTH = %s\n", map->south);
	printf("WEST = %s\n", map->west);
	printf("EAST = %s\n", map->east);
	printf("FLOOR = %s\n", map->floor);
	printf("CEILING = %s\n", map->ceiling);
}

//MAIN

int main (int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		error_message("Invalid number of arguments");
	map_reader(&map, argv[1]);
	return (0);
}
