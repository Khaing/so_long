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
echo -e "${BLUE}     SO_LONG VALIDATION TEST SUITE${NC}"
echo -e "${BLUE}========================================${NC}\n"

# Test invalid maps (should print "Error")
echo -e "${YELLOW}Testing INVALID maps (should fail with Error):${NC}\n"

test_invalid_map() {
    local map=$1
    local name=$(basename "$map" .ber)
    TOTAL=$((TOTAL + 1))

    echo -n "Testing $name... "

    # Just check if "Error" appears in first line of output
    output=$(./so_long "$map" 2>&1 | head -1)

    if echo "$output" | grep -q "Error"; then
        echo -e "${GREEN}PASSED${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}FAILED${NC} (should reject but didn't)"
        FAILED=$((FAILED + 1))
        echo "  Expected: Error"
        echo "  Got: $output"
    fi
}

# Test each invalid map
for map in tests/maps/test_invalid_*.ber; do
    [ -f "$map" ] && test_invalid_map "$map"
done

# Also test existing invalid maps
echo ""
for map in maps/invalid*.ber; do
    [ -f "$map" ] && test_invalid_map "$map"
done

echo ""
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}           TEST SUMMARY${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "Total tests:  $TOTAL"
echo -e "${GREEN}Passed:       $PASSED${NC}"
echo -e "${RED}Failed:       $FAILED${NC}"
echo ""

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}✓ All validation tests passed!${NC}"
    exit 0
else
    echo -e "${RED}✗ Some tests failed!${NC}"
    exit 1
fi
