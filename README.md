# 🐬 so_long - Underwater Adventure Game

A 2D top-down game featuring an underwater sea theme with animated sprites, built with C and MiniLibX for the 42 School curriculum.

![Sea Theme](https://img.shields.io/badge/Theme-Underwater-0080ff?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c)
![Platform](https://img.shields.io/badge/Platform-macOS-000000?style=for-the-badge&logo=apple)

## 📋 Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Game Controls](#game-controls)
- [Map Format](#map-format)
- [Testing](#testing)
- [Project Structure](#project-structure)
- [Technical Details](#technical-details)

## ✨ Features

### Mandatory Requirements ✅
- Map parsing from `.ber` files
- File extension validation
- Rectangular map validation
- Wall enclosure checking
- Valid path detection using flood fill algorithm
- Player movement with WASD and Arrow keys
- Collectible system
- Win condition (collect all items + reach exit)
- Move counter displayed in terminal
- ESC key and window close button exit the game
- Proper error handling with `"Error\n"` prefix
- Memory leak prevention

### Bonus Features 🌟
- **Animated Sprites** (4-frame animations)
  - 🐬 Swimming dolphin player with tail wave motion
  - 🐟 Shimmering golden fish collectibles
- **Camera System** for large maps
  - Smooth scrolling that follows the player
  - Supports maps larger than window size
- **On-Screen HUD**
  - Move counter
  - Collectibles progress (X/Total)
  - Win message display
- **Beautiful Sea Theme**
  - 🪸 Coral reef walls
  - 🌊 Ocean background with water patterns
  - 🌱 Seaweed exit portal
  - All sprites programmatically generated (no external files needed)

## 🔧 Installation

### Prerequisites
- macOS (tested on macOS 10.14+)
- Xcode Command Line Tools
- Make

### Build Instructions

```bash
# Clone the repository
git clone <your-repo-url>
cd so_long

# Compile the project
make

# Run with a map
./so_long maps/medium.ber
```

### Make Commands
```bash
make          # Compile the project
make all      # Same as make
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Clean and recompile
```

## 🎮 Usage

```bash
./so_long <map_file.ber>
```

### Examples
```bash
./so_long maps/tiny.ber       # Small 7x3 map
./so_long maps/simple.ber     # Simple test map
./so_long maps/medium.ber     # Medium 19x11 map
./so_long maps/large.ber      # Large 50x27 map (tests camera)
./so_long maps/challenge.ber  # Challenging maze
```

## 🕹️ Game Controls

| Key | Action |
|-----|--------|
| `W` or `↑` | Move Up |
| `A` or `←` | Move Left |
| `S` or `↓` | Move Down |
| `D` or `→` | Move Right |
| `ESC` | Exit Game |

**Objective:**
1. Control the 🐬 dolphin player
2. Collect all 🐟 fish (collectibles)
3. Reach the 🌱 seaweed exit portal
4. Complete in minimum moves!

## 🗺️ Map Format

Maps are `.ber` files with the following characters:

| Character | Description |
|-----------|-------------|
| `1` | Wall (impassable) |
| `0` | Empty space (water) |
| `C` | Collectible (fish) |
| `E` | Exit (portal) |
| `P` | Player start position (dolphin) |

### Map Requirements
- Must be rectangular
- Must be surrounded by walls (`1`)
- Must contain exactly 1 player (`P`)
- Must contain exactly 1 exit (`E`)
- Must contain at least 1 collectible (`C`)
- Must have a valid path from player to all collectibles and exit
- Minimum size: 3x3

### Example Map
```
1111111
1E0C0P1
1111111
```

## 🧪 Testing

### Automated Tests
```bash
# Run the comprehensive test script
./test_maps.sh
```

This will test:
- ✅ Compilation
- ✅ 15+ error cases
- ✅ Map validation
- ✅ Error message format

### So_long-Tester (gemartin99)
```bash
# The tester is included in the project
bash Tester_so_long.sh
```

**Note:** The tester may hang on valid maps because they open a window and wait for user input (expected behavior). Error map tests will pass successfully.

### Manual Testing Checklist
- [ ] Window opens successfully
- [ ] Animated sprites visible (dolphin swimming, fish shimmering)
- [ ] Player moves with WASD and arrow keys
- [ ] Move counter increments in terminal
- [ ] HUD displays on screen
- [ ] Collectibles disappear when collected
- [ ] Can't move through walls
- [ ] Can't exit until all collectibles gathered
- [ ] Win message displays after collecting all and reaching exit
- [ ] ESC key exits cleanly
- [ ] Window close button works
- [ ] Large maps trigger camera scrolling
- [ ] No memory leaks (test with `leaks --atExit -- ./so_long maps/simple.ber`)

## 📁 Project Structure

```
so_long/
├── Makefile                      # Build configuration
├── README.md                     # This file
├── CLAUDE.md                     # Development instructions
├── test_maps.sh                  # Automated test script
│
├── includes/
│   └── so_long.h                 # Main header file
│
├── src/
│   ├── main.c                    # Entry point & extension validation
│   ├── map_parser.c              # Map file reading & parsing
│   ├── map_validator.c           # Map validation & flood fill
│   ├── game_init.c               # Game initialization
│   ├── game_render.c             # Rendering engine & camera system
│   ├── game_input.c              # Keyboard input handling
│   ├── game_logic.c              # Game logic & win conditions
│   ├── sprite_loader.c           # Programmatic sprite generation
│   ├── sprite_loader_simple.c    # Simple sprite loader
│   ├── animation.c               # Animation system (30 FPS)
│   ├── error_handler.c           # Centralized error handling
│   └── cleanup.c                 # Memory cleanup & resource freeing
│
├── maps/                         # Valid test maps
│   ├── tiny.ber                  # Smallest valid map (3x7)
│   ├── simple.ber                # Simple test map
│   ├── medium.ber                # Medium sized map (11x19)
│   ├── complex.ber               # Complex layout
│   ├── large.ber                 # Large map (27x50)
│   ├── challenge.ber             # Challenging maze (23x21)
│   ├── invalid_*.ber             # Error test cases
│   └── ...
│
├── maps_valid/                   # Tester valid maps (16 maps)
├── maps_err/                     # Tester error maps (51 maps)
│
├── minilibx_opengl_20191021/     # MiniLibX graphics library
└── textures/                     # Sprite documentation
    ├── README.md                 # Sprite descriptions
    └── palette.txt               # Color palette info
```

## 🔬 Technical Details

### Graphics Engine
- **Library:** MiniLibX (OpenGL backend for macOS)
- **Window Size:** 1024x768 pixels (adjustable for map size)
- **Tile Size:** 64x64 pixels
- **Animation:** 4 frames at ~30 FPS (updated every 25 frames)
- **Camera:** Dynamic viewport that follows player on large maps

### Sprite Generation
All sprites are **programmatically generated** at runtime:
- No external image files required
- 64x64 pixel resolution
- 24-bit RGB colors
- Pixel-by-pixel manipulation using `mlx_get_data_addr`
- Mathematical functions for animation (sine waves for swimming motion)

### Algorithms
1. **Flood Fill Path Validation**
   - Creates a copy of the map grid
   - Recursively fills from player starting position
   - Verifies all collectibles and exit are reachable
   - Prevents invalid maps from loading

2. **Camera System**
   - Centers camera on player position
   - Handles boundary constraints
   - Smooth scrolling for maps larger than viewport

3. **Animation System**
   - Frame counter increments on every loop iteration
   - Sprite frame changes every 25 frames
   - Sine wave calculations for smooth swimming motion

### Memory Management
- All heap-allocated memory properly freed
- Image cleanup on exit
- Window destruction handled
- Map grid deallocated
- No memory leaks (verified with `leaks` tool)

### Compilation Flags
```
-Wall -Wextra -Werror -O2
-framework OpenGL -framework AppKit
-lmlx -lm
```

## 📊 Code Statistics
- **Total Lines:** ~1,271 lines of C code
- **Source Files:** 12 `.c` files
- **Functions:** 50+ functions
- **Test Maps:** 74 maps (16 valid, 51 error cases, 7 custom)

## 🎨 Color Palette

### Dolphin Player
- Ocean Blues: `#4A90E2`, `#5DADE2`, `#87CEEB`

### Fish Collectibles
- Golden Yellows: `#FFD700`, `#FFE135`, `#FFA500`

### Coral Walls
- Coral Pinks: `#FF69B4`, `#FF1493`, `#FF6347`, `#DC143C`

### Ocean Background
- Deep Blues: `#006994`, `#4A90E2`, `#87CEEB`

### Seaweed Exit
- Sea Greens: `#228B22`, `#32CD32`, `#00FF7F`, `#90EE90`

## 🐛 Known Limitations

1. **Display Requirement:** The game requires a graphical display and cannot run in pure terminal/SSH environments
2. **macOS Only:** Built specifically for macOS using OpenGL and AppKit frameworks
3. **Background Testing:** The game cannot be fully tested in background mode as it requires window rendering

## 📝 Error Handling

The program outputs `"Error\n"` followed by a descriptive message for:
- Invalid file extension (not `.ber`)
- File not found
- Empty or malformed maps
- Non-rectangular maps
- Missing player, exit, or collectibles
- Duplicate player or exit
- Map not enclosed by walls
- No valid path to collectibles or exit
- Maps too small (< 3x3)

## 🏆 Evaluation Checklist

- [x] Compiles with `-Wall -Wextra -Werror`
- [x] No memory leaks
- [x] Proper error handling
- [x] Map validation (rectangular, walls, valid path)
- [x] Player movement (WASD + Arrows)
- [x] Collectible system
- [x] Win condition
- [x] Move counter
- [x] ESC and window close work
- [x] Makefile with required rules
- [x] Bonus: Sprite animation
- [x] Bonus: Camera system for large maps
- [x] Bonus: On-screen HUD

## 🤝 Contributing

This is a school project for 42 School curriculum. Feel free to:
- Report bugs
- Suggest improvements
- Use as reference (respect your school's academic integrity policy)

## 📄 License

This project is created for educational purposes as part of the 42 School curriculum.

## 🙏 Acknowledgments

- 42 School for the project subject
- MiniLibX library developers
- [gemartin99](https://github.com/gemartin99) for the So_long-Tester
- Claude Code for code review and assistance

---

**Made with 💙 and C** | **42 School Project** | **Last Updated: 2025**
