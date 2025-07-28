# Sea-Themed Textures for so_long

This folder contains texture information for the underwater adventure game.

## Sprite Descriptions

### 🐬 Dolphin Player (Animated)
- **Color Palette**: Ocean blues (#4A90E2, #5DADE2, #87CEEB)
- **Animation**: 4-frame swimming motion with tail movement
- **Features**: Black eye, white highlight, dynamic fins
- **Movement**: Smooth vertical bobbing with tail wave effect

### 🐟 Fish Collectibles (Animated)
- **Color Palette**: Golden yellows (#FFD700, #FFE135, #FFA500)
- **Animation**: 4-frame swimming with shimmering body effect
- **Features**: Moving fins, animated tail, white eye highlight
- **Effect**: Body shine travels across the fish each frame

### 🪸 Coral Walls
- **Color Palette**: Coral pinks and reds (#FF69B4, #FF1493, #FF6347, #DC143C)
- **Features**: Pink coral polyps, textured surface, organic patterns
- **Details**: Central pink coral with surrounding reef structure

### 🌊 Ocean Background
- **Color Palette**: Deep ocean blues (#006994, #4A90E2, #87CEEB)
- **Features**: Flowing water patterns, subtle bubbles, depth variation
- **Animation**: Static background with dynamic water texture

### 🌱 Seaweed Exit Portal
- **Color Palette**: Sea greens (#228B22, #32CD32, #00FF7F, #90EE90)
- **Features**: Kelp forest entrance, swaying seaweed, glowing center
- **Design**: Vertical kelp strands with luminous portal center

## Technical Details

- **Resolution**: 64x64 pixels per tile
- **Format**: Programmatically generated RGB sprites
- **Animation**: 30 FPS frame updates
- **Color Depth**: 24-bit RGB values

## Animation System

The sprites use frame-based animation with:
- **Dolphin**: Vertical swimming motion + tail wave
- **Fish**: Horizontal swimming + body shimmer + fin movement
- **Background**: Static with water pattern details
- **Walls**: Static coral formations
- **Exit**: Static seaweed portal

All sprites are created programmatically in real-time for optimal memory usage and consistent visual quality.