/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** logout.c
*/

#include "my_ftp.h"

int logout(char **cmd, t_server *server, t_client *client)
{
    char uuid[1024];

    if (tablen(cmd) == 1) {
        if (!client->isConnected)
            write(client->sfd, "316 User not connected\n", 23);
        else {
            client->isConnected = false;
            uuid_unparse(client->uuid, uuid);
            write(client->sfd, "215 Successful logout \"", 23);
            write(client->sfd, uuid, strlen(uuid));
            write(client->sfd, "\" \"", 3);
            write(client->sfd, client->username, strlen(client->username));
            write(client->sfd, "\"\n", 2);
            server_event_user_logged_out(uuid);
            return (215);
        }
    } else
        write(client->sfd, "302 Invalid arguments\n", 22);
    return (0);
}