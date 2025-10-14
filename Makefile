NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -O2

# Detect OS
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	MLX_DIR = minilibx-linux
	MLX_LIB = $(MLX_DIR)/libmlx.a
	MLX_INC = -I $(MLX_DIR)
	MLX_LNK = -L $(MLX_DIR) -lmlx -lXext -lX11
	FRAMEWORKS =
else ifeq ($(UNAME_S), Darwin)
	MLX_DIR = minilibx_opengl_20191021
	MLX_LIB = $(MLX_DIR)/libmlx.a
	MLX_INC = -I $(MLX_DIR)
	MLX_LNK = -L $(MLX_DIR) -lmlx
	FRAMEWORKS = -framework OpenGL -framework AppKit
endif

SRCDIR = src
INCDIR = includes

# Mandatory part - No enemies
SRC = $(SRCDIR)/main.c \
      $(SRCDIR)/map_parser.c \
      $(SRCDIR)/map_parse_utils.c \
      $(SRCDIR)/map_validator.c \
      $(SRCDIR)/game_init.c \
      $(SRCDIR)/game_window.c \
      $(SRCDIR)/game_render.c \
      $(SRCDIR)/game_input.c \
      $(SRCDIR)/game_logic.c \
      $(SRCDIR)/sprite_loader.c \
      $(SRCDIR)/sprite_ocean.c \
      $(SRCDIR)/sprite_exit.c \
      $(SRCDIR)/anim_dolphin.c \
      $(SRCDIR)/anim_fish.c \
      $(SRCDIR)/string_utils1.c \
	  $(SRCDIR)/string_utils2.c \
      $(SRCDIR)/animation.c \
      $(SRCDIR)/error_handler.c \
      $(SRCDIR)/cleanup.c \
      $(SRCDIR)/file_utils.c \
      $(SRCDIR)/path_utils.c \
      $(SRCDIR)/render_win.c \
      $(SRCDIR)/render_tile.c

# Bonus part - With enemies
SRC_BONUS = $(SRCDIR)/main.c \
            $(SRCDIR)/map_parser.c \
            $(SRCDIR)/map_parse_utils_bonus.c \
            $(SRCDIR)/map_validator.c \
            $(SRCDIR)/game_init_bonus.c \
            $(SRCDIR)/game_window.c \
            $(SRCDIR)/game_render_bonus.c \
			$(SRCDIR)/game_enemy_init_bonus.c\
            $(SRCDIR)/game_input_bonus.c \
            $(SRCDIR)/game_logic_bonus.c \
            $(SRCDIR)/sprite_loader_bonus.c \
            $(SRCDIR)/sprite_ocean.c \
            $(SRCDIR)/sprite_exit.c \
            $(SRCDIR)/sprite_enemy_bonus.c \
            $(SRCDIR)/anim_dolphin.c \
            $(SRCDIR)/anim_fish.c \
            $(SRCDIR)/enemy_init_bonus.c \
            $(SRCDIR)/enemy_logic_bonus.c \
            $(SRCDIR)/string_utils1.c \
			$(SRCDIR)/string_utils2.c \
            $(SRCDIR)/animation_bonus.c \
            $(SRCDIR)/error_handler.c \
            $(SRCDIR)/cleanup_bonus.c \
            $(SRCDIR)/file_utils.c \
            $(SRCDIR)/path_utils.c \
            $(SRCDIR)/render_win_bonus.c \
            $(SRCDIR)/render_tile_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

INC = -I $(INCDIR) $(MLX_INC)
INC_BONUS = -I $(INCDIR) $(MLX_INC)

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FRAMEWORKS) -lm -o $(NAME)

bonus: $(MLX_LIB) $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) $(MLX_LNK) $(FRAMEWORKS) -lm -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

%_bonus.o: %_bonus.c
	$(CC) $(CFLAGS) $(INC_BONUS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all bonus clean fclean re