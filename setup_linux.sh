#!/bin/bash

# so_long Linux Setup Script
# This script will set up the Linux environment for so_long

echo "========================================="
echo "so_long - Linux Setup Script"
echo "========================================="
echo ""

# Check if running on Linux
if [[ "$OSTYPE" != "linux-gnu"* ]]; then
    echo "⚠️  This script is for Linux only!"
    echo "   Detected OS: $OSTYPE"
    exit 1
fi

# Check for required commands
echo "✓ Checking for required tools..."
command -v gcc >/dev/null 2>&1 || { echo "❌ gcc is required but not installed. Install it with: sudo apt-get install gcc"; exit 1; }
command -v make >/dev/null 2>&1 || { echo "❌ make is required but not installed. Install it with: sudo apt-get install make"; exit 1; }
command -v git >/dev/null 2>&1 || { echo "❌ git is required but not installed. Install it with: sudo apt-get install git"; exit 1; }
echo "✓ All required tools found!"
echo ""

# Check for X11 libraries
echo "✓ Checking for X11 development libraries..."
if ! pkg-config --exists x11 2>/dev/null; then
    echo "⚠️  X11 libraries not found!"
    echo "   Install with: sudo apt-get install libx11-dev libxext-dev"
    read -p "   Do you want to continue anyway? (y/n) " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        exit 1
    fi
else
    echo "✓ X11 libraries found!"
fi
echo ""

# Clone MiniLibX if not present
if [ ! -d "minilibx-linux" ]; then
    echo "📦 Cloning MiniLibX for Linux..."
    git clone https://github.com/42Paris/minilibx-linux.git
    if [ $? -ne 0 ]; then
        echo "❌ Failed to clone MiniLibX!"
        exit 1
    fi
    echo "✓ MiniLibX cloned successfully!"
else
    echo "✓ MiniLibX directory already exists"
fi
echo ""

# Build MiniLibX
echo "🔨 Building MiniLibX..."
cd minilibx-linux
make
if [ $? -ne 0 ]; then
    echo "❌ Failed to build MiniLibX!"
    exit 1
fi
cd ..
echo "✓ MiniLibX built successfully!"
echo ""

# Build so_long
echo "🔨 Building so_long..."
make
if [ $? -ne 0 ]; then
    echo "❌ Failed to build so_long!"
    exit 1
fi
echo "✓ so_long built successfully!"
echo ""

# Success!
echo "========================================="
echo "✅ Setup complete!"
echo "========================================="
echo ""
echo "Run the game with:"
echo "  ./so_long maps/simple.ber"
echo ""
echo "Controls:"
echo "  WASD or Arrow keys - Move"
echo "  ESC - Exit"
echo ""
