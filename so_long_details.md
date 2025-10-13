# So_Long Project Documentation

## Table of Contents
1. [Project Overview](#project-overview)
2. [Architecture](#architecture)
3. [Code Flow](#code-flow)
4. [Module Details](#module-details)
5. [Data Structures](#data-structures)
6. [Game Loop](#game-loop)
7. [Rendering System](#rendering-system)
8. [Input Handling](#input-handling)
9. [Map System](#map-system)
10. [Animation System](#animation-system)
11. [Enemy System (Bonus)](#enemy-system-bonus)
12. [Memory Management](#memory-management)

---

## Project Overview

**So_Long** is a simple 2D game where a player (dolphin) must collect all items (fish) and reach the exit while avoiding enemies (bonus feature). The game is built using the MiniLibX graphics library.

### Game Rules
- Collect all fish ('C') to open the exit
- Reach the exit ('E') to win
- Avoid enemies ('N') in bonus version
- Movement is tracked and displayed

### Key Features
- **Mandatory**: Basic gameplay with animations
- **Bonus**: Static enemies, lose screen, move counter

---

## Architecture

### Directory Structure
```
so_long/
├── includes/
│   ├── so_long.h              # Mandatory header
│   └── so_long_bonus.h        # Bonus header
├── src/
│   ├── main.c                 # Entry point
│   ├── map_parser.c           # Map file parsing
│   ├── map_validator.c        # Map validation logic
│   ├── game_init.c            # Game initialization
│   ├── game_logic.c           # Core game logic
│   ├── game_input.c           # Keyboard input handling
│   ├── game_render_norm.c     # Rendering system
│   ├── animation.c            # Animation loop
│   ├── sprite_*.c             # Sprite creation
│   ├── render_*.c             # Rendering utilities
│   ├── cleanup.c              # Memory cleanup
│   └── *_bonus.c              # Bonus implementations
├── maps/                      # Map files (.ber)
└── Makefile
```

---

## Code Flow

### 1. Program Startup Flow

```
main()
  │
  ├─→ Validate arguments (check map file)
  │
  ├─→ init_game()
  │     │
  │     ├─→ init_game_data()          # Initialize all pointers to NULL
  │     │
  │     ├─→ parse_map()               # Read and parse .ber file
  │     │     ├─→ count_lines()       # Count map height
  │     │     ├─→ allocate grid
  │     │     └─→ read lines with get_next_line()
  │     │
  │     ├─→ validate_map()            # Validate map rules
  │     │     ├─→ Check rectangular shape
  │     │     ├─→ Check walls (borders)
  │     │     ├─→ Check required elements (P, E, C)
  │     │     └─→ is_valid_path() (flood fill algorithm)
  │     │
  │     ├─→ mlx_init()                # Initialize MiniLibX
  │     │
  │     ├─→ create_window()           # Create game window
  │     │
  │     ├─→ init_enemies() (bonus)    # Initialize static enemies
  │     │
  │     ├─→ load_sprites()            # Create all sprites
  │     │     ├─→ create_ocean()
  │     │     ├─→ create_coral()
  │     │     ├─→ create_exit_gate()
  │     │     ├─→ create_dolphin_anim() × 4
  │     │     ├─→ create_fish_anim() × 4
  │     │     └─→ create_enemy_sprite() × 2 (bonus)
  │     │
  │     └─→ setup_hooks()             # Register event handlers
  │           ├─→ mlx_hook(keypress)
  │           ├─→ mlx_hook(close)
  │           └─→ mlx_loop_hook(animation)
  │
  └─→ mlx_loop()                      # Enter main game loop
        └─→ [Event-driven execution begins]
```

### 2. Main Game Loop

```
mlx_loop() [External MiniLibX loop]
  │
  └─→ animation_loop() [Called every frame]
        │
        ├─→ frame_counter++
        │
        ├─→ update_enemies() (bonus)  # Check collisions (NO MOVEMENT)
        │     └─→ check_enemy_collision()
        │
        └─→ Every 25 frames:
              ├─→ Update current_frame (0-3)
              └─→ render_game()
                    ├─→ update_camera()      # Center camera on player
                    ├─→ mlx_clear_window()
                    ├─→ render_visible_tiles()
                    │     └─→ render_tile() for each visible tile
                    │           ├─→ Get sprite for tile
                    │           ├─→ Check if player position
                    │           ├─→ Check if enemy position (bonus)
                    │           └─→ mlx_put_image_to_window()
                    │
                    └─→ render_hud()
                          ├─→ Display moves count
                          ├─→ Display items collected
                          ├─→ render_win_screen() if won
                          └─→ render_lose_screen() if game over (bonus)
```

### 3. Input Handling Flow

```
User presses key
  │
  └─→ handle_keypress(keycode, game)
        │
        ├─→ If ESC: handle_close() → exit
        │
        └─→ If arrow/WASD:
              ├─→ Calculate new position
              │
              └─→ move_player(new_x, new_y)
                    │
                    ├─→ is_valid_move()
                    │     ├─→ Check bounds
                    │     └─→ Check not wall
                    │
                    ├─→ Update player position
                    │
                    ├─→ Increment move counter
                    │
                    ├─→ Print move count to terminal
                    │
                    ├─→ If collectible:
                    │     ├─→ Remove from map
                    │     ├─→ Increment collected count
                    │     └─→ Print collected count
                    │
                    ├─→ check_enemy_collision() (bonus)
                    │     └─→ Set game_over if touched
                    │
                    ├─→ check_win_condition()
                    │     └─→ If all collected and on exit: game_won = 1
                    │
                    └─→ render_game()
```

---

## Module Details

### main.c
**Purpose**: Entry point and argument validation

**Key Functions**:
- `main(int argc, char **argv)`
  - Validates arguments (requires exactly 1 map file)
  - Checks file extension (.ber)
  - Initializes game structure
  - Calls init_game()
  - Starts MLX loop
  - Handles errors

**Flow**:
```c
1. Check argc == 2
2. Check argv[1] ends with ".ber"
3. Create game structure
4. init_game(&game, argv[1])
5. mlx_loop(game.mlx)
6. Return 0
```

---

### map_parser.c
**Purpose**: Read and parse .ber map files

**Key Functions**:

1. **`count_lines(char *filename)`**
   - Opens file
   - Counts number of lines
   - Returns line count

2. **`parse_map(t_game *game, char *filename)`**
   - Allocates grid memory
   - Reads each line with get_next_line()
   - Stores in game->map.grid
   - Processes each character
   - Validates characters and positions

**Data Flow**:
```
File: maps/map.ber
  ↓
count_lines() → height
  ↓
Allocate char **grid[height]
  ↓
For each line:
  get_next_line() → line
  ↓
  Remove newline
  ↓
  Validate width consistency
  ↓
  For each char in line:
    process_map_char() → validate and count
  ↓
  Store in grid[y]
  ↓
Return success/failure
```

---

### map_validator.c
**Purpose**: Validate map structure and playability

**Key Functions**:

1. **`validate_map(t_map *map)`**
   - Checks map has required elements
   - Validates rectangular shape
   - Checks wall borders
   - Validates path with flood fill

2. **`is_valid_path(t_map *map)`**
   - Creates copy of map
   - Performs flood fill from player start
   - Checks if all collectibles and exit reachable

**Validation Rules**:
```
✓ Exactly 1 player (P)
✓ Exactly 1 exit (E)
✓ At least 1 collectible (C)
✓ Rectangular shape (all rows same width)
✓ Surrounded by walls (1)
✓ Valid path to all collectibles and exit
✓ Only valid characters: 0, 1, P, E, C, N (bonus)
```

**Flood Fill Algorithm**:
```c
void flood_fill(char **grid, t_point start, t_point size)
{
    // Mark current position as visited
    grid[start.y][start.x] = 'V';
    
    // Recursively visit neighbors (up, down, left, right)
    // Skip walls (1) and already visited (V)
    // Continue until all reachable tiles marked
}

// After flood fill:
// Check if all 'C' and 'E' were visited
```

---

### game_init.c
**Purpose**: Initialize all game components

**Key Functions**:

1. **`init_game_data(t_game *game)`**
   - Sets all pointers to NULL
   - Initializes counters to 0
   - Prepares clean state

2. **`init_game(t_game *game, char *map_file)`**
   - Coordinates all initialization
   - Error handling for each step
   - Cleanup on failure

**Initialization Sequence**:
```
1. init_game_data()      → Zero out all fields
2. parse_map()           → Load map from file
3. validate_map()        → Check map validity
4. mlx_init()            → Initialize graphics
5. create_window()       → Create display window
6. init_enemies()        → Setup static enemies (bonus)
7. load_sprites()        → Create all graphics
8. setup_hooks()         → Register event callbacks
```

---

### sprite_*.c Files
**Purpose**: Create visual sprites using MLX

**Sprite Creation Process**:
```c
void *create_sprite(void *mlx, int size)
{
    1. mlx_new_image(mlx, size, size)
    2. mlx_get_data_addr() → pixel buffer
    3. Loop through pixels:
       - Calculate color based on position
       - Set pixel: *(int *)(data + y * line + x * bpp/8) = color
    4. Return image pointer
}
```

**Available Sprites**:

1. **Ocean (empty tile)**: Blue gradient
2. **Coral (wall)**: Pink/red pattern
3. **Exit Gate**: Golden gate structure
4. **Dolphin (player)**: 4-frame animation
5. **Fish (collectible)**: 4-frame animation
6. **Enemy (bonus)**: 2-frame red ball

---

### game_render_norm.c
**Purpose**: Main rendering system

**Key Functions**:

1. **`update_camera(t_game *game)`**
   - Centers camera on player
   - Calculates visible area
   - Handles map edges

2. **`render_game(t_game *game)`**
   - Updates camera position
   - Clears window
   - Renders visible tiles
   - Renders HUD
   - Handles win/lose screens

**Camera System**:
```c
// Viewport size
VIEWPORT_WIDTH = 16 tiles
VIEWPORT_HEIGHT = 12 tiles

// Camera positioning
camera.x = player.x - (VIEWPORT_WIDTH / 2)
camera.y = player.y - (VIEWPORT_HEIGHT / 2)

// Clamp to map edges
if (camera.x < 0) camera.x = 0
if (camera.x + viewport_width > map.width)
    camera.x = map.width - viewport_width
```

**Rendering Order**:
```
1. Background tiles (ocean/walls)
2. Collectibles (fish)
3. Exit gate
4. Enemies (bonus)
5. Player (always on top)
6. HUD overlay (text)
```

---

### render_tile.c
**Purpose**: Render individual tiles

**Key Functions**:

1. **`get_tile_sprite(t_game *game, char tile)`**
   - Returns appropriate sprite for tile type
   - Handles animation frames

2. **`render_tile(t_game *game, int map_x, int map_y)`**
   - Converts map coordinates to screen coordinates
   - Selects correct sprite
   - Renders to window

**Tile Rendering Logic**:
```c
1. Check if player position → use player sprite
2. Check if enemy position (bonus) → use enemy sprite
3. Otherwise, check map tile:
   - '1' → wall sprite
   - 'C' → collectible sprite (animated)
   - 'E' → exit sprite
   - '0' → empty sprite (ocean)
4. Calculate screen position:
   screen_x = (map_x - camera.x) * TILE_SIZE
   screen_y = (map_y - camera.y) * TILE_SIZE
5. mlx_put_image_to_window(sprite, screen_x, screen_y)
```

---

### animation.c
**Purpose**: Handle animation timing

**Key Functions**:

1. **`animation_loop(t_game *game)`**
   - Called every frame by MLX
   - Updates animation frame counter
   - Triggers enemy updates (bonus)
   - Triggers rendering at intervals

**Animation Timing**:
```c
Frame rate: ~60 FPS (MLX default)
Animation update: Every 25 frames (~0.4 seconds)

frame_counter++;

// Update enemies (bonus - check collisions only)
if (!game_over && !game_won && enemy_count > 0)
    update_enemies(game);

// Update sprites every 25 frames
if (frame_counter % 25 == 0)
{
    current_frame = (current_frame + 1) % 4;  // Cycle 0→1→2→3→0
    render_game();
}
```

**Animation Cycle**:
```
Frame 0: Dolphin pose 1, Fish pose 1
Frame 25: Dolphin pose 2, Fish pose 2
Frame 50: Dolphin pose 3, Fish pose 3
Frame 75: Dolphin pose 4, Fish pose 4
Frame 100: Back to Frame 0
```

---

### game_input.c
**Purpose**: Handle keyboard input

**Key Functions**:

1. **`handle_keypress(int keycode, t_game *game)`**
   - Receives key events
   - Calculates new position
   - Calls move_player()

2. **`move_player(t_game *game, int new_x, int new_y)`**
   - Validates move
   - Updates position
   - Handles collectibles
   - Checks win/lose conditions

**Key Codes**:
```c
// macOS
KEY_ESC = 53
KEY_W = 13, KEY_A = 0, KEY_S = 1, KEY_D = 2
KEY_UP = 126, KEY_LEFT = 123, KEY_DOWN = 125, KEY_RIGHT = 124

// Linux
KEY_ESC = 65307
KEY_W = 119, KEY_A = 97, KEY_S = 115, KEY_D = 100
KEY_UP = 65362, KEY_LEFT = 65361, KEY_DOWN = 65364, KEY_RIGHT = 65363
```

**Movement Validation**:
```c
bool is_valid_move(game, new_x, new_y)
{
    // Check bounds
    if (new_x < 0 || new_x >= map.width) return false;
    if (new_y < 0 || new_y >= map.height) return false;
    
    // Check not wall
    if (map.grid[new_y][new_x] == '1') return false;
    
    return true;
}
```

---

### game_logic.c
**Purpose**: Core game state logic

**Key Functions**:

1. **`check_win_condition(t_game *game)`**
   - Checks if all collectibles gathered
   - Checks if player on exit
   - Sets game_won flag

**Win Condition**:
```c
void check_win_condition(t_game *game)
{
    // Must collect all items first
    if (game->map.collected < game->map.collectibles)
        return;
    
    // Must be on exit tile
    if (game->map.player.x == game->map.exit.x &&
        game->map.player.y == game->map.exit.y)
    {
        game->game_won = 1;
        ft_putstr(WIN_MSG);
    }
}
```

---

### cleanup.c
**Purpose**: Free all allocated memory

**Key Functions**:

1. **`cleanup_game(t_game *game)`**
   - Destroys sprites
   - Destroys window
   - Frees map grid
   - Frees enemies (bonus)

2. **`free_map(char **map)`**
   - Frees each row
   - Frees row array

**Cleanup Order**:
```
1. Destroy all sprite images (mlx_destroy_image)
2. Destroy window (mlx_destroy_window)
3. Free map grid (free each row, then array)
4. Free enemies array (bonus)
5. Exit program
```

---

## Data Structures

### t_game (Main Game Structure)
```c
typedef struct s_game
{
    void        *mlx;           // MLX connection
    void        *window;        // MLX window
    t_map       map;            // Map data
    t_sprites   sprites;        // All sprites
    t_camera    camera;         // Camera position
    t_enemy     *enemies;       // Enemy array (bonus)
    int         enemy_count;    // Number of enemies (bonus)
    int         moves;          // Move counter
    int         game_won;       // Win flag
    int         game_over;      // Lose flag (bonus)
    int         frame_counter;  // Animation timing
} t_game;
```

### t_map
```c
typedef struct s_map
{
    char        **grid;         // 2D map array
    int         width;          // Map width
    int         height;         // Map height
    int         collectibles;   // Total collectibles
    int         collected;      // Collected count
    t_position  player;         // Player position
    t_position  exit;           // Exit position
} t_map;
```

### t_sprites
```c
typedef struct s_sprites
{
    void    *wall;              // Wall sprite
    void    *empty;             // Empty tile sprite
    void    *collectible[4];    // Collectible animation
    void    *exit;              // Exit sprite
    void    *player[4];         // Player animation
    void    *enemy[2];          // Enemy animation (bonus)
    int     width;              // Sprite width (64)
    int     height;             // Sprite height (64)
    int     current_frame;      // Current animation frame (0-3)
    int     frame_count;        // Total frames (4)
} t_sprites;
```

### t_camera
```c
typedef struct s_camera
{
    int x;                      // Camera tile X
    int y;                      // Camera tile Y
    int offset_x;               // Pixel offset X (unused)
    int offset_y;               // Pixel offset Y (unused)
} t_camera;
```

### t_enemy (Bonus Only)
```c
typedef struct s_enemy
{
    t_position  pos;            // Current position
    int         direction;      // Movement direction (UNUSED - static)
    int         patrol_start;   // Patrol start (== pos)
    int         patrol_end;     // Patrol end (== pos)
    int         axis;           // Patrol axis (UNUSED - static)
} t_enemy;
```

---

## Game Loop

### Loop Structure
```
MLX Loop (60 FPS)
  ↓
animation_loop() [every frame]
  ↓
  ├─→ frame_counter++
  │
  ├─→ update_enemies() (bonus) [every frame]
  │     └─→ check_enemy_collision() only
  │
  └─→ if (frame_counter % 25 == 0) [~2.4 times/second]
        ├─→ Update animation frame (0→1→2→3→0)
        └─→ render_game()
              ├─→ update_camera()
              ├─→ mlx_clear_window()
              ├─→ render_visible_tiles()
              └─→ render_hud()
```

### Timing Diagram
```
Frame 0    : Start, render
Frame 1-24 : Wait (collision checks only)
Frame 25   : Update animation, render
Frame 26-49: Wait
Frame 50   : Update animation, render
...
```

---

## Rendering System

### Viewport System
```
Window: 1024x768 pixels
Tile Size: 64x64 pixels
Viewport: 16x12 tiles

┌─────────────────────────┐
│      Game Window        │
│  ┌─────────────────┐   │
│  │   Viewport      │   │
│  │   16x12 tiles   │   │
│  │                 │   │
│  └─────────────────┘   │
│      HUD (top)          │
└─────────────────────────┘
```

### Camera Centering
```
Player at (px, py)
Viewport size: (vw, vh) = (16, 12)

camera.x = px - vw/2 = px - 8
camera.y = py - vh/2 = py - 6

Clamp to map:
camera.x = max(0, min(camera.x, map.width - vw))
camera.y = max(0, min(camera.y, map.height - vh))
```

### Sprite Layering
```
Z-Index (bottom to top):
0. Background (ocean) - always visible
1. Walls (coral)
2. Collectibles (fish) - animated
3. Exit gate
4. Enemies (bonus) - static, animated
5. Player (dolphin) - animated
6. HUD overlay - text on top
```

---

## Input Handling

### Event Registration
```c
// Key press event
mlx_hook(window, 2, 1L << 0, handle_keypress, game);

// Window close event
mlx_hook(window, 17, 1L << 17, handle_close, game);

// Animation loop
mlx_loop_hook(mlx, animation_loop, game);
```

### Movement Processing
```
Key Press
  ↓
handle_keypress()
  ↓
Calculate new_x, new_y
  ↓
move_player(new_x, new_y)
  ↓
is_valid_move()?
  ├─ NO → Return (no movement)
  └─ YES ↓
Update player position
  ↓
moves++
  ↓
Print "Moves: X"
  ↓
Check if collectible at new position
  ├─ YES ↓
  │   Remove collectible from map
  │   collected++
  │   Print "Collected: X/Y"
  └─ NO ↓
check_enemy_collision() (bonus)
  ├─ Collision ↓
  │   game_over = 1
  │   Print "Game Over!"
  └─ No collision ↓
check_win_condition()
  ├─ All collected AND on exit ↓
  │   game_won = 1
  │   Print "Congratulations!"
  └─ Not won yet ↓
render_game()
```

---

## Map System

### Map File Format (.ber)
```
1111111111
1P00000001
10C0C00001
1000E00N01
1111111111
```

### Character Meanings
```
'1' = Wall (coral)
'0' = Empty space (ocean)
'P' = Player start position
'E' = Exit
'C' = Collectible
'N' = Enemy (bonus only)
```

### Map Validation Checklist
```
✓ Rectangular (all rows same width)
✓ Surrounded by walls
✓ Exactly 1 player (P)
✓ Exactly 1 exit (E)
✓ At least 1 collectible (C)
✓ Valid path to all C and E
✓ Only valid characters
✓ File ends with .ber
```

### Flood Fill Path Validation
```c
Algorithm:
1. Create copy of map
2. Start at player position
3. Mark current tile as 'V' (visited)
4. Recursively visit all adjacent non-wall tiles
5. After flood fill, check:
   - All 'C' were reached (marked as 'V')
   - 'E' was reached (marked as 'V')
6. If any unreachable: map invalid
```

---

## Animation System

### Frame Management
```c
typedef struct s_sprites
{
    // ...
    int current_frame;   // 0, 1, 2, or 3
    int frame_count;     // Always 4
} t_sprites;

// Update every 25 game frames
current_frame = (current_frame + 1) % frame_count;
```

### Animated Sprites
1. **Player (Dolphin)**: 4 frames
   - Swimming animation
   - Frame 0: Neutral
   - Frame 1: Tail up
   - Frame 2: Neutral
   - Frame 3: Tail down

2. **Collectible (Fish)**: 4 frames
   - Swimming animation
   - Varies slightly each frame

3. **Enemy (Bonus)**: 2 frames
   - Simple wobble effect
   - Frame selection: `current_frame % 2`

### Synchronization
All animations update together:
- Same frame counter
- Same update frequency
- All sprites cycle in sync

---

## Enemy System (Bonus)

### Enemy Behavior: STATIC
**IMPORTANT**: Enemies do NOT move!
```c
void update_enemies(t_game *game)
{
    // Enemies are STATIC - no movement
    // Only used for rendering at fixed positions
    (void)game;  // Function does nothing
}
```

### Enemy Initialization
```c
int init_enemies(t_game *game)
{
    1. Count 'N' in map → enemy_count
    2. Allocate enemy array
    3. For each 'N':
       - Store position (x, y)
       - Set patrol_start = pos
       - Set patrol_end = pos
       - Set direction = 0
       - Set axis = 0
    4. Enemies stay at these positions forever
}
```

### Collision Detection
```c
void check_enemy_collision(t_game *game)
{
    for (each enemy)
    {
        if (player.x == enemy.x && player.y == enemy.y)
        {
            game->game_over = 1;
            return;
        }
    }
}
```

### Enemy Properties
```
- Position: Fixed at initialization
- Color: Red
- Size: 64x64 pixels
- Animation: 2-frame wobble
- Behavior: Static obstacle
- Collision: Instant game over
```

---

## Memory Management

### Allocation Points
```c
1. Map grid:
   - char **grid = malloc(sizeof(char *) * height)
   - For each row: grid[i] = malloc(width + 1)

2. Enemy array (bonus):
   - t_enemy *enemies = malloc(sizeof(t_enemy) * count)

3. MLX images (sprites):
   - mlx_new_image() for each sprite
   - Managed by MLX library

4. Temporary buffers:
   - get_next_line() allocations
   - Map copy for flood fill
```

### Cleanup Sequence
```c
void cleanup_game(t_game *game)
{
    // 1. Destroy sprites
    for (each sprite)
        mlx_destroy_image(mlx, sprite);
    
    // 2. Destroy window
    mlx_destroy_window(mlx, window);
    
    // 3. Free map
    free_map(map.grid);
    
    // 4. Free enemies
    if (enemies)
        free(enemies);
}
```

### Error Handling
```
At each allocation:
1. Check if NULL
2. If NULL:
   - Print error
   - cleanup_game()
   - Return failure

On any init failure:
1. cleanup_game()
2. Return 0 (failure)
3. Main exits with error
```

---

## Performance Considerations

### Rendering Optimization
```
Only render visible tiles:
- Calculate viewport bounds
- Skip tiles outside viewport
- Reduces draw calls significantly

Example:
Map: 100x100 = 10,000 tiles
Viewport: 16x12 = 192 tiles
Rendered: ~200 tiles vs 10,000 tiles
= 50x performance improvement
```

### Memory Usage
```
Typical game:
- Map grid: ~10KB (100x100 map)
- Sprites: ~16MB (10 sprites × 64×64 × 4 bytes)
- Enemies: ~100 bytes (10 enemies)
- Total: ~16MB

MLX manages sprite memory internally
```

---

## Debugging Tips

### Common Issues

1. **Map not loading**:
   - Check file path
   - Check .ber extension
   - Verify file permissions

2. **Rendering issues**:
   - Verify sprite creation success
   - Check camera bounds
   - Confirm viewport size

3. **Input not working**:
   - Verify event hooks registered
   - Check key codes for OS
   - Confirm handle_keypress called

4. **Memory leaks**:
   - Use valgrind
   - Ensure cleanup_game() called
   - Check all mlx_destroy_image() calls

### Debug Output
```c
// Add debug prints:
printf("Player: (%d, %d)\n", game->map.player.x, game->map.player.y);
printf("Camera: (%d, %d)\n", game->camera.x, game->camera.y);
printf("Collected: %d/%d\n", game->map.collected, game->map.collectibles);
printf("Frame: %d\n", game->sprites.current_frame);
```

---

## Compilation

### Mandatory
```bash
make
# Produces: so_long
# No enemy features
```

### Bonus
```bash
make bonus
# Produces: so_long_bonus
# Includes static enemies
```

### Testing
```bash
# Mandatory
./so_long maps/map.ber

# Bonus
./so_long_bonus maps/map_bonus.ber
```

---

## Conclusion

The So_Long project demonstrates:
- **Graphics**: Sprite creation, rendering, animation
- **Game Logic**: State management, collision detection, win conditions
- **Input Handling**: Keyboard events, movement validation
- **Memory Management**: Proper allocation/deallocation
- **Algorithm**: Flood fill for path validation
- **Architecture**: Modular design with clear separation

The bonus version adds static enemies as obstacles while maintaining clean code separation between mandatory and bonus features.

---

## Quick Reference

### Important Macros
```c
WINDOW_WIDTH    = 1024
WINDOW_HEIGHT   = 768
TILE_SIZE       = 64
VIEWPORT_WIDTH  = 16
VIEWPORT_HEIGHT = 12
```

### Map Characters
```c
'1' = Wall
'0' = Empty
'P' = Player
'E' = Exit
'C' = Collectible
'N' = Enemy (bonus)
```

### Game States
```c
game_won   = 1  // Player collected all and reached exit
game_over  = 1  // Player touched enemy (bonus)
moves      > 0  // Number of movements made
```

### Key Functions
```c
main()              // Entry point
init_game()         // Initialize everything
animation_loop()    // Main game loop
render_game()       // Draw everything
handle_keypress()   // Process input
move_player()       // Update position
check_win_condition() // Check if won
cleanup_game()      // Free memory
```

---

*Last Updated: October 2025*
*Version: 1.0 (Bonus with Static Enemies)*
