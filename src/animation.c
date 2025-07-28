#include "../includes/so_long.h"

int	animation_loop(t_game *game)
{
	game->frame_counter++;
	
	if (game->frame_counter % 25 == 0)
	{
		game->sprites.current_frame = (game->sprites.current_frame + 1) % game->sprites.frame_count;
		render_game(game);
	}
	
	return (0);
}