/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:00:00 by kmar              #+#    #+#             */
/*   Updated: 2025/10/08 00:00:00 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

static void	draw_win_text(t_game *game, int cx, int cy, int pulse)
{
	char	*moves_str;

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

void	render_win_screen(t_game *game)
{
	int		cx;
	int		cy;
	int		pulse;

	cx = WINDOW_WIDTH / 2;
	cy = WINDOW_HEIGHT / 2;
	if (cx > (game->map.width - game->camera.x) * TILE_SIZE)
		cx = ((game->map.width - game->camera.x) * TILE_SIZE) / 2;
	if (cy > (game->map.height - game->camera.y) * TILE_SIZE)
		cy = ((game->map.height - game->camera.y) * TILE_SIZE) / 2;
	pulse = (game->frame_counter / 10) % 10;
	draw_win_box(game, cx, cy, pulse);
	draw_win_text(game, cx, cy, pulse);
}
