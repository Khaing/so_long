#include "../includes/so_long.h"

void	check_win_condition(t_game *game)
{
	if (game->map.collected == game->map.collectibles)
	{
		if (game->map.player.x == game->map.exit.x &&
			game->map.player.y == game->map.exit.y)
		{
			game->game_won = 1;
			ft_putstr(WIN_MSG);
			ft_putstr("Total moves: ");
			ft_putnbr(game->moves);
			ft_putstr("\n");
		}
	}
}