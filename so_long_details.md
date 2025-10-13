Complete Explanation of the so_long Game

Part 1: Overview - Code Logic from Start to End

Program Start → Validate Input → Parse Map → Validate Map → Initialize Graphics → Game Loop → Exit

./so_long map.ber:

Step 1: Program Entry (main.c:29-48)

int main(int argc, char **argv)
Check arguments: Must have exactly 2 arguments (program name + map file)
Check file extension: Map file must end with .ber
Initialize game: Call init_game() to set everything up
Start game: If successful, render the game and start the event loop
Think of it like: Opening a board game box - you first check you have all the pieces (arguments), verify the rulebook (file extension), then set up the board (initialize), and finally start playing (game loop).

Step 2: Game Initialization (game_init.c:67-108)
This is the setup phase, executed in this specific order (order matters!):
int init_game(t_game *game, char *map_file)

2a. Initialize Data Structures
Set all pointers to NULL
Zero out counters (moves, game_won, etc.)
Clear sprite array slots

2b. Parse the Map (NO graphics yet!)
Read the .ber file
Convert it into a 2D array (grid)
Count collectibles, find player/exit positions

2c. Validate the Map (Still NO graphics!)
Check if rectangular
Check if surrounded by walls
Check if all items are reachable using flood-fill algorithm

2d. Initialize MLX (Graphics starts here)
Only AFTER validation passes
This prevents memory leaks when maps are invalid

2e. Create Window
Calculate window size based on map dimensions
Cap at maximum window size (1024x768)

2f. Load Sprites
Create colorful images for walls, floors, player, collectibles, exit
Store them in the game structure

2g. Setup Event Hooks
Register keyboard handler
Register window close handler
Register animation loop
Why this order? Imagine building a house:
Check if you have a valid blueprint (validate map) ✓
Buy materials (initialize graphics) ✓
Build the house (create window) ✓
Furnish it (load sprites) ✓
Install utilities (setup hooks) ✓
You wouldn't buy expensive materials before checking if the blueprint is valid!
Step 3: Map Parsing (map_parser.c)
int parse_map(t_game *game, char *filename)
What it does:
Opens the file
Counts lines to know grid height
Allocates memory for the grid
Reads each line into the grid array
Extracts information:
Map width and height
Player position (P)
Exit position (E)
Number of collectibles (C)
Example:
Input file:          What we store:
111111               grid[0] = "111111"
1P0C01               grid[1] = "1P0C01"  
1000E1               grid[2] = "1000E1"
111111               grid[3] = "111111"

Also extract:
- width = 6
- height = 4
- player = (1, 1)
- exit = (4, 2)
- collectibles = 1
Step 4: Map Validation (map_validator.c)
int validate_map(t_map *map)
Checks performed: 4a. Size Check
Map must be at least 3x3 (need room for walls + playable area)
4b. Wall Enclosure Check
✓ Valid:        ✗ Invalid:
1111111         1111111
1P0C01          1P0C0   ← Missing wall
1000E1          1000E1
1111111         1111111
4c. Path Validation (Most complex!)
Uses flood-fill algorithm to check if player can reach:
ALL collectibles
The exit
Step 5: Graphics Rendering (game_render_norm.c)
5a. Camera System
void update_camera(t_game *game)
If map is smaller than window: show entire map
If map is larger: center camera on player
Prevents camera from showing beyond map edges
Think of it like: A security camera following a person through a building 5b. Render Loop
void render_game(t_game *game)
Clear the window
Calculate visible tiles based on camera position
Draw each visible tile:
Walls
Empty spaces
Collectibles
Exit
Player
Draw HUD (Heads-Up Display):
Move counter
Items collected counter
If game is won: Draw congratulations message
5c. Win Screen
Draws an animated box in center of screen
Shows "CONGRATULATIONS!"
Shows total moves
Step 6: Input Handling (game_input.c)
int handle_keypress(int keycode, t_game *game)
Flow:
User presses a key
Check which key:
ESC → Exit game
W/↑ → Try move up
S/↓ → Try move down
A/← → Try move left
D/→ → Try move right
Calculate new position
Call move_player() with new position
Step 7: Game Logic (game_logic.c)
void move_player(t_game *game, int new_x, int new_y)
Decision tree:
Can move to new position?
├─ Is it a wall? → NO: Don't move
├─ Is it empty? → YES: Move, increment moves counter
├─ Is it collectible? → YES: Move, collect it, increment moves counter
└─ Is it exit?
   ├─ All items collected? → YES: Move, win game!
   └─ Items remaining? → NO: Don't move
