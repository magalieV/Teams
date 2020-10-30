/*
** EPITECH PROJECT, 2019
** convert
** File description:
** convert
*/

#include "client_header.h"
#include <string.h>
#include "../../libs/myteams/logging_client.h"
#include <stdio.h>

string_t int_to_string(int number)
{
    string_t tmp = init_string(100);

    sprintf(tmp.m_content, "%d", number);
    return (tmp);
}

unsigned int tab_len(array list)
{
    unsigned int len = 0;

    for (len = 0; list[len]; len++);
    return (len);
}

time_t get_time(char **tmp)
{
    struct tm tm;

    strptime(get_next(tmp), "%a %b %d %H:%M:%S %Y", &tm);
    return (mktime(&tm));
}

void next_event(string_t reply, int reply_code, char **t)
{
    char *one, *two, *four, *last;
    time_t my_time;

    switch (reply_code) {
        case 292:
            1 ? one = get_next(t), two = get_next(t), four = get_next(t) : 0;
            client_event_team_created(one, two, four);
            break;
        case 293:
            1 ? one = get_next(t), two = get_next(t), four = get_next(t) : 0;
            client_event_channel_created(one, two, four);
            break;
        case 294:
            1 ? one = get_next(t), two = get_next(t), my_time = get_time(t),
            four = get_next(t), last = get_next(t) : 0;
            client_event_thread_created(one, two, my_time, four, last);
            break;
        default:
            break;
    }
}

void next_cmd(string_t reply, int reply_code, char **t)
{
    char *one, *two, *four, *last;
    time_t my_time;

    switch (reply_code) {
        case 267:
            1 ? one = get_next(t), two = get_next(t), four = get_next(t) : 0;
            client_print_channel(one, two, four);
            break;
        case 268:
            1 ? one = get_next(t), two = get_next(t), my_time = get_time(t),
                four = get_next(t), last = get_next(t) : 0;
            client_print_thread(one, two, my_time, four, last);
            break;
        default:
            break;
    }
}