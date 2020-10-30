/*
** EPITECH PROJECT, 2019
** memory
** File description:
** memory
*/

#include "client_header.h"
#include <stdlib.h>
#include "../../libs/myteams/logging_client.h"
#include <string.h>

static void info_cmd(string_t reply, int reply_code)
{
    char *t = strdup(reply.m_content);
    char *one, *two, *four;

    switch (reply_code) {
        case 265:
            1 ? one = get_next(&t), two = get_next(&t) : 0;
            client_print_user(one, two, atoi(get_next(&t)));
            break;
        case 266:
            1 ? one = get_next(&t), two = get_next(&t), four = get_next(&t) : 0;
            client_print_team(one, two, four);
            break;
        default:
            next_cmd(reply, reply_code, &t);
            break;
    }
}

string_t my_realloc(unsigned int size, string_t *last)
{
    string_t tmp = init_string(size);
    unsigned int index = 0;

    if (last->empty(last))
        return (tmp);
    for (index = 0; last->exist(last, index)
    and index < size; index++) {
        tmp.set(&tmp, index, last->at(last, index));
    }
    tmp.set(&tmp, index, '\0');
    last->destroy(last);
    return (tmp);
}

char *get_next(char **tmp)
{
    string_t temp = init_str("");
    unsigned int index = 0;

    if (!(*tmp) or !**tmp)
        return ("");
    while (**tmp) {
        if (**tmp and **tmp == '\"' and (!(**(tmp) + 1) or (**tmp) + 1 != '\\'))
            break;
        (*tmp)++;
    }
    (*tmp)++;
    while (**tmp) {
        if (**tmp and **tmp == '\"' and (!(**(tmp) + 1) or (**tmp) + 1 != '\\'))
            break;
        temp.add(&temp, **tmp);
        (*tmp)++;
    }
    if (**tmp)
        (*tmp)++;
    return (temp.m_content);
}

void next_list_cmd(string_t reply, int reply_code, char **t)
{
    char *one, *two, *four, *last;
    time_t my_time;

    switch (reply_code) {
        case 262:
            1 ? one = get_next(t), two = get_next(t), my_time = get_time(t),
                four = get_next(t), last = get_next(t) : 0;
            client_channel_print_threads(one, two, my_time, four, last);
            break;
        case 263:
            1 ? one = get_next(t), two = get_next(t), my_time = get_time(t),
                four = get_next(t) : 0;
            client_thread_print_replies(one, two, my_time, four);
            break;
        default:
            info_cmd(reply, reply_code);
            break;
    }
}

void next_cmd_parser(string_t reply, int reply_code, char **t)
{
    char *one, *two, *four, *last;
    time_t my_time;

    switch (reply_code) {
        case 257:
            1 ? one = get_next(t), two = get_next(t), my_time = get_time(t),
                four = get_next(t), last = get_next(t) : 0;
            client_print_thread_created(one, two, my_time, four, last);
            break;
        default:
            1 ? one = get_next(t), two = get_next(t), my_time = get_time(t),
                four = get_next(t) : 0;
            client_print_reply_created(one, two, my_time, four);
            break;
    }
}