/*
** EPITECH PROJECT, 2019
** temp
** File description:
** temp
*/

#include "client_header.h"
#include "../../libs/myteams/logging_client.h"
#include <stdlib.h>
#include <string.h>

static void list_cmd(string_t reply, int reply_code, char **t)
{
    char *one, *two, *fo;

    switch (reply_code) {
        case 236:
            1 ? one = get_next(t), two = get_next(t), fo = get_next(t) : 0;
            client_print_users(one, two, atoi(fo));
            break;
        case 260:
            1 ? one = get_next(t), two = get_next(t), fo = get_next(t) : 0;
            client_print_teams(one, two, fo);
            break;
        case 261:
            1 ? one = get_next(t), two = get_next(t), fo = get_next(t) : 0;
            client_team_print_channels(one, two, fo);
            break;
        default:
            next_list_cmd(reply, reply_code, t);
            break;
    }
}

static void next_passive_info(string_t reply, int reply_code, char **t)
{
    char *one, *two, *fo;
    time_t tm;

    switch (reply_code) {
        case 225:
            1 ? one = get_next(t), tm = get_time(t), two = get_next(t) : 0;
            client_private_message_print_messages(one, tm, two);
            break;
        case 235:
            1 ? one = get_next(t), two = get_next(t), fo = get_next(t) : 0;
            client_print_teams(one, two, fo);
            break;
        default:
            list_cmd(reply, reply_code, t);
            break;
    }
}

void cmd_parser(client_information_t *c,
    string_t reply, int reply_code)
{
    char *t = strdup(reply.m_content);
    char *one, *two, *four;

    switch (reply_code) {
        case 255:
            1 ? one = get_next(&t), two = get_next(&t),
            four = get_next(&t) : 0;
            client_print_team_created(one, two, four);
            break;
        case 256:
            1 ? one = get_next(&t), two = get_next(&t),
            four = get_next(&t) : 0;
            client_print_channel_created(one, two, four);
            break;
        default:
            next_cmd_parser(reply, reply_code, &t);
            break;
    }
}

void event_user(int reply_code, string_t reply)
{
    char *t = strdup(reply.m_content);
    char *one, *two, *three, *four;

    switch (reply_code) {
        case 290:
            1 ? one = get_next(&t), two = get_next(&t) : 0;
            client_event_private_message_received(one, two);
            break;
        case 291:
            1 ? one = get_next(&t), two = get_next(&t), three = get_next(&t),
                four = get_next(&t) : 0;
            client_event_thread_message_received(one, two, three, four);
            break;
        default:
            next_event(reply, reply_code, &t);
            break;
    }
}

void get_passive_information(client_information_t *cl,
    string_t reply, int reply_code)
{
    char *t = strdup(reply.m_content);
    char *one, *two;

    switch (reply_code) {
        case 201:
            1 ? one = get_next(&t), two = get_next(&t) : 0;
            client_print_users(one, two, atoi(get_next(&t)));
            break;
        case 202:
            1 ? one = get_next(&t), two = get_next(&t) : 0;
            client_print_user(one, two, atoi(get_next(&t)));
            break;
        default:
            next_passive_info(reply, reply_code, &t);
            break;
    }
}