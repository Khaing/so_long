# so_long - Cross-Platform Guide

This document explains the differences between running so_long on macOS and Linux.

---

## Quick Start

### macOS
```bash
make
./so_long maps/simple.ber
```

### Linux
```bash
./setup_linux.sh    # First time only
./so_long maps/simple.ber
```

---

## Platform-Specific Details

### macOS

**MiniLibX Version**: OpenGL-based (minilibx_opengl_20191021)

**Dependencies**:
- Built-in (no installation needed)

**Key Codes**:
- ESC: 53
- WASD: 13, 0, 1, 2
- Arrows: 126, 123, 125, 124

**Frameworks**:
- OpenGL
- AppKit

---

### Linux

**MiniLibX Version**: X11-based (minilibx-linux)

**Dependencies**:
```bash
# Debian/Ubuntu
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

# Fedora
sudo dnf install gcc make xorg-x11-server-Xorg libXext-devel libbsd-devel

# Arch
sudo pacman -S gcc make xorg-server libxext libbsd
```

**Key Codes**:
- ESC: 65307
- WASD: 119, 97, 115, 100
- Arrows: 65362, 65361, 65364, 65363

**Libraries**:
- X11
- Xext

---

## Project Structure

```
so_long/
├── minilibx_opengl_20191021/    # macOS MiniLibX (already included)
├── minilibx-linux/               # Linux MiniLibX (run setup_linux.sh)
├── src/                          # Source files
├── includes/                     # Headers
├── maps/                         # Map files (.ber)
├── Makefile                      # Auto-detects OS
├── setup_linux.sh               # Linux setup script
├── LINUX_SETUP.md               # Linux detailed guide
└── README_PLATFORMS.md          # This file
```

---

## Automatic OS Detection

The Makefile automatically detects your operating system:

```makefile
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    # Use Linux MiniLibX and X11
else ifeq ($(UNAME_S), Darwin)
    # Use macOS MiniLibX and frameworks
endif
```

The header file ([so_long.h](includes/so_long.h)) uses preprocessor directives:

```c
#ifdef __APPLE__
  // macOS code
#else
  // Linux code
#endif
```

---

## Key Code Differences

| Key    | macOS | Linux  |
|--------|-------|--------|
| ESC    | 53    | 65307  |
| W      | 13    | 119    |
| A      | 0     | 97     |
| S      | 1     | 115    |
| D      | 2     | 100    |
| Up     | 126   | 65362  |
| Left   | 123   | 65361  |
| Down   | 125   | 65364  |
| Right  | 124   | 65363  |

---

## WSL (Windows Subsystem for Linux)

To run on WSL:

1. **Install X Server on Windows**:
   - VcXsrv: https://sourceforge.net/projects/vcxsrv/
   - X410 (Paid): Microsoft Store

2. **Configure WSL**:
   ```bash
   export DISPLAY=:0
   echo "export DISPLAY=:0" >> ~/.bashrc
   ```

3. **Start X Server** on Windows (VcXsrv with "Disable access control")

4. **Run setup and game**:
   ```bash
   ./setup_linux.sh
   ./so_long maps/simple.ber
   ```

---

## Troubleshooting

### Linux: "cannot find -lX11"
```bash
sudo apt-get install libx11-dev libxext-dev
```

### Linux: "mlx.h: No such file or directory"
```bash
./setup_linux.sh
```

### WSL: Window doesn't appear
- Ensure X server is running on Windows
- Check `echo $DISPLAY` shows `:0`
- Try `export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0`

### macOS: "ld: framework not found OpenGL"
- This shouldn't happen on macOS with Xcode Command Line Tools
- Install with: `xcode-select --install`

---

## Building from Scratch

### macOS
```bash
make fclean    # Clean everything
make           # Rebuild
```

### Linux
```bash
make fclean                # Clean everything
cd minilibx-linux && make  # Rebuild MiniLibX
cd ..
make                       # Rebuild so_long
```

---

## Testing

Both platforms use the same maps and should behave identically:

```bash
# Valid maps
./so_long maps/simple.ber
./so_long maps/complex.ber

# Invalid maps (should show errors)
./so_long maps/invalid.ber
./so_long maps/invalid_no_collectibles.ber
./so_long maps/invalid_duplicate_p.ber
```

---

## Performance Notes

- **macOS**: Uses hardware-accelerated OpenGL
- **Linux**: Uses X11 (may be slower on some systems)
- Both versions support animated sprites and smooth rendering

---

## Contributing

When contributing, test on both platforms:
1. Test on macOS
2. Test on Linux (VM or dual-boot)
3. Ensure Makefile works on both
4. Verify key codes work correctly