void check_win_condition(t_game *game)
Checks if player is on exit AND all collectibles are collected
If yes: Set game->game_won = 1
Print victory message to console
Step 8: Animation Loop (animation.c)
int animation_loop(t_game *game)
This runs continuously (60 times per second):
Increment frame counter
Every 10 frames:
Switch to next animation frame for:
Player sprite (dolphin swimming animation)
Collectible sprite (fish wiggling)
Re-render the game
Effect: Creates smooth animations like in cartoons!
Step 9: Cleanup (cleanup.c)
void cleanup_game(t_game *game)
When game exits:
Destroy all sprite images
Destroy window
Free map grid memory
Like: Cleaning up after playing - put away all the pieces!
Part 2: Detailed Algorithm Explanations
Algorithm 1: Flood Fill (Path Validation)
Location: map_validator.c:48-103 Purpose: Determine if the player can reach all collectibles and the exit. Why not just check adjacent tiles?
Example where simple adjacency fails:
1111111
1P00001
1011101  ← Wall blocks path
10000C1  ← Collectible is adjacent but unreachable!
1111111
The Flood Fill Algorithm: Think of it like pouring water from the player's position - where does the water spread? Step-by-step:
int is_valid_path(t_map *map)
{
    // Step 1: Make a copy of the map (we'll modify it)
    char **grid_copy = copy_map(map);
    
    // Step 2: Start flood fill from player position
    flood_fill(grid_copy, player_x, player_y, width, height);
    
    // Step 3: Count what we reached
    // Step 4: Check if we reached everything
}
The Flood Fill Function: Uses a stack-based approach (iterative, not recursive to avoid stack overflow):
static void flood_fill(char **grid, int sx, int sy, int w, int h)
{
    t_point stack[10000];  // Stack to store positions to visit
    int top = 0;           // Stack pointer
    
    // Add starting position
    stack[top].x = sx;
    stack[top].y = sy;
    top++;
    
    while (top > 0)  // While there are positions to check
    {
        // Pop from stack
        cur = stack[--top];
        
        // Check if valid position
        if (out of bounds || wall || already visited)
            continue;
        
        // Mark as visited
        grid[cur.y][cur.x] = 'V';
        
        // Add all 4 neighbors to stack
        add_if_valid(stack, &top, {cur.x + 1, cur.y});  // Right
        add_if_valid(stack, &top, {cur.x - 1, cur.y});  // Left
        add_if_valid(stack, &top, {cur.x, cur.y + 1});  // Down
        add_if_valid(stack, &top, {cur.x, cur.y - 1});  // Up
    }
}
Visual Example:
Initial map:          After flood fill:
1111111               1111111
1P0C001               1VVCVV1  ← V = Visited
1011101               1V11101  ← Wall blocks
10000C1               1VVVVV1  ← This C is reachable!
1000E01               1VVVEV1  ← E is reachable!
1111111               1111111

Result: Player CAN reach the collectible and exit ✓
Bad map:              After flood fill:
1111111               1111111
1P0C001               1VVCVV1
1011101               1V11101  ← Wall blocks
10000C1               10000C1  ← This C NOT visited!
1111111               1111111

Result: Player CANNOT reach all collectibles ✗
Time Complexity: O(width × height) - visits each cell once Space Complexity: O(width × height) - for the copy and stack
Algorithm 2: Camera Tracking
Location: game_render_norm.c:122-149 Purpose: Keep the player centered on screen when the map is larger than the window. The Problem:
Window size: 1024x768 pixels
Tile size: 64x64 pixels
Visible tiles: 16×12 (1024÷64 × 768÷64)

