/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:00:00 by kmar              #+#    #+#             */
/*   Updated: 2025/10/08 00:00:00 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	create_window(t_game *game)
{
	int	window_width;
	int	window_height;

	window_width = game->map.width * TILE_SIZE;
	window_height = game->map.height * TILE_SIZE;
	if (window_width > WINDOW_WIDTH)
		window_width = WINDOW_WIDTH;
	if (window_height > WINDOW_HEIGHT)
		window_height = WINDOW_HEIGHT;
	game->window = mlx_new_window(game->mlx, window_width, window_height,
			"so_long");
	if (!game->window)
		return (0);
	return (1);
}
