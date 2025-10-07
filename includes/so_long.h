/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:03:24 by kmar              #+#    #+#             */
/*   Updated: 2025/10/07 12:21:48 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

# ifdef __APPLE__
#  include "../minilibx_opengl_20191021/mlx.h"
# else
#  include "../minilibx-linux/mlx.h"
# endif

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define TILE_SIZE 64
# define VIEWPORT_WIDTH 16
# define VIEWPORT_HEIGHT 12

/* Key codes - macOS */
# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_UP 126
#  define KEY_LEFT 123
#  define KEY_DOWN 125
#  define KEY_RIGHT 124
# else
/* Key codes - Linux */
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_UP 65362
#  define KEY_LEFT 65361
#  define KEY_DOWN 65364
#  define KEY_RIGHT 65363
# endif

# define MAP_WALL '1'
# define MAP_EMPTY '0'
# define MAP_COLLECTIBLE 'C'
# define MAP_EXIT 'E'
# define MAP_PLAYER 'P'

# define ERROR_MSG "Error\n"
# define WIN_MSG "Congratulations! You won!\n"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			collectibles;
	int			collected;
	t_position	player;
	t_position	exit;
}	t_map;

typedef struct s_sprites
{
	void	*wall;
	void	*empty;
	void	*collectible[4];
	void	*exit;
	void	*player[4];
	int		width;
	int		height;
	int		current_frame;
	int		frame_count;
}	t_sprites;

typedef struct s_camera
{
	int	x;
	int	y;
	int	offset_x;
	int	offset_y;
}	t_camera;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_sprites	sprites;
	t_camera	camera;
	int			moves;
	int			game_won;
	int			frame_counter;
}	t_game;

int		parse_map(t_game *game, char *filename);
int		validate_map(t_map *map);
int		init_game(t_game *game, char *map_file);
int		load_sprites(t_game *game);
void	*create_colored_square(void *mlx, int size, int color);
void	*create_dolphin(void *mlx, int size);
void	*create_fish(void *mlx, int size);
void	*create_exit_gate(void *mlx, int size);
void	*create_coral(void *mlx, int size);
void	*create_ocean(void *mlx, int size);
void	render_game(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		handle_close(t_game *game);
void	move_player(t_game *game, int new_x, int new_y);
void	check_win_condition(t_game *game);
void	print_error(char *message);
void	cleanup_game(t_game *game);
void	free_map(char **map);
int		count_lines(char *filename);
char	*get_next_line(int fd);
int		is_valid_path(t_map *map);
void	update_camera(t_game *game);
int		animation_loop(t_game *game);
void	ft_putstr(char *str);
void	ft_putnbr(int n);
char	*ft_itoa(int n);

#endif