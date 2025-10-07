/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render_norm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:14:20 by kmar              #+#    #+#             */
/*   Updated: 2025/10/07 12:14:21 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

static void	render_tile(t_game *game, int map_x, int map_y)
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
	else
		sprite = get_tile_sprite(game, game->map.grid[map_y][map_x]);
	if (!sprite)
		return ;
	screen_x = (map_x - game->camera.x) * TILE_SIZE;
	screen_y = (map_y - game->camera.y) * TILE_SIZE;
	mlx_put_image_to_window(game->mlx, game->window, sprite,
		screen_x, screen_y);
}

static void	print_hud_line(t_game *game, char *label, int value, int y)
{
	char	*num_str;

	mlx_string_put(game->mlx, game->window, 10, y, 0xFFFFFF, label);
	num_str = ft_itoa(value);
	if (num_str)
	{
		mlx_string_put(game->mlx, game->window, 100, y, 0xFFFFFF, num_str);
		free(num_str);
	}
}

static void	render_hud(t_game *game)
{
	print_hud_line(game, "Moves:", game->moves, 20);
	print_hud_line(game, "Items:", game->map.collected, 40);
	if (game->game_won)
		mlx_string_put(game->mlx, game->window, 10, 60, 0x00FF00, "YOU WIN!");
}

void	update_camera(t_game *game)
{
	int	win_tiles_x;
	int	win_tiles_y;

	win_tiles_x = WINDOW_WIDTH / TILE_SIZE;
	win_tiles_y = WINDOW_HEIGHT / TILE_SIZE;
	if (game->map.width <= win_tiles_x)
		game->camera.x = 0;
	else
	{
		game->camera.x = game->map.player.x - win_tiles_x / 2;
		if (game->camera.x < 0)
			game->camera.x = 0;
		if (game->camera.x + win_tiles_x > game->map.width)
			game->camera.x = game->map.width - win_tiles_x;
	}
	if (game->map.height <= win_tiles_y)
		game->camera.y = 0;
	else
	{
		game->camera.y = game->map.player.y - win_tiles_y / 2;
		if (game->camera.y < 0)
			game->camera.y = 0;
		if (game->camera.y + win_tiles_y > game->map.height)
			game->camera.y = game->map.height - win_tiles_y;
	}
}

static void	render_visible_tiles(t_game *game)
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

void	render_game(t_game *game)
{
	if (!game || !game->window)
		return ;
	update_camera(game);
	mlx_clear_window(game->mlx, game->window);
	render_visible_tiles(game);
	render_hud(game);
}
