#!/usr/bin/python3
import sys

def find_group(springs, group):
    if len(springs) < group:
        return 0

    for i in range(group):
        if springs[i] == '.':
            return 0

    if len(springs) == group:
        return 1

    if springs[group] == '#':
        return 0

    return 1

def any(s, c):
    for x in s:
        if x == c:
            return 1
    return 0

def find_arrangement(springs, groups, pos, gpos, memo):
    if (pos, gpos) in memo:
        return memo[(pos, gpos)]

    max_index = len(springs[pos:]) - sum(groups[gpos:]) - len(groups[gpos:]) + 1
    if max_index < 0:
        memo[(pos, gpos)] = 0
        return 0

    if len(groups) == gpos:
        res = 1 - any(springs[pos:], '#')
        memo[(pos, gpos)] = res
        return res

    res = 0
    group = groups[gpos]
    if springs[pos] == '.' or springs[pos] == '?':
        res += find_arrangement(springs, groups, pos + 1, gpos, memo)

    if springs[pos] == '#' or springs[pos] == '?':
        find = find_group(springs[(pos + 1):], group - 1)
        if find == 1:
            res += find_arrangement(springs, groups, pos + group + 1, gpos + 1, memo)

    memo[(pos, gpos)] = res
    return res

def read_springs(file):
    res = 0
    n = 5
    for line in file.readlines():
        springs, raw_groups = line.split(' ')
        groups = [int(group) for group in raw_groups.split(',')]
        res += find_arrangement(
                (springs + '?') * (n - 1) + springs, groups * 5, 0, 0, {})

    return res;

def main(argc, argv):
    if argc < 2:
        return 1

    res = 0
    with open(argv[1], 'r') as file:
        res = read_springs(file);

    print(f"length: {res}")

    return 0

if __name__ == "__main__":
    exit(main(len(sys.argv), sys.argv))
