#!/bin/bash
# Build the program, feed it the test commands, and compare with what we expect.

gcc -Wall -o device device.c || { echo "BUILD FAILED"; exit 1; }

./device < commands.txt > actual.txt

if diff expected.txt actual.txt > /dev/null; then
    echo "PASS: output matches expected"
else
    echo "FAIL: output differs"
    diff expected.txt actual.txt
    exit 1
fi