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

static void	draw_win_box(t_game *game, int cx, int cy, int pulse)
{
	int	x;
	int	y;
	int	color;

	y = cy - 100 - pulse;
	while (y < cy + 100 + pulse)
	{
		x = cx - 250;
		while (x < cx + 250)
		{
			if (y == cy - 100 - pulse || y == cy + 100 + pulse - 1
				|| x == cx - 250 || x == cx + 249)
				color = 0xFFD700 + (pulse * 0x001100);
			else
				color = 0x001A33 + (pulse * 0x000511);
			mlx_pixel_put(game->mlx, game->window, x, y, color);
			x++;
		}
		y++;
	}
}

static void	render_win_screen(t_game *game)
{
	int		cx;
	int		cy;
	int		pulse;
	char	*moves_str;

	cx = WINDOW_WIDTH / 2;
	cy = WINDOW_HEIGHT / 2;
	if (cx > (game->map.width - game->camera.x) * TILE_SIZE)
		cx = ((game->map.width - game->camera.x) * TILE_SIZE) / 2;
	if (cy > (game->map.height - game->camera.y) * TILE_SIZE)
		cy = ((game->map.height - game->camera.y) * TILE_SIZE) / 2;
	pulse = (game->frame_counter / 10) % 10;
	draw_win_box(game, cx, cy, pulse);
	mlx_string_put(game->mlx, game->window, cx - 120, cy - 40,
		0xFFFF00 + (pulse * 0x001100), "CONGRATULATIONS!");
	mlx_string_put(game->mlx, game->window, cx - 80, cy,
		0x00FF00, "YOU WIN!");
	mlx_string_put(game->mlx, game->window, cx - 100, cy + 40,
		0xFFFFFF, "Total Moves:");
	moves_str = ft_itoa(game->moves);
	if (moves_str)
	{
		mlx_string_put(game->mlx, game->window, cx + 50, cy + 40,
			0xFFD700, moves_str);
		free(moves_str);
	}
	mlx_string_put(game->mlx, game->window, cx - 120, cy + 70,
		0x888888, "Press ESC to exit");
}

static void	render_hud(t_game *game)
{
	print_hud_line(game, "Moves:", game->moves, 20);
	print_hud_line(game, "Items:", game->map.collected, 40);
	if (game->game_won)
		render_win_screen(game);
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
