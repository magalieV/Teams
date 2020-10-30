/*
** EPITECH PROJECT, 2019
** string_function
** File description:
** string_function
*/

#include "client_header.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void is_same_part(char first, char second, unsigned int *counter,
    bool *delimiter_before)
{
    if (first != second) {
        *delimiter_before = false;
        return;
    }
    if (!*delimiter_before) {
        *counter += 1;
    }
    *delimiter_before = true;
}

static bool is_delimiter(char c, string_t delimiter)
{
    if (c == '\0')
        return (true);
    for (unsigned int idx = 0; delimiter.exist(&delimiter, idx); idx++) {
        if (delimiter.at(&delimiter, idx) == c)
            return (true);
    }
    return (false);
}

static unsigned int found_part_number(string_t str, string_t delimiter)
{
    unsigned int counter = 0;
    bool delimiter_before = true;

    if (str.empty(&str) or delimiter.empty(&delimiter))
        return (0);
    for (unsigned int index = 0; str.exist(&str, index); index++) {
        for (unsigned int idx = 0; delimiter.exist(&delimiter, idx); idx++) {
            is_same_part(str.at(&str, index), delimiter.at(&delimiter, idx),
            &counter, &delimiter_before);
        }
    }
    return (counter);
}

static string_t copy_char(string_t str, unsigned int *index,
                        unsigned int size, string_t delimiter)
{
    string_t new_str = init_string(size + 1);

    if (new_str.empty(&new_str)) {
        fprintf(stdout, "Malloc error on split\n");
        exit(84);
    }
    for (size = *index; str.exist(&str, size); size++) {
        if (is_delimiter(str.at(&str, size), delimiter))
            break;
        new_str.set(&new_str, size - *index, str.at(&str, size));
    }
    new_str.set(&new_str, size - *index, '\0');
    *index = size;
    return (new_str);
}

array split(struct string_s str, struct string_s d)
{
    array new_array = NULL;
    unsigned int size = 0, depth = 0;
    unsigned int size_array = found_part_number(str, d);
    string_t tmp = init_string(0);

    if (size_array == 0 or is_delimiter(str.at(&str, 0), d))
        return (NULL);
    if (!(new_array = malloc(sizeof(char *) * (size_array + 1))))
        1 ? fprintf(stdout, "Malloc error on split\n"), exit(84) : 0;
    for (unsigned int index = 0; str.exist(&str, index); index++) {
        while (str.exist(&str, index) and is_delimiter(str.at(&str, index), d))
            index++;
        for (size = 0; !is_delimiter(str.at(&str, index + size), d); size++);
        if (size == 0 or str.at(&str, index + size) == '\0')
            break;
        tmp = copy_char(str, &index, size, d);
        new_array[depth++] = tmp.content(&tmp);
        new_array[depth] = NULL;
    }
    return (new_array);
}