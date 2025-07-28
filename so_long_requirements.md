# So Long - Project Requirements
*And thanks for all the fish!*

## Summary
This project is a small 2D game. Its purpose is to have you work with textures, sprites, and other basic gameplay elements.

**Version:** 3.2

## Objectives
Create a basic computer graphics project using the MiniLibX library. This will help improve skills in:
- Window management
- Event handling
- Colors and textures
- C programming
- Basic algorithms

## Common Instructions
- Project must be written in C
- Must comply with the Norm (coding standard)
- Functions should not quit unexpectedly (no segfaults, bus errors, double free, etc.)
- All heap-allocated memory must be properly freed
- Must include a Makefile with flags: -Wall, -Wextra, -Werror
- Makefile must include rules: $(NAME), all, clean, fclean, re
- For bonuses: include bonus rule in Makefile, bonus files in _bonus.{c/h} format
- If using libft, copy sources and Makefile to libft folder

## Mandatory Part

### Program Details
- **Program name:** so_long
- **Turn in files:** Makefile, *.h, *.c, maps, textures
- **Arguments:** A map in format *.ber
- **External functions allowed:**
  - open, close, read, write, malloc, free, perror, strerror, exit
  - All functions of the math library (-lm compiler option)
  - All functions of the MiniLibX
  - ft_printf and any equivalent YOU coded
- **Libft:** Yes (authorized)

### Game Description
Create a basic 2D game in which a dolphin escapes Earth after eating some fish. (You can use any character, collectible, and place you want.)

### Game Rules

#### IV.1 Game Mechanics
- Player's goal: collect all collectibles on the map, then escape by choosing the shortest possible route
- Controls: W, A, S, D keys (or ZQSD or arrow keys) for movement
- Movement directions: up, down, left, right
- Player cannot move into walls
- Display current number of movements in the shell at every move
- Use 2D view (top-down or profile)
- Game does not need to be real-time

#### IV.2 Graphic Management
- Program must display the image in a window
- Window management must remain smooth (switching windows, minimizing, etc.)
- ESC key must close window and quit program cleanly
- Clicking the cross on window frame must close window and quit program cleanly
- Must use MiniLibX images

#### IV.3 Map Requirements
- Map constructed with 3 components: walls, collectibles, and free space
- Map composed of only these 5 characters:
  - `0` for empty space
  - `1` for wall
  - `C` for collectible
  - `E` for map exit
  - `P` for player's starting position

#### Map Validation Rules
- Must contain exactly 1 exit, 1 starting position, and at least 1 collectible
- If duplicate characters (exit/start) exist, display error message
- Map must be rectangular
- Map must be enclosed/surrounded by walls
- Must verify there is a valid path in the map
- Must be able to parse any map respecting the above rules
- If misconfiguration encountered, exit cleanly and return "Error\n" followed by explicit error message

#### Example Valid Maps

**Simple map:**
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

**Minimal map:**
```
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
```

## Bonus Part
**Note:** Bonus part only assessed if mandatory part is PERFECT.

Extra points for:
- Make player lose when touching an enemy patrol
- Add sprite animation
- Display movement count directly on screen instead of shell

You can use additional functions for bonus part if justified during evaluation.

## Key Implementation Notes
- Use MiniLibX library (school version or install from sources)
- Handle all edge cases for map validation
- Implement clean error handling
- Ensure smooth window management
- Path validation is crucial (player must be able to reach all collectibles and exit)
- Memory management is critical (no leaks allowed)

## File Structure
```
project/
├── Makefile
├── *.h (header files)
├── *.c (source files)
├── maps/ (map files)
├── textures/ (texture files)
└── libft/ (if using libft)
```