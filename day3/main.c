#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static bool issymbol(char c)
{
    if (isdigit(c))
        return false;

    if (c == '.' || c == '\n')
        return false;

    return true;
}

static int parse_number(char **engine, size_t i, size_t j, size_t size)
{
    if (engine[i][j] == '\0')
        return 0;

    bool isvalid = false;
    int value = atoi(engine[i] + j);

    size_t up_length = (i == 0) ? 0 : strlen(engine[i - 1]);
    size_t down_length = (i == size - 1) ? 0 : strlen(engine[i + 1]);

    if (j > 0)
    {
        if (j - 1 < up_length && issymbol(engine[i - 1][j - 1]))
            isvalid = true;

        if (issymbol(engine[i][j - 1]))
            isvalid = true;

        if (j - 1 < down_length && issymbol(engine[i + 1][j - 1]))
            isvalid = true;
    }

    while (isdigit(engine[i][j]))
    {
        if (j < up_length && issymbol(engine[i - 1][j]))
            isvalid = true;

        if (issymbol(engine[i][j]))
            isvalid = true;

        if (j < down_length && issymbol(engine[i + 1][j]))
            isvalid = true;

        j++;
    }

    if (j < up_length && issymbol(engine[i - 1][j]))
        isvalid = true;

    if (engine[i][j] != '\0' && issymbol(engine[i][j]))
        isvalid = true;

    if (j < down_length && issymbol(engine[i + 1][j]))
        isvalid = true;

    return isvalid ? value : 0;
}

static int parse_engine(char **engine, size_t size)
{
    int sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        size_t j = 0;
        while (engine[i][j] != '\0')
        {
            while (engine[i][j] != '\0' && !isdigit(engine[i][j]))
                j++;

            sum += parse_number(engine, i, j, size);

            while (isdigit(engine[i][j]))
                j++;
        }
    }

    return sum;
}

static int get_gear_ratio(char **engine, size_t i, ssize_t j, size_t size)
{
    ssize_t k = j;
    int numbers = 0;
    int prod = 1;
    if (i > 0)
    {
        if (j > 0)
        {
            k--;
            while (k >= 0 && isdigit(engine[i - 1][k]))
                k--;

            if (k != j - 1)
            {
                numbers++;
                k++;
                prod *= atoi(engine[i - 1] + k);
            }

            while (isdigit(engine[i - 1][k]))
                k++;

            if (k < j)
                k = j;
        }

        if (k == j)
        {
            if (!isdigit(engine[i - 1][k]))
                k++;

            if (isdigit(engine[i - 1][k]))
            {
                numbers++;
                prod *= atoi(engine[i - 1] + k);
            }
        }
    }

    k = j;
    if (j > 0 && isdigit(engine[i][j - 1]))
    {
        k--;
        while (k >= 0 && isdigit(engine[i][k]))
            k--;

        numbers++;
        k++;
        prod *= atoi(engine[i] + k);
    }

    k = j + 1;
    if (engine[i][k] != '\0' && isdigit(engine[i][k]))
    {
        numbers++;
        prod *= atoi(engine[i] + k);
    }

    k = j;
    if (i + 1 < size)
    {
        if (j > 0)
        {
            k--;
            while (k >= 0 && isdigit(engine[i + 1][k]))
                k--;

            if (k != j - 1)
            {
                k++;
                numbers++;
                prod *= atoi(engine[i + 1] + k);
            }

            while (isdigit(engine[i + 1][k]))
                k++;

            if (k < j)
                k = j;
        }

        if (k == j)
        {
            if (!isdigit(engine[i + 1][k]))
                k++;

            if (isdigit(engine[i + 1][k]))
            {
                numbers++;
                prod *= atoi(engine[i + 1] + k);
            }
        }
    }

    return (numbers == 2) ? prod : 0;
}

static int calculate_gear_ratio(char **engine, size_t size)
{
    int sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; engine[i][j] != '\0'; j++)
        {
            if (engine[i][j] == '*')
                sum += get_gear_ratio(engine, i, j, size);
        }
    }

    return sum;
}

static int read_engine(FILE *file, int *gear_ratio)
{
    int sum = 0;
    char *line = NULL;
    char **engine = NULL;
    size_t size = 0;
    size_t n = 0;
    while (getline(&line, &n, file) > 0)
    {
        size++;
        engine = realloc(engine, sizeof(char *) * size);
        engine[size - 1] = malloc(sizeof(char) * (strlen(line) + 1));
        strcpy(engine[size - 1], line);
    }

    free(line);

    sum = parse_engine(engine, size);
    *gear_ratio = calculate_gear_ratio(engine, size);

    for (size_t i = 0; i < size; i++)
        free(engine[i]);

    free(engine);

    return sum;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    FILE *file = fopen(argv[1], "r");

    int gear_ratio = 0;
    int sum = read_engine(file, &gear_ratio);
    printf("sum: %d\n", sum);
    printf("gear_ratio: %d\n", gear_ratio);

    fclose(file);

    return 0;
}
