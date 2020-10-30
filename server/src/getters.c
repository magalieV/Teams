/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** getters
*/

#include "my_ftp.h"

team_t *get_team(t_server *server, uuid_t uuid)
{
    for (team_t *team_tmp = server->team_list; team_tmp;
            team_tmp = team_tmp->next) {
        if (uuid_compare(team_tmp->uuid, uuid) == 0)
            return (team_tmp);
    }
    return (NULL);
}

channel_t *get_channel(t_server *server, uuid_t team_uuid, uuid_t chan_uuid)
{
    team_t *team_tmp = get_team(server, team_uuid);
    for (channel_t *chan_tmp = team_tmp->channel; chan_tmp;
            chan_tmp = chan_tmp->next) {
        if (uuid_compare(chan_tmp->uuid, chan_uuid) == 0)
            return (chan_tmp);
    }
    return (NULL);
}

thread_t *get_thread(t_server *server, uuid_t team_uuid, uuid_t chan_uuid,
                        uuid_t thread_uuid)
{
    channel_t *chan_tmp = get_channel(server, team_uuid, chan_uuid);
    for (thread_t *thread_tmp = chan_tmp->thread; thread_tmp;
        thread_tmp = thread_tmp->next) {
        if (uuid_compare(thread_tmp->uuid, thread_uuid) == 0)
            return (thread_tmp);
    }
    return (NULL);
}

t_client *get_user_by_uuid(t_server *server, char *uuid)
{
    uuid_t user_uuid;

    uuid_parse(uuid, user_uuid);
    for (client_list_t list = server->client_list; list; list = list->next) {
        if (uuid_compare(list->client->uuid, user_uuid) == 0) {
            return (list->client);
        }
    }
    return (NULL);
}

bool is_team_exist(t_server *server, uuid_t uuid)
{
    for (team_t *tmp = server->team_list; tmp; tmp = tmp->next)
        if (uuid_compare(tmp->uuid, uuid) == 0)
            return (true);
    return (false);
}