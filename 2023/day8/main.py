#!/usr/bin/python3
import sys
from math import lcm
from time import sleep

instructions = None
directions = {}

def navigate_on_camel(start, step):
    global instructions, directions
    while start != "ZZZ":
        if instructions[step % len(instructions)] == 'L':
            start = directions[start][0]
        else:
            start = directions[start][1]
        step += 1

    return step

def ghost_in(place):
    return [dest for dest in directions.keys() if dest[2] == place]

def navigate_as_ghost(start, step):
    global instructions, directions
    steps = [0] * len(start)
    for i in range(len(start)):
        st = start[i]
        while st[2] != 'Z':
            if instructions[steps[i] % len(instructions)] == 'L':
                st = directions[st][0]
            else:
                st = directions[st][1]
            steps[i] += 1

    return lcm(*steps)

def read_map(file, ghost_mode):
    global instructions, directions
    instructions = file.readline().strip('\n');
    file.readline()

    for line in file.readlines():
        directions[line[:3]] = (line[7:10], line[12:15])

    if ghost_mode:
        return navigate_as_ghost(ghost_in('A'), 0)

    return navigate_on_camel('AAA', 0)


def main(argc, argv):
    if argc < 2:
        return 1

    if argc == 3:
        ghost = argv[1] == "--ghost"
        path = argv[2]
    else:
        ghost = False
        path = argv[1]

    res = 0;
    with open(path, 'r') as file:
        res = read_map(file, ghost);

    print(f"step: {res}")

    return 0

if __name__ == "__main__":
    exit(main(len(sys.argv), sys.argv))
