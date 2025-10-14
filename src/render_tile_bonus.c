/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tile_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:00:00 by kmar              #+#    #+#             */
/*   Updated: 2025/10/14 14:06:48 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	*get_tile_sprite(t_game *game, char tile)
{
	if (tile == MAP_WALL)
		return (game->sprites.wall);
	else if (tile == MAP_COLLECTIBLE)
		return (game->sprites.collectible[game->sprites.current_frame]);
	else if (tile == MAP_EXIT)
		return (game->sprites.exit);
	else
		return (game->sprites.empty);
}

static int	is_enemy_at(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].pos.x == x && game->enemies[i].pos.y == y)
			return (1);
		i++;
	}
	return (0);
}

void	render_tile(t_game *game, int map_x, int map_y)
{
	void	*sprite;
	int		screen_x;
	int		screen_y;

	if (map_x >= game->map.width || map_y >= game->map.height)
		return ;
	if (map_x < 0 || map_y < 0)
		return ;
	if (map_x == game->map.player.x && map_y == game->map.player.y)
		sprite = game->sprites.player[game->sprites.current_frame];
	else if (is_enemy_at(game, map_x, map_y))
		sprite = game->sprites.enemy[game->sprites.current_frame % 2];
	else
		sprite = get_tile_sprite(game, game->map.grid[map_y][map_x]);
	if (!sprite)
		return ;
	screen_x = (map_x - game->camera.x) * TILE_SIZE;
	screen_y = (map_y - game->camera.y) * TILE_SIZE;
	mlx_put_image_to_window(game->mlx, game->window, sprite,
		screen_x, screen_y);
}

void	render_visible_tiles(t_game *game)
{
	int	x;
	int	y;
	int	max_x;
	int	max_y;

	max_x = game->camera.x + (WINDOW_WIDTH / TILE_SIZE);
	max_y = game->camera.y + (WINDOW_HEIGHT / TILE_SIZE);
	if (max_x > game->map.width)
		max_x = game->map.width;
	if (max_y > game->map.height)
		max_y = game->map.height;
	y = game->camera.y - 1;
	while (++y < max_y)
	{
		x = game->camera.x - 1;
		while (++x < max_x)
			render_tile(game, x, y);
	}
}
