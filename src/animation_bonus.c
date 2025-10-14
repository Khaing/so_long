/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:07:00 by kmar              #+#    #+#             */
/*   Updated: 2025/10/07 12:10:13 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

int	animation_loop(t_game *game)
{
	static int	end_screen_rendered = 0;

	game->frame_counter++;
	if (!game->game_over && !game->game_won && game->enemy_count > 0)
		update_enemies(game);
	if (game->frame_counter % 25 == 0 && !game->game_won && !game->game_over)
	{
		game->sprites.current_frame = (game->sprites.current_frame + 1)
			% game->sprites.frame_count;
		render_game(game);
		end_screen_rendered = 0;
	}
	if ((game->game_won || game->game_over) && !end_screen_rendered)
	{
		render_game(game);
		end_screen_rendered = 1;
	}
	return (0);
}
