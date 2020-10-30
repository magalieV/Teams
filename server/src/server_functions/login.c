/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login.c
*/

#include "my_ftp.h"

uuid_t *is_user_exist(client_list_t client_list, char *username)
{
    for (; client_list; client_list = client_list->next) {
        if (client_list->client->username &&
            strcmp(client_list->client->username, username) == 0) {
            return (&client_list->client->uuid);
        }
    }
    return (NULL);
}

int already_connected_error(char **cmd, t_server *server, t_client *client)
{
    char uuid[1024];

    uuid_unparse(client->uuid, uuid);
    write(client->sfd, "311 User already connected \"", 28);
    write(client->sfd, uuid, strlen(uuid));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, client->username, strlen(client->username));
    write(client->sfd, "\"\n", 2);
}

int user_login(char **cmd, t_server *server, t_client *client)
{
    char uuid[1024];

    client->isConnected = true;
    if (is_user_exist(server->client_list, cmd[1]) == NULL) {
        uuid_generate(client->uuid);
        uuid_unparse(client->uuid, uuid);
        client->username = strdup(cmd[1]);
        server_event_user_created(uuid, client->username);
    } else {
        uuid_copy(client->uuid, *is_user_exist(server->client_list, cmd[1]));
        client->username = strdup(cmd[1]);
    }
    uuid_unparse(client->uuid, uuid);
    server_event_user_logged_in(uuid);
    write(client->sfd, "210 Successful login \"", 22);
    write(client->sfd, uuid, strlen(uuid));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, client->username, strlen(client->username));
    write(client->sfd, "\"\n", 2);
}

int login(char **cmd, t_server *server, t_client *client)
{
    if (tablen(cmd) == 2) {
        if (client->isConnected) {
            already_connected_error(cmd, server, client);
        } else {
            user_login(cmd, server, client);
        }
    } else
        write(client->sfd, "302 Invalid arguments\n", 22);
    return (0);
}