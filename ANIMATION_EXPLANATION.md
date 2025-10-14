# So_Long Animation System Explanation

## Table of Contents
1. [What is Sprite Animation?](#what-is-sprite-animation)
2. [How I Implemented It](#how-i-implemented-it)
3. [Animation Files Overview](#animation-files-overview)
4. [Detailed Code Walkthrough](#detailed-code-walkthrough)
5. [Frame Management](#frame-management)
6. [Performance Considerations](#performance-considerations)

---

## What is Sprite Animation?

**Sprite animation** is a technique where multiple static images (called frames) are displayed in rapid succession to create the illusion of movement. It's similar to how flip books work - each page shows a slightly different image, and when you flip through them quickly, it appears as smooth motion.

### Key Concepts:
- **Sprite**: A single 2D image representing an object (like a character or collectible)
- **Frame**: One image in an animation sequence
- **Frame Rate**: How quickly frames change (measured in frames per second)
- **Animation Cycle**: A complete sequence of frames that loops

### Example:
For a swimming dolphin animation with 4 frames:
```
Frame 0: Dolphin with tail centered
Frame 1: Dolphin with tail up
Frame 2: Dolphin with tail centered
Frame 3: Dolphin with tail down
[Loop back to Frame 0]
```

---

## How I Implemented It

### 1. **Multi-Frame Sprite Creation**

Instead of creating one static image per object, I create **multiple variations** of each animated object:

- **Player (Dolphin)**: 4 frames of swimming animation
- **Collectible (Fish)**: 4 frames of swimming animation
- **Enemy (Bonus)**: 2 frames of wobbling animation

### 2. **Frame Storage**

I use **arrays** to store multiple sprite images:

```c
typedef struct s_sprites
{
    void    *player[4];         // 4 frames for player animation
    void    *collectible[4];    // 4 frames for collectible animation
    void    *enemy[2];          // 2 frames for enemy animation (bonus)
    int     current_frame;      // Which frame to display (0-3)
    int     frame_count;        // Total frames (4)
}   t_sprites;
```

### 3. **Frame Timing**

I use the **MiniLibX loop hook** which runs continuously (approximately 60 times per second). Instead of updating animation every loop iteration, I use a **frame counter** to control timing:

```c
if (frame_counter % 25 == 0)  // Update every 25 iterations
{
    current_frame = (current_frame + 1) % 4;  // Cycle through 0,1,2,3,0,1...
    render_game();  // Redraw with new frame
}
```

**Result**: Animation updates approximately every 0.4 seconds (25 frames ÷ 60 fps ≈ 0.4s)

### 4. **Frame Selection During Rendering**

When drawing the game, I select the appropriate frame based on `current_frame`:

```c
if (is_player_position)
    sprite = game->sprites.player[game->sprites.current_frame];
else if (is_collectible)
    sprite = game->sprites.collectible[game->sprites.current_frame];
```

---

## Animation Files Overview

### Core Animation Files:

| File | Purpose | Key Functions |
|------|---------|---------------|
| **animation.c / animation_bonus.c** | Main animation loop controller | `animation_loop()` - Controls timing and frame updates |
| **anim_dolphin.c** | Creates 4 dolphin animation frames | `create_dolphin_anim()` - Generates each frame programmatically |
| **anim_fish.c** | Creates 4 fish animation frames | `create_fish_anim()` - Generates each frame programmatically |
| **sprite_enemy_bonus.c** | Creates 2 enemy animation frames | `create_enemy_sprite()` - Generates wobbling effect |
| **render_tile.c / render_tile_bonus.c** | Renders current frame | `render_tile()` - Displays appropriate frame |

---

## Detailed Code Walkthrough

### File: `animation.c` / `animation_bonus.c`

**Purpose**: Controls the animation timing and frame cycling

```c
int animation_loop(t_game *game)
{
    // Increment frame counter every loop iteration (~60 times/second)
    game->frame_counter++;

    // Only update animation every 25 frames
    if (game->frame_counter % 25 == 0)
    {
        // Cycle to next frame (0→1→2→3→0)
        game->sprites.current_frame = (game->sprites.current_frame + 1)
                                      % game->sprites.frame_count;

        // Redraw game with new frame
        render_game(game);
    }

    return (0);
}
```

**Why modulo (%) operation?**
- `current_frame % frame_count` ensures the value cycles: 0, 1, 2, 3, 0, 1, 2, 3...
- Example: (4 % 4) = 0, (5 % 4) = 1, (6 % 4) = 2, (7 % 4) = 3, (8 % 4) = 0

**Bonus Version Additions:**
```c
// Stop animation when game ends
if (game->frame_counter % 25 == 0 && !game->game_won && !game->game_over)
{
    // ... update animation ...
}

// Render final screen once
if ((game->game_won || game->game_over) && !end_screen_rendered)
{
    render_game(game);
    end_screen_rendered = 1;
}
```

---

### File: `anim_dolphin.c`

**Purpose**: Creates 4 different dolphin poses programmatically

```c
void *create_dolphin_anim(void *mlx, int size, int frame)
{
    void    *img;
    char    *data;
    int     bpp, line_len, endian;

    // Create empty image
    img = mlx_new_image(mlx, size, size);
    data = mlx_get_data_addr(img, &bpp, &line_len, &endian);

    // Draw dolphin body (same for all frames)
    draw_dolphin_body(data, size, ...);

    // Draw tail at different positions based on frame number
    if (frame == 0)
        draw_tail_center(data, ...);
    else if (frame == 1)
        draw_tail_up(data, ...);      // Tail moves up
    else if (frame == 2)
        draw_tail_center(data, ...);
    else if (frame == 3)
        draw_tail_down(data, ...);    // Tail moves down

    return (img);
}
```

**How it creates animation:**
1. **Frame 0**: Dolphin with tail in neutral position
2. **Frame 1**: Dolphin with tail moved upward → creates swimming motion
3. **Frame 2**: Dolphin with tail back to neutral
4. **Frame 3**: Dolphin with tail moved downward → completes swimming cycle

**Each frame is a unique image** created by drawing pixels at slightly different positions.

---

### File: `anim_fish.c`

**Purpose**: Creates 4 different fish poses for collectibles

```c
void *create_fish_anim(void *mlx, int size, int frame)
{
    // Similar to dolphin animation
    // Each frame shows fish in slightly different swimming pose

    // Body wobbles slightly side-to-side
    // Fins move to simulate swimming
    // Tail position changes

    return (img);
}
```

**Animation style:**
- Subtle body wobble
- Fin movements
- Creates gentle swimming motion

---

### File: `sprite_enemy_bonus.c` (Bonus Only)

**Purpose**: Creates 2 frames for enemy wobble effect

```c
void *create_enemy_sprite(void *mlx, int size, int frame)
{
    // Frame 0: Enemy ball slightly larger
    // Frame 1: Enemy ball slightly smaller

    // Creates pulsing/wobbling effect
    int radius = (frame == 0) ? 28 : 26;
    draw_circle(data, center_x, center_y, radius, 0xFF0000);

    return (img);
}
```

**Simple 2-frame animation:**
- Frame alternates between slightly larger and smaller
- Creates menacing pulsing effect

---

### File: `render_tile.c` / `render_tile_bonus.c`

**Purpose**: Displays the current animation frame

```c
void render_tile(t_game *game, int map_x, int map_y)
{
    void *sprite;

    // Select which sprite and frame to display
    if (map_x == player_x && map_y == player_y)
        sprite = game->sprites.player[game->sprites.current_frame];
    else if (is_collectible)
        sprite = game->sprites.collectible[game->sprites.current_frame];
    else if (is_enemy)  // Bonus only
        sprite = game->sprites.enemy[game->sprites.current_frame % 2];

    // Display the selected frame
    mlx_put_image_to_window(mlx, window, sprite, screen_x, screen_y);
}
```

**How it works:**
1. Determines what object is at map position (x, y)
2. Selects appropriate sprite array (player, collectible, enemy)
3. Uses `current_frame` as index to get the right frame
4. Displays that specific frame on screen

**Enemy frame selection:**
- Uses `current_frame % 2` because enemy only has 2 frames
- When `current_frame = 0, 2, 4, 6...` → displays frame 0
- When `current_frame = 1, 3, 5, 7...` → displays frame 1

---

## Frame Management

### Initialization (sprite_loader.c)

```c
int load_sprites(t_game *game)
{
    // Create all 4 dolphin frames
    game->sprites.player[0] = create_dolphin_anim(mlx, TILE_SIZE, 0);
    game->sprites.player[1] = create_dolphin_anim(mlx, TILE_SIZE, 1);
    game->sprites.player[2] = create_dolphin_anim(mlx, TILE_SIZE, 2);
    game->sprites.player[3] = create_dolphin_anim(mlx, TILE_SIZE, 3);

    // Create all 4 fish frames
    game->sprites.collectible[0] = create_fish_anim(mlx, TILE_SIZE, 0);
    game->sprites.collectible[1] = create_fish_anim(mlx, TILE_SIZE, 1);
    game->sprites.collectible[2] = create_fish_anim(mlx, TILE_SIZE, 2);
    game->sprites.collectible[3] = create_fish_anim(mlx, TILE_SIZE, 3);

    // Initialize frame tracking
    game->sprites.current_frame = 0;
    game->sprites.frame_count = 4;

    return (1);
}
```

### Frame Synchronization

**All animated sprites share the same `current_frame` counter**, which means:
- Player and collectibles animate in sync
- All fish on screen move together
- Simpler code and consistent timing

### Memory Management

```c
void destroy_sprites(t_game *game)
{
    // Destroy all 4 player frames
    for (int i = 0; i < 4; i++)
    {
        mlx_destroy_image(mlx, game->sprites.player[i]);
        mlx_destroy_image(mlx, game->sprites.collectible[i]);
    }

    // Destroy 2 enemy frames (bonus)
    for (int i = 0; i < 2; i++)
        mlx_destroy_image(mlx, game->sprites.enemy[i]);
}
```

---

## Performance Considerations

### Why Update Every 25 Frames?

```
MLX loop runs at: ~60 FPS
Update every 25 frames: 60 / 25 = 2.4 updates/second
Animation cycle time: 4 frames × 0.4s = 1.6 seconds per complete cycle
```

**Benefits:**
- Smooth, visible animation (not too fast, not too slow)
- Reduces CPU usage (not rendering every frame)
- Gives retro game feel

### Memory Usage

```
Per animated sprite:
- 4 frames × 64×64 pixels × 4 bytes/pixel = 65,536 bytes = 64 KB

Total for mandatory version:
- Player: 4 frames = 64 KB
- Collectibles: 4 frames = 64 KB (shared by all collectibles)
Total: ~128 KB for animations

Bonus version adds:
- Enemy: 2 frames = 32 KB
Total: ~160 KB for animations
```

**Optimization:** All collectibles share the same 4 frames (not creating separate frames per collectible).

---

## Animation Flow Diagram

```
┌─────────────────────────────────────────────────────────┐
│                    MLX MAIN LOOP                        │
│              (Runs continuously at ~60 FPS)             │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
        ┌────────────────────────────┐
        │   animation_loop() called  │
        │   frame_counter++          │
        └────────────┬───────────────┘
                     │
                     ▼
        ┌────────────────────────────┐
        │ Is frame_counter % 25 == 0?│
        └────────────┬───────────────┘
                     │
          ┌──────────┴──────────┐
          │                     │
          ▼ YES                 ▼ NO
   ┌──────────────┐      ┌────────────┐
   │ Update frame │      │ Do nothing │
   │ current_frame│      │ (skip this │
   │ = (frame+1)%4│      │  iteration)│
   └──────┬───────┘      └────────────┘
          │
          ▼
   ┌──────────────┐
   │ render_game()│
   └──────┬───────┘
          │
          ▼
   ┌─────────────────────┐
   │  render_tile()      │
   │  for each tile      │
   └──────┬──────────────┘
          │
          ▼
   ┌───────────────────────────────┐
   │ Select sprite frame:          │
   │ sprite = sprites[current_frame│
   └──────┬────────────────────────┘
          │
          ▼
   ┌──────────────────────────────┐
   │ mlx_put_image_to_window()    │
   │ Display frame on screen      │
   └──────────────────────────────┘
```

---

## Summary

### What I Implemented:

1. **Frame-based Animation System**
   - Created multiple sprite images for each animated object
   - Stored frames in arrays for efficient access

2. **Timing Control**
   - Used frame counter to control animation speed
   - Updates every 25 frames for smooth, visible motion

3. **Synchronized Animation**
   - All animated sprites share same frame counter
   - Ensures consistent, synchronized movement

4. **Memory Efficient**
   - Reuses same frames for all collectibles on map
   - Properly frees all frames on cleanup

5. **Programmatic Sprite Generation**
   - Created all sprites using pixel manipulation
   - No external image files needed
   - Each frame drawn by calculating pixel positions

### Technical Achievement:

- ✅ Multiple frames per sprite (4 for player/fish, 2 for enemy)
- ✅ Smooth animation timing (~2.4 FPS animation speed)
- ✅ Efficient memory management (shared frames)
- ✅ Clean code structure (separate files per animation type)
- ✅ Proper cleanup (all frames destroyed on exit)

This animation system brings the game to life while maintaining clean, efficient code!
