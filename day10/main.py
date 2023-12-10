#!/usr/bin/python3
import sys

east_pipe = ['S', '-', '7', 'J']
west_pipe = ['S', '-', 'F', 'L']
north_pipe = ['S', '|', '7', 'F']
south_pipe = ['S', '|', 'L', 'J']

def bfs(pipe, st_x, st_y):
    pos = [(st_x, st_y)]
    w = len(pipe[0])
    h = len(pipe)
    distance = [[-1 for _ in range(w)] for _ in range(h)]
    distance[st_y][st_x] = 0
    while len(pos) > 0:
        i, j = pos.pop(0)
        if pipe[j][i] in east_pipe and i > 0 \
                and pipe[j][i - 1] in west_pipe and distance[j][i - 1] == -1:
            pos.append((i - 1, j))
            distance[j][i - 1] = distance[j][i] + 1
        if pipe[j][i] in west_pipe and i + 1 < w \
                and pipe[j][i + 1] in east_pipe and distance[j][i + 1] == -1:
            pos.append((i + 1, j))
            distance[j][i + 1] = distance[j][i] + 1
        if pipe[j][i] in south_pipe and j > 0 \
                and pipe[j - 1][i] in north_pipe and distance[j - 1][i] == -1:
            pos.append((i, j - 1))
            distance[j - 1][i] = distance[j][i] + 1
        if pipe[j][i] in north_pipe and j + 1 < h \
                and pipe[j + 1][i] in south_pipe and distance[j + 1][i] == -1:
            pos.append((i, j + 1))
            distance[j + 1][i] = distance[j][i] + 1

    inside = 0
    for j in range(h):
        state = 0
        for i in range(w):
            if distance[j][i] == -1:
                pipe[j][i] = 'I' if state else 'O'
                if state:
                    inside += 1
            else:
                if pipe[j][i] in south_pipe:
                    state ^= 1
                if pipe[j][i] in north_pipe:
                    state ^= 2

    #for j in range(h):
    #    print(pipe[j])

    return (max([max(d) for d in distance]), inside)

def determine_start(pipe, i, j):
    w = len(pipe[0])
    h = len(pipe)
    if i > 0 and pipe[j][i - 1] in west_pipe:
        if j > 0 and pipe[j - 1][i] in north_pipe:
            pipe[j][i] = 'J'
        elif j + 1 < h and pipe[j + 1][i] in south_pipe:
            pipe[j][i] = '7'
        else:
            pipe[j][i] = '-'
    elif i + 1 < w and pipe[j][i + 1] in east_pipe:
        if j > 0 and pipe[j - 1][i] in north_pipe:
            pipe[j][i] = 'L'
        else:
            pipe[j][i] = 'F'
    else:
        pipe[j][i] = '|'


def read_pipe(file):
    pipe = []
    st_x = 0
    st_y = 0
    i = 0
    j = 0

    for line in file.readlines():
        curr = []
        i = 0
        for c in line:
            if c == '\n':
                break

            if c == 'S':
                st_x = i
                st_y = j
            curr.append(c)
            i += 1

        pipe.append(curr)
        j += 1

    determine_start(pipe, st_x, st_y)

    return bfs(pipe, st_x, st_y)


def main(argc, argv):
    if argc < 2:
        return 1

    res = 0;
    inside = 0
    with open(argv[1], 'r') as file:
        res, inside = read_pipe(file);

    print(f"size: {res}")
    print(f"inside: {inside}")

    return 0

if __name__ == "__main__":
    exit(main(len(sys.argv), sys.argv))
