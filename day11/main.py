#!/usr/bin/python3
import sys

def expand_universe(raw, cols, rows, factor):
    n = 1
    galaxies = []
    w = len(raw[0])
    h = len(raw)
    y = 0
    for j in range(h):
        if j in rows:
            y += factor
            continue
        x = 0
        for i in range(w):
            if i in cols:
                x += factor
                continue
            if raw[j][i] == '#':
                galaxies.append((x, y))
            x += 1
        y += 1

    return galaxies

def distance(galaxies, start, end):
    x, y = galaxies[start]
    end_x, end_y = galaxies[end]
    return abs(end_x - x) + end_y - y

def read_universe(file):
    raw_universe = []
    empty_col = []
    empty_row = []
    j = 0
    for line in file.readlines():
        curr = []
        empty_row.append(j)
        for i in range(len(line)):
            if line[i] != '\n':
                if j == 0:
                    empty_col.append(i)
                curr.append(line[i])
            if line[i] == '#':
                if i in empty_col:
                    del empty_col[empty_col.index(i)]
                if j in empty_row:
                    del empty_row[-1]
        raw_universe.append(curr)
        j += 1

    galaxies = expand_universe(raw_universe, empty_col, empty_row, 1000000)

    res = 0
    for i in range(len(galaxies)):
        for j in range(i + 1, len(galaxies)):
            res += distance(galaxies, i, j)

    return res;

def main(argc, argv):
    if argc < 2:
        return 1

    res = 0
    with open(argv[1], 'r') as file:
        res = read_universe(file);

    print(f"length: {res}")

    return 0

if __name__ == "__main__":
    exit(main(len(sys.argv), sys.argv))
