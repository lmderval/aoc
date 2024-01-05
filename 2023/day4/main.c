#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static int get_card_number(char *card)
{
    size_t i = 0;
    while (!isdigit(card[i]))
        i++;

    return atoi(card + i);
}

static int *parse_numbers(char *str, size_t *size)
{
    int *numbers = NULL;
    char *saveptr = NULL;
    for (char *n = strtok_r(str, " ", &saveptr); n;
         n = strtok_r(NULL, " ", &saveptr))
    {
        (*size)++;
        numbers = realloc(numbers, sizeof(int) * (*size));
        numbers[*size - 1] = atoi(n);
    }

    return numbers;
}

static int count_point(char *card, int *scratchcards, int **copies, int *size)
{
    int card_number = get_card_number(card);

    size_t i = 0;
    while (card[i] != ':')
        i++;

    char *content = card + i + 1;

    char *saveptr = NULL;
    char *winning = strtok_r(content, "|", &saveptr);
    char *numbers = strtok_r(NULL, "\n", &saveptr);

    size_t winning_length = 0;
    size_t numbers_length = 0;

    int *winning_numbers = parse_numbers(winning, &winning_length);
    int *my_numbers = parse_numbers(numbers, &numbers_length);

    int points = 0;
    int new_copies = 0;
    for (i = 0; i < numbers_length; i++)
    {
        for (size_t j = 0; j < winning_length; j++)
        {
            if (my_numbers[i] == winning_numbers[j])
            {
                points = points ? 2 * points : 1;
                new_copies++;
            }
        }
    }

    int old_size = *size;
    *size =
        (*size > card_number + new_copies) ? *size : card_number + new_copies;

    *copies = realloc(*copies, sizeof(int) * (*size));

    for (int k = old_size; k < *size; k++)
        (*copies)[k] = 1;

    for (int k = 0; k < new_copies; k++)
    {
        (*copies)[card_number + k] += (*copies)[card_number - 1];
    }

    *scratchcards += (*copies)[card_number - 1];

    free(winning_numbers);
    free(my_numbers);

    return points;
}

static int read_card(FILE *file, int *scratchcards)
{
    int sum = 0;
    char *line = NULL;
    size_t n = 0;
    int *copies = malloc(sizeof(int));
    *copies = 1;
    int size = 1;
    while (getline(&line, &n, file) > 0)
    {
        sum += count_point(line, scratchcards, &copies, &size);
    }

    free(line);

    free(copies);

    return sum;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    FILE *file = fopen(argv[1], "r");

    int scratchcards = 0;
    int sum = read_card(file, &scratchcards);
    printf("sum: %d\n", sum);
    printf("scratchcards: %d\n", scratchcards);

    fclose(file);

    return 0;
}
