/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:18:29 by kmar              #+#    #+#             */
/*   Updated: 2025/10/14 17:43:11 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	parse_map_line(t_map *map, char *line, int y)
{
	int	x;

	if (!line || ft_strlen(line) == 0)
		return (0);
	if (strncmp(line, "(null)", 6) == 0)
		return (0);
	if (map->width == 0)
		map->width = ft_strlen(line);
	else if ((int)ft_strlen(line) != map->width)
		return (0);
	x = 0;
	while (line[x])
	{
		if (!process_map_char(map, line[x], x, y))
			return (0);
		x++;
	}
	return (1);
}

static int	validate_parsed_map(t_game *game, int y)
{
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

static void	line_check(t_game *game, char *line, int *y)
{
	free(line);
	while (--*y >= 0)
		free(game->map.grid[*y]);
	free(game->map.grid);
	game->map.grid = NULL;
}

static int	read_map_file(t_game *game, int fd)
{
	int		y;
	char	*line;

	y = 0;
	line = get_next_line(fd);
	while (y < game->map.height && line != NULL)
	{
		if (!parse_map_line(&game->map, line, y))
		{
			line_check(game, line, &y);
			return (0);
		}
		game->map.grid[y] = line;
		y++;
		line = get_next_line(fd);
	}
	if (line != NULL)
	{
		line_check(game, line, &y);
		return (0);
	}
	return (validate_parsed_map(game, y));
}

int	parse_map(t_game *game, char *filename)
{
	int		fd;
	int		result;

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
	result = read_map_file(game, fd);
	close(fd);
	return (result);
}
