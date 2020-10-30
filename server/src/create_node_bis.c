/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_node_bis
*/

#include "my_ftp.h"

void data_thread_creation(t_client *client, thread_t *new_st)
{
    char uuid[1024];
    char uuid2[1024];
    char uuid3[1024];

    uuid_unparse(new_st->uuid, uuid);
    uuid_unparse(new_st->creator, uuid2);
    write(client->sfd, "257 Thread created \"", 20);
    write(client->sfd, uuid, strlen(uuid));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, uuid2, strlen(uuid2));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, ctime(&new_st->creation_time),
            strlen(ctime(&new_st->creation_time)) - 1);
    write(client->sfd, "\" \"", 3);
    write(client->sfd, new_st->title, strlen(new_st->title));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, new_st->message, strlen(new_st->message));
    write(client->sfd, "\"\n", 2);
    uuid_unparse(client->use_channel, uuid3);
    server_event_thread_created(uuid3, uuid, uuid2, new_st->message);
}

thread_t *create_thread_nod(t_client *client, thread_t *begin, char *title,
                            char *message)
{
    thread_t *new_st = malloc(sizeof(thread_t));

    new_st->next = NULL;
    new_st->title = strdup(title);
    new_st->message = strdup(message);
    new_st->reply = NULL;
    uuid_generate(new_st->uuid);
    uuid_copy(new_st->creator, client->uuid);
    time(&new_st->creation_time);
    data_thread_creation(client, new_st);
    if (begin == NULL) {
        new_st->prev = NULL;
    } else {
        new_st->prev = begin;
        begin->next = new_st;
    }
    return (new_st);
}

void data_reply_creation(t_client *client, reply_t *new_st,
                        uuid_t thread_creator)
{
    char uuid[1024];
    char uuid2[1024];
    char uuid3[1024];

    uuid_unparse(client->use_thread, uuid);
    uuid_unparse(new_st->creator, uuid2);
    uuid_unparse(thread_creator, uuid3);
    write(client->sfd, "258 Reply created \"", 19);
    write(client->sfd, uuid, strlen(uuid));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, uuid3, strlen(uuid));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, ctime(&new_st->creation_time),
            strlen(ctime(&new_st->creation_time)) - 1);
    write(client->sfd, "\" \"", 3);
    write(client->sfd, new_st->body, strlen(new_st->body));
    write(client->sfd, "\"\n", 2);
    server_event_thread_new_message(uuid, uuid2, new_st->body);
}

reply_t *create_reply_nod(t_client *client, reply_t *begin, char *body,
                            uuid_t thread_creator)
{
    reply_t *new_st = malloc(sizeof(reply_t));

    new_st->next = NULL;
    new_st->body = strdup(body);
    uuid_generate(new_st->uuid);
    uuid_copy(new_st->creator, client->uuid);
    time(&new_st->creation_time);
    data_reply_creation(client, new_st, thread_creator);
    if (begin == NULL) {
        new_st->prev = NULL;
    } else {
        new_st->prev = begin;
        begin->next = new_st;
    }
    return (new_st);
}