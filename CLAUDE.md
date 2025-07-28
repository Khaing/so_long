# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a **so_long** project - a 2D game implementation using C and the MiniLibX graphics library. The project is part of the 42 School curriculum and focuses on basic computer graphics programming, window management, and event handling.

**Current Status**: Project contains MiniLibX library but no source code implementation yet.

## Development Commands

### MiniLibX Library Build
```bash
cd minilibx_opengl_20191021/
make                    # Build libmlx.a library
make clean             # Remove object files
make re                # Clean and rebuild
```

### Project Build Commands (when implemented)
```bash
make                    # Build the so_long executable
make all               # Same as make
make clean             # Remove object files
make fclean            # Remove object files and executable
make re                # Clean and rebuild
make bonus             # Build with bonus features (if implemented)
```

### Required Compiler Flags
- `-Wall -Wextra -Werror` (mandatory)
- `-framework OpenGL -framework AppKit` (macOS)
- Link with libmlx.a and math library: `-lm`

### Running the Game
```bash
./so_long maps/map_file.ber    # Run with a specific map file
```

## Architecture and Structure

### MiniLibX Integration
- **Library Location**: `minilibx_opengl_20191021/`
- **Header**: `mlx.h` contains all graphics function declarations
- **Platform**: macOS version using OpenGL and AppKit frameworks
- **Key Functions**: Window management, image handling, event hooks, pixel manipulation

### Required Implementation Structure
```
project/
├── Makefile
├── *.h (headers)
├── *.c (sources) 
├── maps/ (map files - .ber format)
├── textures/ (sprite files)
├── minilibx_opengl_20191021/ (graphics library)
└── libft/ (if using libft)
```

### Core Components to Implement
- **Game Engine**: 2D top-down or profile view game
- **Map Parser**: Read and validate .ber map files
- **Input Handler**: WASD/ZQSD/Arrow keys for movement
- **Graphics Renderer**: Sprite-based rendering with MiniLibX
- **Game Logic**: Collectible tracking, movement validation, win conditions

### Map Format Requirements (.ber files)
Maps use 5 characters:
- `0`: Empty space
- `1`: Wall
- `C`: Collectible
- `E`: Exit
- `P`: Player starting position

### Validation Rules
- Exactly 1 exit and 1 starting position
- At least 1 collectible
- Map must be rectangular and surrounded by walls
- Valid path must exist from start to all collectibles and exit
- Error handling with "Error\n" prefix for invalid maps

### MiniLibX Key Functions
- `mlx_init()`: Initialize graphics system
- `mlx_new_window()`: Create game window
- `mlx_xpm_file_to_image()` / `mlx_png_file_to_image()`: Load textures
- `mlx_hook()`: Handle keyboard and window events
- `mlx_loop()`: Main game loop

### Memory Management
- All heap-allocated memory must be freed
- No segfaults, bus errors, or double frees allowed
- Clean exit on ESC key or window close
- Destroy images and windows before exit

### Implementation Notes
- Movement counter displayed in shell (mandatory) or on-screen (bonus)
- Game uses discrete movement (not real-time)
- Window management must remain smooth
- Path validation algorithm needed for map verification
- Alpha channel represents transparency in images