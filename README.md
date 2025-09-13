# CS 3503 – Assignment 1: Number Base Conversion Utility

This project implements number base conversion using two algorithms and prints bit manipulation tables.

## Files
- `convert.c` – contains the three required functions:
  - `div_convert`: base conversion using division
  - `sub_convert`: base conversion using subtraction
  - `print_tables`: prints binary, octal, decimal, and hex representations, plus shift and mask
- `main.c` – test driver that parses `A1_tests.txt`, runs functions, and prints PASS/FAIL
- `A1_tests.txt` – provided test cases
- `output.txt` – saved program output (all tests run)

## Build Instructions
To compile (with GCC):

```bash
gcc -Wall -Wextra -O2 -o run main.c convert.c
