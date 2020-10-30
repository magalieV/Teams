/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** utils.c
*/

#include "my_ftp.h"

int count(char *str, char c)
{
    int count = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            count++;
    return (count);
}

int count_once(char *str, char c)
{
    int count = 0;
    int find = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == c)
            find++;
        if (str[i] != c)
            find = 0;
        if (str[i] == c && find == 1)
            count++;
    }
    return (count);
}

char *clear_str(char *str, char delimiter)
{
    char *new = malloc(sizeof(char) * (strlen(str) - count(str, delimiter)
                + count_once(str, delimiter) + 1));
    int idx = 0;
    bool find = false;
    int _find = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == delimiter)
            _find++;
        if (str[i] != delimiter)
            _find = 0;
        if ((_find == 1 && str[i] != '\n') ||
            (str[i] != delimiter && str[i] != '\n')) {
            new[idx] = str[i];
            idx++;
        }
    }
    new[idx] = '\0';
    return (new);
}

size_t strlen_n(char *str, int pos, char delimiter)
{
    size_t nb = 0;

    for (int i = pos; str[i]; i++, nb++) {
        if (str[i] == delimiter)
            break;
    }

    return (nb--);
}

char **split(char *str, char delimiter)
{
    char **tab = malloc(sizeof(char *) * (count(str, delimiter) + 2));
    int x = 0;
    int y = 0;
    int idx = 0;
    int nb = 0;

    for (; y < count(str, delimiter) + 1; y++) {
        nb = strlen_n(str, idx, delimiter);
        tab[y] = malloc(sizeof(char) * (nb + 1));
        x = 0;
        for (; x < nb; idx++, x++) {
            tab[y][x] = str[idx];
        }
        idx++;
        tab[y][x] = '\0';
    }
    tab[y] = NULL;
    return (tab);
}