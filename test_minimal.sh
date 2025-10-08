#!/bin/bash

echo "Test 1: No args"
./so_long > /tmp/test1.txt 2>&1
LINE=$(head -n 1 /tmp/test1.txt)
LINE2=$(sed -n '2p' /tmp/test1.txt)
echo "Line 1: $LINE"
echo "Line 2: $LINE2"

echo ""
echo "Test 2: Too many args"
./so_long invent.ber more argv > /tmp/test2.txt 2>&1
LINE=$(head -n 1 /tmp/test2.txt)
LINE2=$(sed -n '2p' /tmp/test2.txt)
echo "Line 1: $LINE"
echo "Line 2: $LINE2"

echo ""
echo "Test 3: Invalid map - no player"
./so_long maps_err/no_player.ber > /tmp/test3.txt 2>&1
LINE=$(head -n 1 /tmp/test3.txt)
LINE2=$(sed -n '2p' /tmp/test3.txt)
echo "Line 1: $LINE"
echo "Line 2: $LINE2"

echo ""
echo "Test 4: Valid map"
./so_long maps_valid/ok.ber &
PID=$!
sleep 0.5
if ps -p $PID > /dev/null 2>&1; then
    kill $PID
    echo "OK - window opened"
else
    echo "FAIL - process died"
fi

rm -f /tmp/test*.txt
