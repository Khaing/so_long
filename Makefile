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

SRC = $(SRCDIR)/main.c \
      $(SRCDIR)/map_parser.c \
      $(SRCDIR)/map_parse_utils.c \
      $(SRCDIR)/map_validator.c \
      $(SRCDIR)/game_init.c \
      $(SRCDIR)/game_window.c \
      $(SRCDIR)/game_render_norm.c \
      $(SRCDIR)/game_input.c \
      $(SRCDIR)/game_logic.c \
      $(SRCDIR)/sprite_loader_norm.c \
      $(SRCDIR)/sprite_ocean.c \
      $(SRCDIR)/sprite_exit.c \
      $(SRCDIR)/anim_dolphin.c \
      $(SRCDIR)/anim_fish.c \
      $(SRCDIR)/string_utils.c \
      $(SRCDIR)/animation.c \
      $(SRCDIR)/error_handler.c \
      $(SRCDIR)/cleanup.c \
      $(SRCDIR)/file_utils.c \
      $(SRCDIR)/path_utils.c \
      $(SRCDIR)/render_win.c \
      $(SRCDIR)/render_tile.c

OBJ = $(SRC:.c=.o)

INC = -I $(INCDIR) $(MLX_INC)

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FRAMEWORKS) -lm -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re