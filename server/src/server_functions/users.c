/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** users.c
*/

#include "my_ftp.h"

int list_all_users(t_server *server, t_client *client)
{
    char uuid[1024];

    for (client_list_t users_tmp = server->client_list; users_tmp;
        users_tmp = users_tmp->next) {
        uuid_unparse(users_tmp->client->uuid, uuid);
        write(client->sfd, "201 \"", 5);
        write(client->sfd, uuid, strlen(uuid));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, users_tmp->client->username,
                strlen(users_tmp->client->username));
        write(client->sfd, "\" \"", 3);
        if (users_tmp->client->isConnected)
            write(client->sfd, "1", 1);
        else
            write(client->sfd, "0", 1);
        write(client->sfd, "\"\n", 2);
    }
}

int users(char **cmd, t_server *server, t_client *client)
{
    if (client->isConnected) {
        if (tablen(cmd) == 1) {
            list_all_users(server, client);
        } else
            write(client->sfd, "302 Invalid arguments\n", 22);
    } else
        write(client->sfd, "300 Please login with /login\n", 29);
    return (0);
}