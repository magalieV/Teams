/*
** EPITECH PROJECT, 2019
** string_init_setter
** File description:
** string_init_setter
*/

#include "client_header.h"
#include <stdlib.h>
#include <stdio.h>

static bool set(struct string_s *this, unsigned int index, char value)
{
    if (this->m_content == NULL or index >= this->m_size)
        return (false);
    this->m_content[index] = value;
    return (true);
}

static bool add(struct string_s *this, char c)
{
    char *tmp = NULL;
    unsigned int index = 0;

    tmp = malloc(sizeof(char) * (this->size(this) + 2));
    if (!tmp)
        return (false);
    for (index = 0; this->exist(this, index); index++) {
        tmp[index] = this->at(this, index);
    }
    tmp[index] = c;
    tmp[++index] = '\0';
    free(this->m_content);
    this->m_content = tmp;
    this->m_size += 1;
    return (true);
}

static bool append(struct string_s *this, struct string_s other)
{
    char *tmp = NULL;
    unsigned int index = 0;

    if (this->empty(this))
        return (false);
    tmp = malloc(sizeof(char) * (this->size(this) + other.size(&other) + 2));
    if (!tmp)
        return (false);
    for (unsigned int idx = 0; this->exist(this, idx); idx++) {
        tmp[index++] = this->at(this, idx);
    }
    for (unsigned int idx = 0; other.exist(&other, idx); idx++) {
        tmp[index++] = other.at(&other, idx);
    }
    tmp[index] = '\0';
    free(this->m_content);
    this->m_content = tmp;
    this->m_size += other.size(&other);
    return (true);
}

static bool empty(struct string_s *this)
{
    if (!this->m_content or this->size(this) == 0)
        return (true);
    return (false);
}

void init_setter(string_t *str)
{
    str->set = &set;
    str->add = &add;
    str->append = &append;
    str->empty = &empty;
    init_getter(str);
    init_operator(str);
}