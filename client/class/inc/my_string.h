/*
** EPITECH PROJECT, 2019
** my_string
** File description:
** my_string
*/

#ifndef __MYTEAMS_MY_STRING_H__
#define __MYTEAMS_MY_STRING_H__

#include "client_header.h"
#include <stdbool.h>

#define array char **

typedef struct string_s
{
    char *m_content;
    unsigned int m_size;
    bool (*set)(struct string_s *this, unsigned int index, char value);
    bool (*add)(struct string_s *this, char c);
    bool (*append)(struct string_s *this, struct string_s other);
    void (*destroy)(struct string_s *this);
    char *(*content)(struct string_s *this);
    unsigned int (*size)(struct string_s *this);
    bool (*empty)(struct string_s *this);
    bool (*exist)(struct string_s *this, unsigned int index);
    char (*at)(struct string_s *this, unsigned int index);
    bool (*equal)(struct string_s *this, struct string_s other);
    array (*split)(struct string_s str, struct string_s delimiter);
    char *(*find_number)(struct string_s *this);
} string_t;

string_t init_string(unsigned int size);
string_t init_str(char *str);
string_t put_on_string(char *message, ...);
void init_setter(string_t *str);
void init_getter(string_t *str);
void init_operator(string_t *str);

#endif //__MYTEAMS_MY_STRING_H__
