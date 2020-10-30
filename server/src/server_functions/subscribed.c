/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** subscribed.c
*/

#include "my_ftp.h"

int list_all_subscribed_team(char **cmd, t_server *server, t_client *client)
{
    char tmp_uuid2[1024];

    for (list_sub_t *tmp = client->sub; tmp; tmp = tmp->next) {
        team_t *team_tmp = get_team(server, tmp->uuid);
        uuid_unparse(tmp->uuid, tmp_uuid2);
        write(client->sfd, "235 Subscribed to \"", 19);
        write(client->sfd, tmp_uuid2, strlen(tmp_uuid2));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, team_tmp->name, strlen(team_tmp->name));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, team_tmp->description,
                strlen(team_tmp->description));
        write(client->sfd, "\"\n", 2);
    }
}

void print_is_connectd(t_client *client)
{
    if (client->isConnected)
        write(client->sfd, "1", 1);
    else
        write(client->sfd, "0", 1);
}

int list_all_user_subscribed(char **cmd, t_server *server, t_client *client,
                            uuid_t team_uuid)
{
    uuid_t tmp_uuid1;
    char tmp_uuid2[1024];
    for (client_list_t list = server->client_list; list; list = list->next) {
        uuid_unparse(list->client->uuid, tmp_uuid2);
        for (list_sub_t *tmp = list->client->sub; tmp; tmp = tmp->next) {
            if (uuid_compare(tmp->uuid, team_uuid) == 0) {
                write(client->sfd, "236 User subscribed \"", 21);
                write(client->sfd, tmp_uuid2, strlen(tmp_uuid2));
                write(client->sfd, "\" \"", 3);
                write(client->sfd, list->client->username,
                        strlen(list->client->username));
                write(client->sfd, "\" \"", 3);
                print_is_connectd(list->client);
                write(client->sfd, "\"\n", 2);
            }
        }
    }
}

int subscribed(char **cmd, t_server *server, t_client *client)
{
    uuid_t tmp_uuid1;
    char tmp_uuid2[1024];

    if (client->isConnected) {
        if (tablen(cmd) == 2) {
            uuid_parse(cmd[1], tmp_uuid1);
            if (is_team_exist(server, tmp_uuid1)) {
                list_all_user_subscribed(cmd, server, client, tmp_uuid1);
            } else
                write(client->sfd, "304 Team uuid invalid\n", 22);
        } else if (tablen(cmd) == 1) {
            list_all_subscribed_team(cmd, server, client);
        } else {
            write(client->sfd, "302 Invalid arguments\n", 22);
        }
    } else {
        write(client->sfd, "300 Please login with /login\n", 29);
    }
    return (0);
}