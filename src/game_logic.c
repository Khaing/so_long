#include "../includes/so_long.h"

void	check_win_condition(t_game *game)
{
	if (game->map.collected == game->map.collectibles)
	{
		if (game->map.player.x == game->map.exit.x && 
			game->map.player.y == game->map.exit.y)
		{
			game->game_won = 1;
			printf(WIN_MSG);
			printf("Total moves: %d\n", game->moves);
		}
	}
}