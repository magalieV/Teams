/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** subscribe.c
*/

#include "my_ftp.h"

bool is_subscribed(t_client *client, uuid_t uuid)
{
    for (list_sub_t *tmp = client->sub; tmp; tmp = tmp->next) {
        if (uuid_compare(tmp->uuid, uuid) == 0)
            return (true);
    }
    return (false);
}

int subscribe_user(char **cmd, t_server *server, t_client *client)
{
    uuid_t tmp;
    char user_uuid[1024];

    uuid_parse(cmd[1], tmp);
    for (; client->sub && client->sub->next; client->sub = client->sub->next);
    client->sub = create_sub_node(client->sub, tmp);
    for (client->sub; client->sub->prev; client->sub = client->sub->prev);
    uuid_unparse(client->uuid, user_uuid);
    write(client->sfd, "230 Successful subscription \"", 29);
    write(client->sfd, user_uuid, strlen(user_uuid));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, cmd[1], strlen(cmd[1]));
    write(client->sfd, "\"\n", 2);
    server_event_user_join_a_team(cmd[1], user_uuid);
}

int subscribe_bis(char **cmd, t_server *server, t_client *client)
{
    uuid_t tmp;
    char user_uuid[1024];

    uuid_parse(cmd[1], tmp);
    if (is_team_exist(server, tmp)) {
        if (is_subscribed(client, tmp)) {
            write(client->sfd, "331 Already subscribed to \"", 27);
            write(client->sfd, user_uuid, strlen(user_uuid));
            write(client->sfd, "\" \"", 3);
            write(client->sfd, cmd[1], strlen(cmd[1]));
            write(client->sfd, "\"\n", 2);
        } else {
            subscribe_user(cmd, server, client);
        }
    } else
        write(client->sfd, "304 Team uuid invalid\n", 22);
}

int subscribe(char **cmd, t_server *server, t_client *client)
{
    uuid_t tmp;
    char user_uuid[1024];

    if (client->isConnected) {
        if (tablen(cmd) == 2) {
            subscribe_bis(cmd, server, client);
        } else {
            write(client->sfd, "302 Invalid arguments\n", 22);
        }
    } else {
        write(client->sfd, "300 Please login with /login\n", 29);
    }
    return (0);
}