#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counters
TOTAL=0
PASSED=0
FAILED=0

# Change to so_long directory
cd "$(dirname "$0")/.." || exit

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}     SO_LONG CUSTOM TEST SUITE${NC}"
echo -e "${BLUE}========================================${NC}\n"

# Test valid maps (should NOT print "Error")
echo -e "${YELLOW}Testing VALID maps (should succeed):${NC}\n"

test_valid_map() {
    local map=$1
    local name=$(basename "$map" .ber)
    TOTAL=$((TOTAL + 1))

    echo -n "Testing $name... "

    # Run for 1 second and kill (we just want to check if it loads)
    timeout 1s ./so_long "$map" 2>&1 | head -1 > /tmp/so_long_test_output.txt

    if grep -q "Error" /tmp/so_long_test_output.txt; then
        echo -e "${RED}FAILED${NC} (should be valid but got Error)"
        FAILED=$((FAILED + 1))
        cat /tmp/so_long_test_output.txt
    else
        echo -e "${GREEN}PASSED${NC}"
        PASSED=$((PASSED + 1))
    fi
}

for map in tests/maps/test_valid_*.ber; do
    [ -f "$map" ] && test_valid_map "$map"
done

echo ""

# Test invalid maps (should print "Error")
echo -e "${YELLOW}Testing INVALID maps (should fail with Error):${NC}\n"

test_invalid_map() {
    local map=$1
    local name=$(basename "$map" .ber)
    TOTAL=$((TOTAL + 1))

    echo -n "Testing $name... "

    output=$(./so_long "$map" 2>&1 | head -1)

    if echo "$output" | grep -q "Error"; then
        echo -e "${GREEN}PASSED${NC} (correctly rejected)"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}FAILED${NC} (should reject but didn't)"
        FAILED=$((FAILED + 1))
        echo "  Got: $output"
    fi
}

for map in tests/maps/test_invalid_*.ber; do
    [ -f "$map" ] && test_invalid_map "$map"
done

echo ""

# Test with existing maps directory
echo -e "${YELLOW}Testing with existing maps:${NC}\n"

if [ -d "maps" ]; then
    # Test a few known maps
    [ -f "maps/simple.ber" ] && test_valid_map "maps/simple.ber"
    [ -f "maps/medium.ber" ] && test_valid_map "maps/medium.ber"
    [ -f "maps/invalid.ber" ] && test_invalid_map "maps/invalid.ber"
fi

echo ""
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}           TEST SUMMARY${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "Total tests:  $TOTAL"
echo -e "${GREEN}Passed:       $PASSED${NC}"
echo -e "${RED}Failed:       $FAILED${NC}"
echo ""

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}✓ All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}✗ Some tests failed!${NC}"
    exit 1
fi
