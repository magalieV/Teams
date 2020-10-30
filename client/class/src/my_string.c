/*
** EPITECH PROJECT, 2019
** my_string
** File description:
** my_string
*/

#include "client_header.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

static string_t found_type(char c, va_list *list)
{
    string_t tmp = init_string(2);

    if (c == 'd')
        return (int_to_string(va_arg(*list, int)));
    else if (c == 's')
        return (init_str(va_arg(*list, char *)));
    tmp.set(&tmp, 0, va_arg(*list, int));
    return (tmp);
}

string_t put_on_string(char *message, ...)
{
    va_list list;
    string_t mess = init_string(1);
    string_t str = init_str(message);

    mess.m_content[0] = '\0';
    va_start(list, message);
    for (unsigned int index = 0; str.exist(&str, index); index++) {
        if (str.at(&str, index) == '%' and str.exist(&str, index + 1)
            and str.at(&str, index + 1) != '%') {
            mess.append(&mess, found_type(str.at(&str, index + 1), &list));
            index += 1;
        } else if (str.at(&str, index) == '%') {
            mess.add(&mess, '%');
            index += 1;
        } else {
            mess.add(&mess, str.at(&str, index));
        }
    }
    return (mess);
}

static void destroy(struct string_s *this)
{
    free(this->m_content);
}

string_t init_string(unsigned int size)
{
    string_t str;

    if (size != 0) {
        str.m_content = malloc(sizeof(char) * size);
        if (!str.m_content) {
            fprintf(stdout, "Error, can't init a string\n");
            exit(84);
        }
        bzero(str.m_content, size);
    } else
        str.m_content = NULL;
    str.destroy = &destroy;
    str.m_size = size;
    init_setter(&str);
    return (str);
}

string_t init_str(char *str)
{
    string_t content;

    content.m_content = strdup(str);
    content.m_size = strlen(str);
    content.destroy = &destroy;
    init_setter(&content);
    return (content);
}