But map might be 50×50 tiles!
The Solution: Scrolling Camera
void update_camera(t_game *game)
{
    int win_tiles_x = WINDOW_WIDTH / TILE_SIZE;   // 16
    int win_tiles_y = WINDOW_HEIGHT / TILE_SIZE;  // 12
    
    // X-axis camera
    if (map width <= window width)
        camera.x = 0;  // Show entire map
    else
    {
        // Try to center player
        camera.x = player.x - (win_tiles_x / 2);
        
        // Don't go past left edge
        if (camera.x < 0)
            camera.x = 0;
        
        // Don't go past right edge
        if (camera.x + win_tiles_x > map.width)
            camera.x = map.width - win_tiles_x;
    }
    
    // Same logic for Y-axis
}
Visual Example:
Map (20×20):                 Window (10×10):
┌────────────────────┐       ┌──────────┐
│xxxxxxxxxxxxxxxxxx  │       │xxxxxxx   │ ← Visible portion
│xxxxxxxxxxxxxxxxxx  │       │xxxxxxx   │
│xxxxxxxxxxxxxxxxxx  │       │xxxxxxx   │
│xxxxxxxxxxxxxxxxxx  │       │xxxxxxx P │ ← Player at edge
│xxxxxxxxxxxxxxxxx P │  →    │xxxxxxx   │
│xxxxxxxxxxxxxxxxxx  │       │xxxxxxx   │
│xxxxxxxxxxxxxxxxxxE │       │xxxxxxx   │
│xxxxxxxxxxxxxxxxxx  │       └──────────┘
│xxxxxxxxxxxxxxxxxx  │
└────────────────────┘

Camera follows player:
- camera.x = player.x - 5 (half window width)
- Renders tiles from camera.x to camera.x + 10
Algorithm 3: Win Screen Rendering
Location: game_render_norm.c:86-112 Purpose: Draw an animated congratulations message. The Challenge: Make it visible on ANY screen size. The Algorithm:
static void render_win_screen(t_game *game)
{
    // Step 1: Calculate center of screen
    cx = WINDOW_WIDTH / 2;   // Center X in pixels
    cy = WINDOW_HEIGHT / 2;  // Center Y in pixels
    
    // Step 2: Adjust for small maps
    // If map is smaller than window, center on visible map area
    if (cx > visible_map_width)
        cx = visible_map_width / 2;
    if (cy > visible_map_height)
        cy = visible_map_height / 2;
    
    // Step 3: Calculate pulse animation
    pulse = (frame_counter / 10) % 10;  // 0-9 cycle
    
    // Step 4: Draw animated box
    draw_win_box(game, cx, cy, pulse);
    
    // Step 5: Draw text at calculated positions
    mlx_string_put(..., cx - 120, cy - 40, "CONGRATULATIONS!");
    mlx_string_put(..., cx - 80, cy, "YOU WIN!");
    mlx_string_put(..., cx - 100, cy + 40, "Total Moves:");
    mlx_string_put(..., cx + 50, cy + 40, moves_number);
}
The Pulse Animation:
Frame 0:  Box size = 200×200 + 0  = 200×200
Frame 10: Box size = 200×200 + 1  = 201×201
Frame 20: Box size = 200×200 + 2  = 202×202
...
Frame 90: Box size = 200×200 + 9  = 209×209
Frame 100: Back to 200×200 (cycles)

Effect: Breathing/pulsing animation!
Algorithm 4: Memory Management Strategy
Location: game_init.c:67-108 The Critical Insight: Initialization order prevents memory leaks! ❌ OLD (Leaky) Approach:
init_game_data();
mlx = mlx_init();        // ← Allocates ~96KB
if (!parse_map())        // ← Map invalid!
{
    cleanup();           // ← But MLX can't be freed on macOS!
    return 0;            // ← 96KB leaked!
}
✅ NEW (Leak-Free) Approach:
init_game_data();
if (!parse_map())        // ← Check map FIRST (no allocations yet)
    return 0;            // ← Exit cleanly, nothing to free!

