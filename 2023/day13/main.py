#!/usr/bin/python3
import sys

def check_vertical_mirror(pattern, axis):
    error = 1
    w = len(pattern[0])
    for line in pattern:
        x = axis
        i = axis + 1
        while x >= 0 and i < w:
            if line[x] != line[i]:
                if error > 0:
                    error -= 1
                else:
                    return False
            x -= 1
            i += 1

    return error == 0

def check_horizontal_mirror(pattern, axis):
    error = 1
    w = len(pattern[0])
    h = len(pattern)
    for x in range(w):
        y = axis
        j = axis + 1
        while y >= 0 and j < h:
            if pattern[y][x] != pattern[j][x]:
                if error > 0:
                    error -= 1
                else:
                    return False
            y -= 1
            j += 1

    return error == 0

def find_mirror(pattern):
    w = len(pattern[0])
    h = len(pattern)

    res = 0

    for i in range(w - 1):
        if check_vertical_mirror(pattern, i):
            res += i + 1

    for j in range(h - 1):
        if check_horizontal_mirror(pattern, j):
            res += 100 * (j + 1)

    return res

def read_mirror(file):
    res = 0
    pattern = []
    for line in file.readlines():
        if line[0] == '\n':
            res += find_mirror(pattern)
            pattern = []
        else:
            curr = []
            for c in line:
                if c != '\n':
                    curr.append(c)
            pattern.append(curr)

    return res;

def main(argc, argv):
    if argc < 2:
        return 1

    res = 0
    with open(argv[1], 'r') as file:
        res = read_mirror(file);

    print(f"res: {res}")

    return 0

if __name__ == "__main__":
    exit(main(len(sys.argv), sys.argv))
