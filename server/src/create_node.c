/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_node
*/

#include "my_ftp.h"

void data_channel_creation(t_client *client, channel_t *new_st)
{
    char uuid[1024];
    char uuid2[1024];

    uuid_unparse(new_st->uuid, uuid);
    write(client->sfd, "256 Channel created \"", 21);
    write(client->sfd, uuid, strlen(uuid));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, new_st->name, strlen(new_st->name));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, new_st->description, strlen(new_st->description));
    write(client->sfd, "\"\n", 2);
    uuid_unparse(client->use_team, uuid2);
    server_event_channel_created(uuid2, uuid, new_st->name);
}

channel_t *create_channel_nod(t_client *client, channel_t *begin, char *name,
                                char *desc)
{
    channel_t *new_st = malloc(sizeof(channel_t));

    new_st->next = NULL;
    new_st->name = strdup(name);
    new_st->description = strdup(desc);
    new_st->thread = NULL;
    uuid_generate(new_st->uuid);
    uuid_copy(new_st->creator, client->uuid);
    time(&new_st->creation_time);
    data_channel_creation(client, new_st);
    if (begin == NULL) {
        new_st->prev = NULL;
    } else {
        new_st->prev = begin;
        begin->next = new_st;
    }
    return (new_st);
}

void data_team_creation(t_client *client, team_t *new_st)
{
    char uuid[1024];
    char uuid2[1024];

    uuid_unparse(new_st->uuid, uuid);
    write(client->sfd, "255 Team created \"", 18);
    write(client->sfd, uuid, strlen(uuid));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, new_st->name, strlen(new_st->name));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, new_st->description, strlen(new_st->description));
    write(client->sfd, "\"\n", 2);
    uuid_unparse(new_st->creator, uuid2);
    server_event_team_created(uuid, new_st->name, uuid2);
}

team_t *create_team_nod(t_client *client, team_t *begin, char *name,
                        char *desc)
{
    team_t *new_st = malloc(sizeof(team_t));

    new_st->next = NULL;
    new_st->name = strdup(name);
    new_st->description = strdup(desc);
    new_st->channel = NULL;
    uuid_generate(new_st->uuid);
    uuid_copy(new_st->creator, client->uuid);
    time(&new_st->creation_time);
    data_team_creation(client, new_st);
    if (begin == NULL) {
        new_st->prev = NULL;
    } else {
        new_st->prev = begin;
        begin->next = new_st;
    }
    return (new_st);
}

void free_list(list_t *begin)
{
    list_t *tmp = NULL;

    while (begin) {
        tmp = begin;
        begin = begin->next;

        if (tmp && tmp->arg)
            free(tmp->arg);
        free(tmp);
    }
}