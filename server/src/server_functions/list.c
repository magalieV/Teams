/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list.c
*/

#include "my_ftp.h"

int list_channels(t_server *server, t_client *client)
{
    char uuid[1024];

    for (team_t *team = server->team_list; team; team = team->next) {
        if (uuid_compare(team->uuid, client->use_team) == 0) {
            for (channel_t *chan = team->channel; chan; chan = chan->next) {
                uuid_unparse(chan->uuid, uuid);
                write(client->sfd, "261 \"", 5);
                write(client->sfd, uuid, strlen(uuid));
                write(client->sfd, "\" \"", 3);
                write(client->sfd, chan->name, strlen(chan->name));
                write(client->sfd, "\" \"", 3);
                write(client->sfd, chan->description,
                        strlen(chan->description));
                write(client->sfd, "\"\n", 2);
            }
        }
    }
}

int list_threads(t_server *server, t_client *client)
{
    char uuid[1024];
    char uuid2[1024];
    channel_t *chan = get_channel(server, client->use_team,
                                client->use_channel);
    for (thread_t *thread = chan->thread; thread; thread = thread->next) {
        uuid_unparse(thread->uuid, uuid);
        uuid_unparse(thread->creator, uuid2);
        write(client->sfd, "262 \"", 5);
        write(client->sfd, uuid, strlen(uuid));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, uuid2, strlen(uuid));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, ctime(&thread->creation_time),
                strlen(ctime(&thread->creation_time)) - 1);
        write(client->sfd, "\" \"", 3);
        write(client->sfd, thread->title, strlen(thread->title));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, thread->message, strlen(thread->message));
        write(client->sfd, "\"\n", 2);
    }
}

int list_replies(t_server *server, t_client *client)
{
    char uuid[1024];
    char uuid2[1024];
    thread_t *thread = get_thread(server, client->use_team,
                        client->use_channel, client->use_thread);

    for (reply_t *reply = thread->reply; reply; reply = reply->next) {
        uuid_unparse(client->use_thread, uuid);
        uuid_unparse(thread->creator, uuid2);
        write(client->sfd, "263 \"", 5);
        write(client->sfd, uuid, strlen(uuid));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, uuid2, strlen(uuid));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, ctime(&reply->creation_time),
                strlen(ctime(&reply->creation_time)) - 1);
        write(client->sfd, "\" \"", 3);
        write(client->sfd, reply->body, strlen(reply->body));
        write(client->sfd, "\"\n", 2);
    }
}

int list_bis(char **cmd, t_server *server, t_client *client)
{
    if (client->use_value == TEAM) {
        list_teams(server, client);
        return (0);
    }
    if (is_subscribed(client, client->use_team)) {
        if (client->use_value == CHANNEL)
            list_channels(server, client);
        if (client->use_value == THREAD)
            list_threads(server, client);
        if (client->use_value == REPLY)
            list_replies(server, client);
    }  else
            write(client->sfd, "308 User not subscribed to the team\n", 36);
}

int list(char **cmd, t_server *server, t_client *client)
{
    if (client->isConnected) {
        if (tablen(cmd) == 1)
            list_bis(cmd, server, client);
        else
            write(client->sfd, "302 Invalid arguments\n", 22);
    } else
        write(client->sfd, "300 Please login with /login\n", 29);
    return (0);
}