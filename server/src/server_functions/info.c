/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** info.c
*/

#include "my_ftp.h"

int info_channel(char **cmd, t_server *server, t_client *client)
{
    channel_t *tmp = get_channel(server, client->use_team,
                                client->use_channel);
    char uuid[1024];

    if (tmp != NULL) {
        uuid_unparse(tmp->uuid, uuid);
        write(client->sfd, "267 \"", 5);
        write(client->sfd, uuid, strlen(uuid));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, tmp->name, strlen(tmp->name));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, tmp->description, strlen(tmp->description));
        write(client->sfd, "\"\n", 2);
    }
    return (267);
}

int info_thread(char **cmd, t_server *server, t_client *client)
{
    thread_t *tmp = get_thread(server, client->use_team, client->use_channel,
                                client->use_thread);
    char uuid[1024];
    if (tmp != NULL) {
        uuid_unparse(tmp->uuid, uuid);
        write(client->sfd, "268 \"", 5);
        write(client->sfd, uuid, strlen(uuid));
        write(client->sfd, "\" \"", 3);
        uuid_unparse(tmp->creator, uuid);
        write(client->sfd, uuid, strlen(uuid));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, ctime(&tmp->creation_time),
        strlen(ctime(&tmp->creation_time)) - 1);
        write(client->sfd, "\" \"", 3);
        write(client->sfd, tmp->title, strlen(tmp->title));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, tmp->message, strlen(tmp->message));
        write(client->sfd, "\"\n", 2);
    }
    return (268);
}

int info_user(char **cmd, t_server *server, t_client*client)
{
    char uuid[1024];

    uuid_unparse(client->uuid, uuid);
    write(client->sfd, "265 \"", 5);
    write(client->sfd, uuid, strlen(uuid));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, client->username, strlen(client->username));
    write(client->sfd, "\" \"", 3);
    if (client->isConnected)
        write(client->sfd, "1", 1);
    else
        write(client->sfd, "0", 1);
    write(client->sfd, "\"\n", 2);
    return (265);
}

int info_bis(char **cmd, t_server *server, t_client *client)
{
    if (client->use_value == TEAM) {
        info_user(cmd, server, client);
        return (0);
    } if (is_subscribed(client, client->use_team)) {
        if (client->use_value == CHANNEL)
            info_team(cmd, server, client);
        if (client->use_value == THREAD)
            info_channel(cmd, server, client);
        if (client->use_value == REPLY)
            info_thread(cmd, server, client);
    } else
        write(client->sfd, "308 User not subscribed to the team\n", 36);
}

int info(char **cmd, t_server *server, t_client *client)
{
    if (client->isConnected) {
        if (tablen(cmd) == 1)
            info_bis(cmd, server, client);
        else
            write(client->sfd, "302 Invalid arguments\n", 22);
    } else
        write(client->sfd, "300 Please login with /login\n", 29);

    return (0);
}