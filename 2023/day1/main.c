#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static int getletterdigit(char *str)
{
    char *digits[] = { "zero", "one", "two",   "three", "four",
                       "five", "six", "seven", "eight", "nine" };
    for (int i = 0; i <= 9; i++)
    {
        if (strncmp(str, digits[i], strlen(digits[i])) == 0)
            return i;
    }

    return -1;
}

static int first_digit(char *str)
{
    for (size_t i = 0; str[i]; i++)
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
    for (size_t i = 0; str[i]; i++)
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
