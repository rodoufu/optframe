#!/usr/bin/env python3

import sys
import random

if __name__ == '__main__':
    size = int(sys.argv[1])
    min_val, max_val = 1, 2_147_483_647
    if len(sys.argv) > 2:
        min_val = int(sys.argv[2])
    if len(sys.argv) > 3:
        max_val = int(sys.argv[3])
    max_val = max(max_val, size)
    if len(sys.argv) > 4:
        random.seed(int(sys.argv[4]))

    print(size)
    for _ in range(size):
        print(str(random.randint(min_val, max_val)) + " ", end='')

    print("")
