/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** unsubscribe.c
*/

#include "my_ftp.h"

int unsubscribe_bis(char **cmd, t_server *server, t_client *client,
                    uuid_t team_uuid)
{
    char user_uuid[1024];
    if (is_team_exist(server, team_uuid)) {
        if (is_subscribed(client, team_uuid) == false) {
            write(client->sfd, "341 User not subscribed to the team \"", 37);
            write(client->sfd, cmd[1], strlen(cmd[1]));
            write(client->sfd, "\"\n", 2);
        } else {
            uuid_unparse(client->uuid, user_uuid);
            write(client->sfd, "240 User unsubscribed to \"", 26);
            write(client->sfd, user_uuid, strlen(user_uuid));
            write(client->sfd, "\" \"", 3);
            write(client->sfd, cmd[1], strlen(cmd[1]));
            write(client->sfd, "\"\n", 2);
            client->sub = delete_sub_node_uuid(client->sub, team_uuid);
            for (; client->sub && client->sub->prev;
                    client->sub = client->sub->prev);
            server_event_user_leave_a_team(cmd[1], user_uuid);
        }
    } else
        write(client->sfd, "304 Team uuid invalid\n", 22);
}

int unsubscribe(char **cmd, t_server *server, t_client *client)
{
    uuid_t tmp;
    char user_uuid[1024];

    if (client->isConnected) {
        if (tablen(cmd) == 2) {
            uuid_parse(cmd[1], tmp);
            unsubscribe_bis(cmd, server, client, tmp);
        } else {
            write(client->sfd, "302 Invalid arguments\n", 22);
        }
    } else {
        write(client->sfd, "300 Please login with /login\n", 29);
    }
    return (0);
}