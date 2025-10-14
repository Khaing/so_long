/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_win_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:00:00 by kmar              #+#    #+#             */
/*   Updated: 2025/10/14 14:07:03 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	draw_win_text(t_game *game, int cx, int cy)
{
	char	*moves_str;
	int		color;

	color = 0xFFFF00;
	mlx_string_put(game->mlx, game->window, cx - 120, cy - 40,
		color, "CONGRATULATIONS!");
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

void	render_win_screen(t_game *game)
{
	int		cx;
	int		cy;

	cx = WINDOW_WIDTH / 2;
	cy = WINDOW_HEIGHT / 2;
	if (cx > (game->map.width - game->camera.x) * TILE_SIZE)
		cx = ((game->map.width - game->camera.x) * TILE_SIZE) / 2;
	if (cy > (game->map.height - game->camera.y) * TILE_SIZE)
		cy = ((game->map.height - game->camera.y) * TILE_SIZE) / 2;
	draw_win_text(game, cx, cy);
}

void	render_lose_screen(t_game *game)
{
	int		cx;
	int		cy;

	cx = WINDOW_WIDTH / 2;
	cy = WINDOW_HEIGHT / 2;
	if (cx > (game->map.width - game->camera.x) * TILE_SIZE)
		cx = ((game->map.width - game->camera.x) * TILE_SIZE) / 2;
	if (cy > (game->map.height - game->camera.y) * TILE_SIZE)
		cy = ((game->map.height - game->camera.y) * TILE_SIZE) / 2;
	mlx_string_put(game->mlx, game->window, cx - 80, cy - 20,
		0xFF0000, "GAME OVER!");
	mlx_string_put(game->mlx, game->window, cx - 120, cy + 20,
		0xFF8888, "You touched an enemy!");
	mlx_string_put(game->mlx, game->window, cx - 120, cy + 50,
		0x888888, "Press ESC to exit");
}
