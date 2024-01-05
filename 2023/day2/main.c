#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static int max(int x, int y)
{
    return (x > y) ? x : y;
}

static int parse_game(char *game, int cubes[3])
{
    int id = atoi(game + 5);
    char *saveptrset = NULL;
    size_t j = 5;
    while (game[j++] != ':')
        continue;

    for (char *set = strtok_r(game + j, ";", &saveptrset); set;
         set = strtok_r(NULL, ";", &saveptrset))
    {
        char *saveptrcube = NULL;
        for (char *cube = strtok_r(set, ",", &saveptrcube); cube;
             cube = strtok_r(NULL, ",", &saveptrcube))
        {
            int n = atoi(cube + 1);
            size_t i = 1;
            while (cube[i++] != ' ')
                continue;

            if (strncmp(cube + i, "red", 3) == 0)
                cubes[0] = max(cubes[0], n);

            if (strncmp(cube + i, "green", 5) == 0)
                cubes[1] = max(cubes[1], n);

            if (strncmp(cube + i, "blue", 4) == 0)
                cubes[2] = max(cubes[2], n);
        }
    }

    return id;
}

static int read_game(FILE *file, unsigned long long *power)
{
    int sum = 0;
    char *line = NULL;
    size_t n = 0;
    while (getline(&line, &n, file) > 0)
    {
        int cubes[3] = { 0, 0, 0 };
        int id = parse_game(line, cubes);
        if (cubes[0] <= 12 && cubes[1] <= 13 && cubes[2] <= 14)
            sum += id;

        *power += cubes[0] * cubes[1] * cubes[2];
    }

    free(line);

    return sum;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    FILE *file = fopen(argv[1], "r");

    unsigned long long power = 0;
    int sum = read_game(file, &power);
    printf("sum: %d\n", sum);
    printf("power: %llu\n", power);

    fclose(file);

    return 0;
}
