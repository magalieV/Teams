/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** info_bis
*/

#include "my_ftp.h"

int info_team(char **cmd, t_server *server, t_client *client)
{
    team_t *tmp = get_team(server, client->use_team);
    char uuid[1024];

    if (tmp != NULL) {
        uuid_unparse(tmp->uuid, uuid);
        write(client->sfd, "266 \"", 5);
        write(client->sfd, uuid, strlen(uuid));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, tmp->name, strlen(tmp->name));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, tmp->description, strlen(tmp->description));
        write(client->sfd, "\"\n", 2);
    }
    return (266);
}

int list_teams(t_server *server, t_client *client)
{
    char uuid[1024];

    for (team_t *team = server->team_list; team; team = team->next) {
        uuid_unparse(team->uuid, uuid);
        write(client->sfd, "260 \"", 5);
        write(client->sfd, uuid, strlen(uuid));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, team->name, strlen(team->name));
        write(client->sfd, "\" \"", 3);
        write(client->sfd, team->description, strlen(team->description));
        write(client->sfd, "\"\n", 2);
    }
}

char *split_by_len(char *str, int begin, int end)
{
    char *new_str = malloc(sizeof(char) * (end - begin + 2));
    int i = 0;

    for (; begin <= end; begin++, i++)
        new_str[i] = str[begin];
    new_str[i] = '\0';
    return (new_str);
}

int print_team(team_t *teams)
{
    return (0);
}

char *get_timestamp(void)
{
    char *str_timestamp = malloc(sizeof(char) * 1024);
    long timestamp = (long)time(NULL);

    sprintf(str_timestamp, "%ld", timestamp);
    return (str_timestamp);
}