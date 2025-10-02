# so_long - Quick Start Guide

## 🚀 Running the Game

### macOS:
```bash
make
./so_long maps/simple.ber
```

### Linux:
```bash
./setup_linux.sh
./so_long maps/simple.ber
```

---

## 🎮 Controls

| Key | Action |
|-----|--------|
| **W** or **↑** | Move up |
| **A** or **←** | Move left |
| **S** or **↓** | Move down |
| **D** or **→** | Move right |
| **ESC** or **Red X** | Exit game |

---

## 🎯 Objective

1. **Collect** all golden items (collectibles)
2. **Reach** the red exit
3. **Win** with minimum moves!

---

## 🎨 Colors

| Color | Element |
|-------|---------|
| 🟤 Brown | Walls |
| 🔵 Blue | Floor |
| 🟢 Green | Player |
| 🟡 Gold | Collectibles |
| 🔴 Red | Exit |

---

## 📁 Available Maps

```bash
./so_long maps/simple.ber      # Easy 5x13 map
./so_long maps/complex.ber     # Harder 6x34 map
```

---

## ✅ Features

- ✅ **42 Norm compliant** - All functions ≤ 25 lines, ≤ 5 variables
- ✅ **No forbidden functions** - Custom ft_putstr(), ft_putnbr(), ft_itoa()
- ✅ **Cross-platform** - Works on macOS and Linux
- ✅ **Animated sprites** - 4-frame animation
- ✅ **On-screen HUD** - Move counter and items collected
- ✅ **Camera system** - For large maps
- ✅ **Full error handling** - Validates maps and shows clear errors

---

## 🛠️ Build Commands

```bash
make           # Compile project
make clean     # Remove object files
make fclean    # Remove objects + executable
make re        # Clean rebuild
```

---

## ❌ Error Testing

```bash
./so_long                                    # Error: Usage message
./so_long nonexistent.ber                    # Error: File not found
./so_long maps/invalid.ber                   # Error: Invalid map
./so_long maps/invalid_no_collectibles.ber   # Error: No collectibles
./so_long maps/invalid_duplicate_p.ber       # Error: Duplicate player
```

---

## 📊 Move Counter

The game displays your moves in the terminal:
```
Moves: 1
Moves: 2
Collected: 1/1
Moves: 3
Congratulations! You won!
Total moves: 3
```

Try to win with the **fewest moves** possible!

---

## 🔍 Mandatory Requirements Checklist

✅ Game uses `.ber` map files
✅ Player moves with WASD/Arrows
✅ Cannot pass through walls
✅ Collect all items before exit
✅ Move count in shell
✅ ESC closes game
✅ Window X button works
✅ Map validation (walls, path, format)
✅ Error messages start with "Error\n"
✅ No memory leaks
✅ Clean compilation with `-Wall -Wextra -Werror`

---

## 💡 Tips

1. **Plan your route** before moving
2. **Minimize moves** for a better score
3. **Test error cases** to verify robustness
4. **Check norm compliance** with norminette (if available)

---

## 📚 Documentation

- **[42_NORM_COMPLIANCE.md](42_NORM_COMPLIANCE.md)** - Norm compliance details
- **[LINUX_SETUP.md](LINUX_SETUP.md)** - Linux setup guide
- **[README_PLATFORMS.md](README_PLATFORMS.md)** - Cross-platform guide
- **[CLAUDE.md](CLAUDE.md)** - Development notes

---

## 🎓 Evaluation Ready

Your project meets all requirements and is ready for defense!

**Good luck!** 🚀
