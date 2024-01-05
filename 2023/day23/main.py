#!/usr/bin/python3
import sys

sys.setrecursionlimit(25000)

def neighbours_slopes(trails, u, visited):
    x, y = u
    neighbours = []
    if (x + 1, y) not in visited and (
        trails[y][x] == '>'
        or (
            trails[y][x] == '.'
            and trails[y][x + 1] != '#'
        )
    ):
        neighbours.append((x + 1, y))

    if (x - 1, y) not in visited and (
        trails[y][x] == '<'
        or (
            trails[y][x] == '.'
            and trails[y][x - 1] != '#'
        )
    ):
        neighbours.append((x - 1, y))

    if (x, y + 1) not in visited and (
        trails[y][x] == 'v'
        or (
            trails[y][x] == '.'
            and trails[y + 1][x] != '#'
        )
    ):
        neighbours.append((x, y + 1))

    if (x, y - 1) not in visited and (
        trails[y][x] == '^'
        or (
            trails[y][x] == '.'
            and trails[y - 1][x] != '#'
        )
    ):
        neighbours.append((x, y - 1))

    return neighbours

def neighbours(trails, u, visited):
    x, y = u
    neighbours = []
    if (
        (x + 1, y) not in visited
        and trails[y][x + 1] != '#'
    ):
        neighbours.append((x + 1, y))

    if (
        (x - 1, y) not in visited
        and trails[y][x - 1] != '#'
    ):
        neighbours.append((x - 1, y))

    if (
        (x, y + 1) not in visited
        and trails[y + 1][x] != '#'
    ):
        neighbours.append((x, y + 1))

    if (
        (x, y - 1) not in visited
        and trails[y - 1][x] != '#'
    ):
        neighbours.append((x, y - 1))

    return neighbours

def dfs_rec(trails, u, d, visited, L, l):
    visited.add(u)
    L.append(u)

    if u == d:
        l.append(len(L) - 1)
    else:
        for s in neighbours(trails, u, visited):
            dfs_rec(trails, s, d, visited, L, l)

    L.pop()
    visited.remove(u)

def dfs(trails):
    w = len(trails[0])
    h = len(trails)
    L = [(1, 0)]
    visited = {(1, 0)}
    l = []
    dfs_rec(trails, (1, 1), (w - 2, h - 1), visited, L, l)

    return max(l)

def read_trail(file):
    res = 0
    trails = []
    for line in file.readlines():
        trails.append([c for c in line if c != '\n'])

    res = dfs(trails)
    return res

def main(argc, argv):
    if argc < 2:
        return 1

    res = 0;
    with open(argv[1], 'r') as file:
        res = read_trail(file);

    print(f"res: {res}")

    return 0

if __name__ == "__main__":
    exit(main(len(sys.argv), sys.argv))
