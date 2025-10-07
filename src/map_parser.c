/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:18:29 by kmar              #+#    #+#             */
/*   Updated: 2025/10/07 12:19:56 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffer;
	char	c;
	int		i;
	int		ret;

	buffer = malloc(10000);
	if (!buffer)
		return (NULL);
	i = 0;
	ret = read(fd, &c, 1);
	while (ret && c != '\n' && i < 9999)
	{
		if (c != '\r')
			buffer[i++] = c;
		ret = read(fd, &c, 1);
	}
	if (ret == 0 && i == 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[i] = '\0';
	line = malloc(strlen(buffer) + 1);
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	strcpy(line, buffer);
	free(buffer);
	return (line);
}

int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	lines = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		lines++;
		free(line);
	}
	close(fd);
	return (lines);
}

static void	init_map_data(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->collectibles = 0;
	map->collected = 0;
	map->player.x = -1;
	map->player.y = -1;
	map->exit.x = -1;
	map->exit.y = -1;
}

static int	parse_map_line(t_map *map, char *line, int y)
{
	int	x;

	if (!line || strlen(line) == 0)
		return (0);
	if (map->width == 0)
		map->width = strlen(line);
	else if ((int)strlen(line) != map->width)
		return (0);
	x = 0;
	while (line[x])
	{
		if (line[x] == MAP_PLAYER)
		{
			if (map->player.x != -1)
				return (0);
			map->player.x = x;
			map->player.y = y;
		}
		else if (line[x] == MAP_EXIT)
		{
			if (map->exit.x != -1)
				return (0);
			map->exit.x = x;
			map->exit.y = y;
		}
		else if (line[x] == MAP_COLLECTIBLE)
			map->collectibles++;
		else if (line[x] != MAP_WALL && line[x] != MAP_EMPTY)
			return (0);
		x++;
	}
	return (1);
}

int	parse_map(t_game *game, char *filename)
{
	int		fd;
	int		y;
	char	*line;

	init_map_data(&game->map);
	game->map.height = count_lines(filename);
	if (game->map.height <= 0 || game->map.height < 3)
		return (0);
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(game->map.grid);
		game->map.grid = NULL;
		return (0);
	}
	y = 0;
	while (y < game->map.height && (line = get_next_line(fd)) != NULL)
	{
		if (!parse_map_line(&game->map, line, y))
		{
			free(line);
			while (--y >= 0)
				free(game->map.grid[y]);
			free(game->map.grid);
			game->map.grid = NULL;
			close(fd);
			return (0);
		}
		game->map.grid[y] = line;
		y++;
	}
	close(fd);
	if (y != game->map.height)
	{
		while (--y >= 0)
			free(game->map.grid[y]);
		free(game->map.grid);
		game->map.grid = NULL;
		return (0);
	}
	game->map.grid[y] = NULL;
	if (game->map.player.x == -1 || game->map.exit.x == -1
		|| game->map.collectibles == 0)
	{
		free_map(game->map.grid);
		game->map.grid = NULL;
		return (0);
	}
	return (1);
}
