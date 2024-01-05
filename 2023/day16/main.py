#!/usr/bin/python3
import sys

def energize_tiles(beam, contraption):
    w = len(contraption[0])
    h = len(contraption)

    beams = [beam]
    memo = set(())
    energized = set(())

    res = 0

    while beams != []:
        beam = beams.pop(0)
        if beam in memo:
            continue

        memo.add(beam)
        x, y, dx, dy = beam

        if 0 <= x < w and 0 <= y < h:
            if (x, y) not in energized:
                energized.add((x, y))
                res += 1

        nx, ny = x + dx, y + dy
        if nx < 0 or nx >= w or ny < 0 or ny >= h:
            continue

        if contraption[ny][nx] == '/':
            dx, dy = -dy, -dx
        elif contraption[ny][nx] == '\\':
            dx, dy = dy, dx
        elif contraption[ny][nx] == '|':
            if dy == 0:
                dx = 0
                dy = 1
                beams.append((nx, ny, 0, -1))
        elif contraption[ny][nx] == '-':
            if dx == 0:
                dx = 1
                dy = 0
                beams.append((nx, ny, -1, 0))
        beams.append((nx, ny, dx, dy))

    return res

def count_energized(energized):
    res = 0
    for line in energized:
        res += sum(line)

    return res

def read_contraption(file):
    res = 0
    contraption = []
    for line in file.readlines():
        curr_c = []
        curr_e = []
        for c in line:
            if c != '\n':
                curr_c.append(c)
        contraption.append(curr_c)

    w = len(contraption[0])
    h = len(contraption)

    for j in range(h):
        res = max(res, energize_tiles((-1, j, 1, 0), contraption))
        res = max(res, energize_tiles((w, j, -1, 0), contraption))

    for i in range(w):
        res = max(res, energize_tiles((i, -1, 0, 1), contraption))
        res = max(res, energize_tiles((i, h, 0, -1), contraption))

    return res

def main(argc, argv):
    if argc < 2:
        return 1

    res = 0
    with open(argv[1], 'r') as file:
        res = read_contraption(file);

    print(f"res: {res}")

    return 0

if __name__ == "__main__":
    exit(main(len(sys.argv), sys.argv))
