/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:12:40 by kmar              #+#    #+#             */
/*   Updated: 2025/10/07 12:13:31 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static int	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map.width
		|| new_y < 0 || new_y >= game->map.height)
		return (0);
	if (game->map.grid[new_y][new_x] == MAP_WALL)
		return (0);
	return (1);
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (!is_valid_move(game, new_x, new_y))
		return ;
	if (game->game_won || game->game_over)
		return ;
	game->map.player.x = new_x;
	game->map.player.y = new_y;
	game->moves++;
	ft_putstr("Moves: ");
	ft_putnbr(game->moves);
	ft_putstr("\n");
	if (game->map.grid[new_y][new_x] == MAP_COLLECTIBLE)
	{
		game->map.grid[new_y][new_x] = MAP_EMPTY;
		game->map.collected++;
		ft_putstr("Collected: ");
		ft_putnbr(game->map.collected);
		ft_putstr("/");
		ft_putnbr(game->map.collectibles);
		ft_putstr("\n");
	}
	check_enemy_collision(game);
	if (game->game_over)
		ft_putstr(LOSE_MSG);
	else
		check_win_condition(game);
	render_game(game);
}

int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	if (keycode == KEY_ESC)
	{
		handle_close(game);
		return (0);
	}
	new_x = game->map.player.x;
	new_y = game->map.player.y;
	if (keycode == KEY_W || keycode == KEY_UP)
		new_y--;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		new_y++;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		new_x--;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		new_x++;
	else
		return (0);
	move_player(game, new_x, new_y);
	return (0);
}

int	handle_close(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
