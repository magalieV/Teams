/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** use.c
*/

#include "my_ftp.h"

int use_team(char **cmd, t_server *server, t_client *client)
{
    client->use_value = TEAM;
    write(client->sfd, "250 Use OK (set for team)\n", 26);
}

int use_channel(char **cmd, t_server *server, t_client *client)
{
    uuid_t tmp;

    uuid_parse(cmd[1], tmp);
    if (get_team(server, tmp)) {
        client->use_value = CHANNEL;
        uuid_copy(client->use_team, tmp);
        write(client->sfd, "250 Use OK (set for channel)\n", 29);
    } else
        write(client->sfd, "304 Team uuid invalid\n", 22);
}

int use_thread(char **cmd, t_server *server, t_client *client)
{
    uuid_t tmp;
    uuid_t tmp_chan;

    uuid_parse(cmd[1], tmp);
    uuid_parse(cmd[2], tmp_chan);
    if (get_channel(server, tmp, tmp_chan)) {
        client->use_value = THREAD;
        uuid_copy(client->use_team, tmp);
        uuid_copy(client->use_channel, tmp_chan);
        write(client->sfd, "250 Use OK (set for thread)\n", 28);
    } else {
        write(client->sfd, "305 Channel uuid invalid\n", 25);
    }
}

int use_reply(char **cmd, t_server *server, t_client *client)
{
    uuid_t tmp;
    uuid_t tmp_chan;
    uuid_t tmp_thread;

    uuid_parse(cmd[1], tmp);
    uuid_parse(cmd[2], tmp_chan);
    uuid_parse(cmd[3], tmp_thread);
    if (get_thread(server, tmp, tmp_chan, tmp_thread)) {
        client->use_value = REPLY;
        uuid_copy(client->use_team, tmp);
        uuid_copy(client->use_channel, tmp_chan);
        uuid_copy(client->use_thread, tmp_thread);
        write(client->sfd, "250 Use OK (set for reply)\n", 27);
    } else
        write(client->sfd, "306 Thread uuid invalid\n", 24);
}

int use(char **cmd, t_server *server, t_client *client)
{
    if (client->isConnected) {
        if (tablen(cmd) == 1)
            use_team(cmd, server, client);
        if (tablen(cmd) == 2)
            use_channel(cmd, server, client);
        if (tablen(cmd) == 3)
            use_thread(cmd, server, client);
        if (tablen(cmd) == 4)
            use_reply(cmd, server, client);
        if (tablen(cmd) != 1 && tablen(cmd) != 2 &&
            tablen(cmd) != 3 && tablen(cmd) != 4)
            write(client->sfd, "302 Invalid arguments\n", 22);
    } else
        write(client->sfd, "300 Please login with /login\n", 29);
    return (0);
}