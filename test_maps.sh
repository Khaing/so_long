#!/bin/bash

# Colors
GREEN='\033[1;92m'
RED='\033[1;91m'
YELLOW='\033[0;93m'
CYAN='\033[0;96m'
DEF='\033[0;39m'

echo -e "${CYAN}========================================${DEF}"
echo -e "${CYAN}  SO_LONG - Manual Test Script${DEF}"
echo -e "${CYAN}========================================${DEF}"
echo ""

# Test 1: Compilation
echo -e "${YELLOW}[1] Testing Compilation...${DEF}"
make re > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ Compilation successful${DEF}"
else
    echo -e "${RED}❌ Compilation failed${DEF}"
    exit 1
fi
echo ""

# Test 2: Error cases
echo -e "${YELLOW}[2] Testing Error Cases...${DEF}"
PASSED=0
FAILED=0

test_error_case() {
    local desc="$1"
    local cmd="$2"

    eval "$cmd" > /tmp/test_output.txt 2>&1

    if grep -q "^Error" /tmp/test_output.txt; then
        echo -e "${GREEN}✅${DEF} $desc"
        ((PASSED++))
    else
        echo -e "${RED}❌${DEF} $desc"
        ((FAILED++))
    fi
}

test_error_case "No arguments" "./so_long"
test_error_case "Bad extension (.txt)" "./so_long maps_err/badextension1.txt"
test_error_case "Nonexistent file" "./so_long nonexistent.ber"
test_error_case "Duplicate player" "./so_long maps_err/duplicate_player.ber"
test_error_case "Duplicate exit" "./so_long maps_err/duplicate_exit.ber"
test_error_case "No exit" "./so_long maps_err/no_exit.ber"
test_error_case "No player" "./so_long maps_err/no_player.ber"
test_error_case "No collectibles" "./so_long maps_err/no_object.ber"
test_error_case "Wrong characters" "./so_long maps_err/wrong_chars.ber"
test_error_case "Non-rectangular" "./so_long maps_err/no_rectangular.ber"
test_error_case "No walls" "./so_long maps_err/no_walls.ber"
test_error_case "No valid path" "./so_long maps_err/no_valid_road.ber"
test_error_case "Too small map" "./so_long maps/invalid_too_small.ber"
test_error_case "No path to collectible" "./so_long maps/invalid_no_path_to_collectible.ber"
test_error_case "No path to exit" "./so_long maps/invalid_no_path_to_exit.ber"

echo ""
echo -e "${CYAN}Error Tests: ${GREEN}$PASSED passed${DEF}, ${RED}$FAILED failed${DEF}"
echo ""

# Test 3: Valid maps info
echo -e "${YELLOW}[3] Valid Map Files Created:${DEF}"
echo -e "   ${GREEN}•${DEF} maps/tiny.ber - Smallest valid map (3x7)"
echo -e "   ${GREEN}•${DEF} maps/simple.ber - Simple test map"
echo -e "   ${GREEN}•${DEF} maps/medium.ber - Medium sized map (11x19)"
echo -e "   ${GREEN}•${DEF} maps/complex.ber - Complex layout"
echo -e "   ${GREEN}•${DEF} maps/large.ber - Large map with camera scrolling (27x50)"
echo -e "   ${GREEN}•${DEF} maps/challenge.ber - Challenging maze (23x21)"
echo ""

# Test 4: Manual testing instructions
echo -e "${YELLOW}[4] Manual Testing Required:${DEF}"
echo -e "   Run these commands to test gameplay:"
echo -e "   ${CYAN}./so_long maps/tiny.ber${DEF}"
echo -e "   ${CYAN}./so_long maps/medium.ber${DEF}"
echo -e "   ${CYAN}./so_long maps/large.ber${DEF} (tests camera system)"
echo -e "   ${CYAN}./so_long maps/challenge.ber${DEF} (tests pathfinding)"
echo ""
echo -e "   ${YELLOW}Verify:${DEF}"
echo -e "   • Window opens with animated sea theme"
echo -e "   • 🐬 Dolphin player moves with WASD/Arrow keys"
echo -e "   • 🐟 Fish collectibles disappear when collected"
echo -e "   • Move counter displays in terminal"
echo -e "   • HUD shows moves and collectibles on screen"
echo -e "   • Can't move through 🪸 coral walls"
echo -e "   • Can't exit 🌱 seaweed portal until all fish collected"
echo -e "   • ESC key exits cleanly"
echo -e "   • Window close button works"
echo ""

# Test 5: Summary
echo -e "${CYAN}========================================${DEF}"
if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}✨ All automated tests passed!${DEF}"
    echo -e "${YELLOW}⚠️  Don't forget manual gameplay testing${DEF}"
else
    echo -e "${RED}⚠️  Some tests failed. Check output above.${DEF}"
fi
echo -e "${CYAN}========================================${DEF}"

rm -f /tmp/test_output.txt
