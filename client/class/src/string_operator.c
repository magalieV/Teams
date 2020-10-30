/*
** EPITECH PROJECT, 2019
** string_operator
** File description:
** string_operator
*/

#include "client_header.h"
#include <string.h>
#include <stdlib.h>

static bool equal(struct string_s *this, struct string_s other)
{
    if (this->empty(this) or other.empty(&other))
        return (false);
    if (strcmp(this->m_content, other.m_content) == 0)
        return (true);
    return (false);
}

static char *find_number(struct string_s *this)
{
    array list = this->split(*this, init_str(" \t\n={}$"));
    char *nb = NULL;

    for (unsigned int i = 0; list[i]; i++) {
        if (list[i][0] and list[i][0] >= '0' and list[i][0] <= '9')
            nb = list[i];
    }
    return (nb);
}

void init_operator(string_t *str)
{
    str->equal = &equal;
    str->find_number = &find_number;
}