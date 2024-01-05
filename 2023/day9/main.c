#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#ifdef DEBUG
static void print_array(int *arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
        printf("%d ", arr[i]);

    printf("\n");
}
#endif /* DEBUG */

static bool is_zero(int *arr, size_t size)
{
    for (size_t i = 1; i < size; i++)
    {
        if (arr[i] != 0)
            return false;
    }

    return true;
}

static int extrapolate(int *arr, size_t size)
{
    if (is_zero(arr, size))
    {
        return 0;
    }
    else
    {
        for (size_t i = 1; i < size - 1; i++)
            arr[i] = arr[i + 1] - arr[i];

#ifdef DEBUG
        print_array(arr, size - 1);
#endif /* DEBUG */

        int tmp = arr[1];
        int next_value = extrapolate(arr, size - 1) + arr[size - 1];

        arr[0] = tmp - arr[0];

        return next_value;
    }
}

static int parse_history(char *line, int *prev)
{
    size_t size = 1;
    int *history = malloc(sizeof(int) * size);
    history[0] = 0;
    for (size_t i = 0; line[i] != '\0' && line[i] != '\n'; i++)
    {
        size++;
        history = realloc(history, sizeof(int) * size);
        history[size - 1] = atoi(line + i);
        while (isdigit(line[i]) || line[i] == '-')
            i++;
    }

    int tmp = history[1];
    int val = extrapolate(history, size);
    *prev += tmp - history[0];

    free(history);

    return val;
}

static int read_report(FILE *file, int *prev)
{
    char *line = NULL;
    size_t n = 0;
    int next = 0;
    while (getline(&line, &n, file) > 0)
        next += parse_history(line, prev);

    free(line);

    return next;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    FILE *file = fopen(argv[1], "r");

    int prev = 0;
    int next = read_report(file, &prev);
    printf("next: %d\n", next);
    printf("prev: %d\n", prev);

    fclose(file);

    return 0;
}
