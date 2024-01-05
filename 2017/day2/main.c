#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 64

static char *read_file(FILE *file)
{
    char ptr[BUFFER_LENGTH] = { 0 };
    char *content = NULL;
    size_t size = 0;
    size_t len = 0;
    while ((size = fread(ptr, sizeof(char), BUFFER_LENGTH, file)) != 0)
    {
        content = realloc(content, sizeof(char) * (len + size + 1));

        for (size_t i = 0; i < size; i++)
            content[len + i] = ptr[i];

        len += size;
    }

    content[len] = '\0';

    return content;
}

static int *to_int_array(char *content, size_t *size)
{
    *size = 0;
    if (!content)
        return NULL;

    int *arr = NULL;
    char *saveptr = NULL;
    for (char *number = strtok_r(content, " \f\n\r\t\v", &saveptr); number;
            number = strtok_r(NULL, " \f\n\r\t\v", &saveptr))
    {
        arr = realloc(arr, sizeof(int) * (*size + 1));
        arr[(*size)++] = atoi(number);
    }

    return arr;
}

static void min_max(int *arr, int *min, int *max, size_t size)
{
    *min = arr[0];
    *max = arr[0];

    for (size_t i = 1; i < size; i++)
    {
        if (*min > arr[i])
            *min = arr[i];
        if (*max < arr[i])
            *max = arr[i];
    }
}

static int calculate_checksum(const char *content)
{
    char *copy = malloc(sizeof(char) * (strlen(content) + 1));
    strcpy(copy, content);

    int checksum = 0;
    char *saveptr = NULL;
    for (char *line = strtok_r(copy, "\n", &saveptr); line;
            line = strtok_r(NULL, "\n", &saveptr))
    {
        int min = 0;
        int max = 0;

        size_t size = 0;
        int *arr = to_int_array(line, &size);
        min_max(arr, &min, &max, size);

        free(arr);

        checksum += max - min;
    }

    free(copy);

    return checksum;
}

static int divide(int *arr, size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = i + 1; j < size; j++)
        {
            if (arr[i] % arr[j] == 0)
                return arr[i] / arr[j];

            if (arr[j] % arr[i] == 0)
                return arr[j] / arr[i];
        }
    }

    return 0;
}

static int find_evenly_divisible(const char *content)
{
    char *copy = malloc(sizeof(char) * (strlen(content) + 1));
    strcpy(copy, content);

    int sum = 0;
    char *saveptr = NULL;
    for (char *line = strtok_r(copy, "\n", &saveptr); line;
            line = strtok_r(NULL, "\n", &saveptr))
    {
        size_t size = 0;
        int *arr = to_int_array(line, &size);

        sum += divide(arr, size);

        free(arr);
    }

    free(copy);

    return sum;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    FILE *file = fopen(argv[1], "r");

    char *content = read_file(file);
    fclose(file);

    printf("checksum: %d\n", calculate_checksum(content));
    printf("evenly_divisible: %d\n", find_evenly_divisible(content));

    free(content);

    return 0;
}
