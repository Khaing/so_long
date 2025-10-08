#!/bin/bash

echo "════════════════════════════════════════════════════════════"
echo "  42 SO_LONG EVALUATION VERIFICATION"
echo "════════════════════════════════════════════════════════════"
echo ""

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

PASS=0
FAIL=0

test_case() {
    local name="$1"
    local cmd="$2"
    local expected="$3"
    
    echo -n "Testing: $name... "
    output=$(eval "$cmd" 2>&1 | head -1)
    
    if echo "$output" | grep -q "$expected"; then
        echo -e "${GREEN}✅ PASS${NC}"
        PASS=$((PASS + 1))
    else
        echo -e "${RED}❌ FAIL${NC}"
        echo "  Expected: $expected"
        echo "  Got: $output"
        FAIL=$((FAIL + 1))
    fi
}

echo "1. PRELIMINARY CHECKS"
echo "────────────────────────────────────────────────────────────"

# Check Makefile exists
if [ -f "Makefile" ]; then
    echo -e "Makefile exists: ${GREEN}✅ PASS${NC}"
    PASS=$((PASS + 1))
else
    echo -e "Makefile exists: ${RED}❌ FAIL${NC}"
    FAIL=$((FAIL + 1))
fi

# Check compilation
make re > /dev/null 2>&1
if [ -f "so_long" ]; then
    echo -e "Compilation: ${GREEN}✅ PASS${NC}"
    PASS=$((PASS + 1))
else
    echo -e "Compilation: ${RED}❌ FAIL${NC}"
    FAIL=$((FAIL + 1))
fi

echo ""
echo "2. ERROR HANDLING TESTS"
echo "────────────────────────────────────────────────────────────"

test_case "No arguments" "./so_long" "Error"
test_case "Wrong extension" "./so_long test.txt" "Error"
test_case "Invalid map (no player)" "./so_long tests/maps/test_invalid_no_player.ber" "Error"
test_case "Invalid map (no exit)" "./so_long tests/maps/test_invalid_no_exit.ber" "Error"
test_case "Invalid map (no collectible)" "./so_long tests/maps/test_invalid_no_collectible.ber" "Error"

echo ""
echo "3. MAP VALIDATION TESTS"
echo "────────────────────────────────────────────────────────────"

test_case "Two players" "./so_long tests/maps/test_invalid_two_players.ber" "Error"
test_case "Unknown character" "./so_long tests/maps/test_invalid_unknown_char.ber" "Error"
test_case "Not rectangular" "./so_long tests/maps/test_invalid_not_rectangular.ber" "Error"

echo ""
echo "════════════════════════════════════════════════════════════"
echo "  EVALUATION SUMMARY"
echo "════════════════════════════════════════════════════════════"
echo -e "Tests Passed: ${GREEN}$PASS${NC}"
echo -e "Tests Failed: ${RED}$FAIL${NC}"
echo "Total Tests: $((PASS + FAIL))"

if [ $FAIL -eq 0 ]; then
    echo -e "\n${GREEN}✅ ALL TESTS PASSED - READY FOR EVALUATION${NC}"
    exit 0
else
    echo -e "\n${RED}❌ SOME TESTS FAILED - NEEDS FIXING${NC}"
    exit 1
fi

