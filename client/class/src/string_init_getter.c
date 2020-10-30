/*
** EPITECH PROJECT, 2019
** init_getter
** File description:
** init_getter
*/

#include "client_header.h"
#include "tools.h"
#include <string.h>

static char *content(struct string_s *this)
{
    return (this->m_content);
}

static unsigned int size(struct string_s *this)
{
    return (this->m_size);
}

static bool exist(struct string_s *this, unsigned int index)
{
    if (this->empty(this))
        return (false);
    if (this->m_content[index])
        return (true);
    return (false);
}

static char at(struct string_s *this, unsigned int index)
{
    if (this->empty(this))
        return ('\0');
    return (this->m_content[index]);
}

void init_getter(string_t *str)
{
    str->content = &content;
    str->size = &size;
    str->exist = &exist;
    str->at = &at;
    str->split = &split;
}