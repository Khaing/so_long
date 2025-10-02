# Linux Setup Guide for so_long

## Prerequisites

### Install Required Packages

#### Debian/Ubuntu:
```bash
sudo apt-get update
sudo apt-get install -y gcc make xorg libxext-dev libbsd-dev
```

#### Fedora/RHEL:
```bash
sudo dnf install -y gcc make xorg-x11-server-Xorg libXext-devel libbsd-devel
```

#### Arch Linux:
```bash
sudo pacman -S gcc make xorg-server libxext libbsd
```

---

## Installation Steps

### 1. Clone MiniLibX for Linux

```bash
cd /path/to/so_long
git clone https://github.com/42Paris/minilibx-linux.git
```

### 2. Build MiniLibX

```bash
cd minilibx-linux
make
cd ..
```

### 3. Build so_long

```bash
make
```

---

## Running the Game

```bash
./so_long maps/simple.ber
```

---

## Controls

- **W / ↑** → Move up
- **A / ←** → Move left
- **S / ↓** → Move down
- **D / →** → Move right
- **ESC** → Exit game

---

## Troubleshooting

### Error: "mlx.h: No such file or directory"
- Make sure `minilibx-linux` folder exists in the project root
- Run `make` inside the `minilibx-linux` directory first

### Error: "cannot find -lXext" or "cannot find -lX11"
Install X11 development libraries:
```bash
sudo apt-get install libxext-dev libx11-dev
```

### Error: "Permission denied" when running
Make the executable runnable:
```bash
chmod +x so_long
```

### Black screen or window doesn't open
- Check if X11 server is running
- Try running: `echo $DISPLAY` (should show `:0` or similar)
- If in WSL, you need an X server like VcXsrv or X410

---

## Differences from macOS Version

1. **Key codes**: Linux uses X11 key codes instead of macOS key codes
2. **MiniLibX**: Uses X11-based MiniLibX instead of OpenGL version
3. **Linking**: Links against X11 libraries (-lX11 -lXext) instead of macOS frameworks

---

## Build System

The Makefile automatically detects your OS:
- **macOS**: Uses `minilibx_opengl_20191021` with AppKit/OpenGL frameworks
- **Linux**: Uses `minilibx-linux` with X11 libraries

---

## WSL (Windows Subsystem for Linux)

If using WSL, you need an X server:

1. Install VcXsrv or X410 on Windows
2. Start the X server
3. Set display:
   ```bash
   export DISPLAY=:0
   ```
4. Run the game:
   ```bash
   ./so_long maps/simple.ber
   ```

---

## Testing

Test with different maps:
```bash
./so_long maps/simple.ber      # Small map
./so_long maps/complex.ber     # Larger map
```

Test error handling:
```bash
./so_long maps/invalid.ber     # Should show error
./so_long                       # Should show usage
./so_long nonexistent.ber       # Should show error
```
