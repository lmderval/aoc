#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static int getletterdigit(char *str)
{
    if (strncmp(str, "zero", 4) == 0)
        return 0;

    if (strncmp(str, "one", 3) == 0)
        return 1;

    if (strncmp(str, "two", 3) == 0)
        return 2;

    if (strncmp(str, "three", 5) == 0)
        return 3;

    if (strncmp(str, "four", 4) == 0)
        return 4;

    if (strncmp(str, "five", 4) == 0)
        return 5;

    if (strncmp(str, "six", 3) == 0)
        return 6;

    if (strncmp(str, "seven", 5) == 0)
        return 7;

    if (strncmp(str, "eight", 5) == 0)
        return 8;

    if (strncmp(str, "nine", 4) == 0)
        return 9;

    return -1;
}

static int first_digit(char *str)
{
    for(size_t i = 0; str[i]; i++)
    {
        if (isdigit(str[i]))
            return str[i] - '0';

        int ldigit = getletterdigit(str + i);
        if (ldigit != -1)
            return ldigit;
    }

    return 0;
}

static int last_digit(char *str)
{
    int digit = 0;
    for(size_t i = 0; str[i]; i++)
    {
        if (isdigit(str[i]))
        {
            digit = str[i] - '0';
        }
        else
        {
            int ldigit = getletterdigit(str + i);
            if (ldigit != -1)
                digit = ldigit;
        }
    }

    return digit;
}

static int read_calibration(FILE *file)
{
    int sum = 0;
    char *line = NULL;
    size_t n = 0;
    while (getline(&line, &n, file) > 0)
    {
        int i = first_digit(line) * 10;
        int j = last_digit(line);
        sum += i + j;
    }

    free(line);

    return sum;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    FILE *file = fopen(argv[1], "r");

    int sum = read_calibration(file);
    printf("sum: %d\n", sum);

    fclose(file);

    return 0;
}
