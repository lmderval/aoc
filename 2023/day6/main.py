#!/usr/bin/python3
import sys
import numpy as np

def find_strategies(t, d):
    n = 0
    for tau in range(t + 1):
        speed = tau
        distance = (t - tau) * speed
        if distance > d:
            n += 1
    return n

def read_records(file):
    raw_time = file.readline().strip('\n').split(':')[1].strip().split(' ')
    time = [int(rt) for rt in raw_time if rt != '']
    raw_distance = file.readline().strip('\n').split(':')[1].strip().split(' ')
    distance = [int(rd) for rd in raw_distance if rd != '']

    total_time = int("".join(raw_time))
    total_distance = int("".join(raw_distance))

    prod = 1
    for i in range(len(time)):
        prod *= find_strategies(time[i], distance[i])

    long_race = find_strategies(total_time, total_distance)

    return prod, long_race

def main(argc, argv):
    if argc < 2:
        return 1

    res = 0;
    with open(argv[1], 'r') as file:
        res = read_records(file);

    print(f"prod: {res}")

    return 0

if __name__ == "__main__":
    exit(main(len(sys.argv), sys.argv))
