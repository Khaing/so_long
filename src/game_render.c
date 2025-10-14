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

void	render_game(t_game *game)
{
	if (!game || !game->window)
		return ;
	update_camera(game);
	mlx_clear_window(game->mlx, game->window);
	render_visible_tiles(game);
	render_hud(game);
}
