#define _POSIX_C_SOURCE 200809L

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

static int calculate_captcha(const char *captcha)
{
    int sum = 0;
    char last = '\0';
    for (size_t i = 0; captcha[i + 1]; i++)
    {
        if (captcha[i] == captcha[i + 1])
        {
            int digit = captcha[i] - '0';
            sum += digit;
        }

        last = captcha[i + 1];
    }

    if (captcha[0] == last)
    {
        int digit = captcha[0] - '0';
        sum += digit;
    }

    return sum;
}

static int calculate_halfway_captcha(const char *captcha)
{
    int sum = 0;
    size_t half = strlen(captcha) / 2;
    for (size_t i = 0; i < half; i++)
    {
        if (captcha[i] == captcha[half + i])
        {
            int digit = captcha[i] - '0';
            sum += 2 * digit;
        }
    }

    return sum;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    FILE *file = fopen(argv[1], "r");

    char *content = read_file(file);
    fclose(file);

    char *saveptr = NULL;
    for (char *line = strtok_r(content, "\n", &saveptr); line;
            line = strtok_r(NULL, "\n", &saveptr))
    {
        printf("line: %s\n", line);
        printf("captcha: %d\n", calculate_captcha(line));
        printf("halfway_captcha: %d\n", calculate_halfway_captcha(line));
    }

    free(content);

    return 0;
}
