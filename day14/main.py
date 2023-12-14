#!/usr/bin/python3
import sys

def move_south(rocks, w, h, x, y):
    j = y
    while j + 1 < h and rocks[x + w * (j + 1)] == '.':
        rocks[x + w * (j + 1)] = rocks[x + w * j]
        rocks[x + w * j] = '.'
        j += 1

    return j

def move_north(rocks, w, h, x, y):
    j = y
    while j > 0 and rocks[x + w * (j - 1)] == '.':
        rocks[x + w * (j - 1)] = rocks[x + w * j]
        rocks[x + w * j] = '.'
        j -= 1

    return j

def move_west(rocks, w, h, x, y):
    i = x
    while i > 0 and rocks[i - 1 + w * y] == '.':
        rocks[i - 1 + w * y] = rocks[i + w * y]
        rocks[i + w * y] = '.'
        i -= 1

    return y

def move_east(rocks, w, h, x, y):
    i = x
    while i + 1 < w  and rocks[i + 1 + w * y] == '.':
        rocks[i + 1 + w * y] = rocks[i + w * y]
        rocks[i + w * y] = '.'
        i += 1

    return y

def tilt_north_west(rocks, w, h, move):
    res = 0

    for j in range(h):
        for i in range(w):
            if rocks[i + w * j] == 'O':
                res += h - move(rocks, w, h, i, j)

    return res

def tilt_south_east(rocks, w, h, move):
    res = 0

    for j in range(h):
        for i in range(w):
            if rocks[w - i - 1 + w * (h - j - 1)] == 'O':
                res += h - move(rocks, w, h, w - i - 1, h - j - 1)

    return res

def read_mirror(file):
    res = 0
    rocks = []
    w = 0
    h = 0
    for line in file.readlines():
        if line[0] == '\n':
            continue
        h += 1
        for c in line:
            if c == '\n':
                continue
            rocks.append(c)
            if h == 1:
                w += 1

    n = 1000000000
    memo = {}
    rocks_history = []
    x = 0
    k = 0
    for i in range(n):
        x = i
        k = i

        tilt_north_west(rocks, w, h, move_north)
        tilt_north_west(rocks, w, h, move_west)
        tilt_south_east(rocks, w, h, move_south)
        res = tilt_south_east(rocks, w, h, move_east)

        str_rocks = "".join(rocks)
        if str_rocks in memo:
            k = memo[str_rocks][0]
            break
        else:
            memo[str_rocks] = i, res
            rocks_history.append(str_rocks)

    if x != k:
        j = k + (n - k - 1) % (x - k)
    else:
        j = n - 1

    rocks = rocks_history[j]
    res = memo[rocks][1]

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