if (!validate_map())     // ← Validate BEFORE graphics
{
    free(map);           // ← Only free the map
    return 0;            // ← No MLX allocated yet!
}

mlx = mlx_init();        // ← ONLY allocate if map is valid!
Why This Works:
Failure Cases:

Case 1: Invalid file
├─ parse_map() fails
├─ No MLX allocated
└─ Only need to free map strings

Case 2: Invalid map structure  
├─ validate_map() fails
├─ No MLX allocated
└─ Only need to free map grid

Case 3: Graphics fail
├─ MLX allocated but map is VALID
├─ Worth keeping the resources
└─ This is rare (graphics usually works)
Memory Leak Test Results:
Before fix:  3 leaks for 98,448 bytes
After fix:   0 leaks for 0 bytes ✓
Algorithm 5: Animation Frame Management
Location: animation.c Purpose: Smooth sprite animations without consuming too much CPU.
int animation_loop(t_game *game)
{
    game->frame_counter++;
    
    // Update animation every 10 frames (10/60 = ~0.16 seconds)
    if (game->frame_counter % 10 == 0)
    {
        // Cycle through 4 animation frames
        game->sprites.current_frame++;
        if (game->sprites.current_frame >= 4)
            game->sprites.current_frame = 0;
    }
    
    render_game(game);
    return 0;
}
Frame Cycle:
Time:    0.0s  0.16s 0.32s 0.48s 0.64s
Frame:   [0]   [1]   [2]   [3]   [0]   ← Loops
Sprite:  🐬    🐬    🐬    🐬    🐬
         ↑     ↗    ↑     ↖    ↑    ← Appears to swim!
Why every 10 frames?
Game loop runs at ~60 FPS
60 FPS ÷ 10 = 6 animation updates/second
Smooth enough to look fluid
Not so fast it's jarring
Summary: Complete Data Flow
User runs: ./so_long map.ber
    ↓
main() validates arguments
    ↓
init_game() called
    ↓
Parse map.ber into grid[][] array
    ↓
Validate map with flood-fill
    ↓
Initialize MLX graphics (only if valid!)
    ↓
Create window sized to map
    ↓
Load sprite images
    ↓
Setup keyboard/close event handlers
    ↓
render_game() displays initial state
    ↓
mlx_loop() starts
    ↓
┌─────────────────────────────────┐
│ GAME LOOP (60 FPS)              │
│ ┌─────────────────────────────┐ │
│ │ 1. animation_loop()         │ │
│ │    - Update frame counter   │ │
│ │    - Switch sprite frames   │ │
│ │                             │ │
│ │ 2. User presses key?        │ │
│ │    - handle_keypress()      │ │
│ │    - move_player()          │ │
│ │    - check_win_condition()  │ │
│ │                             │ │
│ │ 3. render_game()            │ │
│ │    - update_camera()        │ │
│ │    - Draw visible tiles     │ │
│ │    - Draw HUD               │ │
│ │    - Draw win screen?       │ │
│ │                             │ │
│ │ 4. User closes window?      │ │
│ │    → handle_close()         │ │
│ │    → cleanup_game()         │ │
│ │    → EXIT                   │ │
│ └─────────────────────────────┘ │
│  ↑_____________________________│
└─────────────────────────────────┘
Key Takeaways
Order Matters: Validate input before allocating expensive resources
Algorithms: Flood-fill ensures game is winnable
Graphics: Camera system handles large maps elegantly
Memory: Clean initialization order prevents leaks
User Experience: Animations and smooth controls make it feel polished
This is a great example of a complete small game project that demonstrates:
File I/O
Data structures (2D arrays, stacks)
Algorithms (flood-fill, pathfinding)
Graphics programming
Event-driven programming
Memory management
Does this explanation help you understand the project better? Would you like me to dive deeper into any specific part?