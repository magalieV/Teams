/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** user.c
*/

#include "my_ftp.h"

bool is_user_exist_bis(t_server *server, uuid_t uuid)
{
    for (client_list_t users_tmp = server->client_list; users_tmp;
            users_tmp = users_tmp->next) {
        if (uuid_compare(users_tmp->client->uuid, uuid) == 0)
            return (true);
    }
    return (false);
}

void send_user_data(t_client *client, t_client *user_tmp)
{
    char uuid[1024];

    uuid_unparse(user_tmp->uuid, uuid);
    write(client->sfd, "202 \"", 5);
    write(client->sfd, uuid, strlen(uuid));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, user_tmp->username, strlen(user_tmp->username));
    write(client->sfd, "\" \"", 3);
    if (user_tmp->isConnected)
        write(client->sfd, "1", 1);
    else
        write(client->sfd, "0", 1);
    write(client->sfd, "\"\n", 2);
}

int list_one_user(char **cmd, t_server *server, t_client *client)
{
    char uuid[1024];
    uuid_t user_uuid;
    t_client *tmp = NULL;

    uuid_parse(cmd[1], user_uuid);
    tmp = get_user_by_uuid(server, cmd[1]);
    if (is_user_exist_bis(server, user_uuid)) {
        send_user_data(client, tmp);
    } else
        write(client->sfd, "303 User uuid invalid\n", 22);
    return (0);
}

int user(char **cmd, t_server *server, t_client *client)
{
    if (client->isConnected) {
        if (tablen(cmd) == 2) {
            list_one_user(cmd, server, client);
        } else
            write(client->sfd, "302 Invalid arguments\n", 22);
    } else
        write(client->sfd, "300 Please login with /login\n", 29);
    return (0);
}