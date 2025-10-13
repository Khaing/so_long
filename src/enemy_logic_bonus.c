/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_logic_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:00:00 by kmar              #+#    #+#             */
/*   Updated: 2025/10/13 00:00:00 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	check_enemy_collision(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].pos.x == game->map.player.x
			&& game->enemies[i].pos.y == game->map.player.y)
		{
			game->game_over = 1;
			return ;
		}
		i++;
	}
}

void	update_enemies(t_game *game)
{
	(void)game;
}
