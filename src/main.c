#include "../includes/so_long.h"

static int	check_file_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	
	len = strlen(filename);
	if (len < 4)
		return (0);
	
	if (strcmp(filename + len - 4, ".ber") != 0)
		return (0);
	
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_error("Usage: ./so_long map_file.ber");
		return (1);
	}
	
	if (!check_file_extension(argv[1]))
	{
		print_error("Map file must have .ber extension");
		return (1);
	}
	
	if (!init_game(&game, argv[1]))
		return (1);
	
	render_game(&game);
	mlx_loop(game.mlx);
	
	return (0);
}