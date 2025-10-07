/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:13:56 by kmar              #+#    #+#             */
/*   Updated: 2025/10/07 12:14:12 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	check_win_condition(t_game *game)
{
	if (game->map.collected == game->map.collectibles)
	{
		if (game->map.player.x == game->map.exit.x
			&& game->map.player.y == game->map.exit.y)
		{
			game->game_won = 1;
			ft_putstr(WIN_MSG);
			ft_putstr("Total moves: ");
			ft_putnbr(game->moves);
			ft_putstr("\n");
		}
	}
}
