/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create.c
*/

#include "my_ftp.h"

int create_channel(t_client *client, t_server *server, char *name, char *desc)
{
    for (team_t *tmp = server->team_list; tmp; tmp = tmp->next) {
        if (uuid_compare(tmp->uuid, client->use_team) == 0) {
            for (tmp->channel; tmp->channel && tmp->channel->next;
                    tmp->channel = tmp->channel->next);
            tmp->channel = create_channel_nod(client, tmp->channel, name,
                                                desc);
            channel_created_event(server, client, tmp->channel);
            for (tmp->channel; tmp->channel->prev;
                    tmp->channel = tmp->channel->prev);
        }
    }
}

int create_thread(t_client *client, t_server *server, char *title,
                    char *message)
{
    channel_t *chan = get_channel(server, client->use_team,
                                client->use_channel);

    for (chan->thread; chan->thread && chan->thread->next;
        chan->thread = chan->thread->next);
    chan->thread = create_thread_nod(client, chan->thread, title, message);
    thread_created_event(server, client, chan->thread);
    for (chan->thread; chan->thread->prev; chan->thread = chan->thread->prev);
}

int create_reply(t_client *client, t_server *server, char *body)
{
    thread_t *thread = get_thread(server, client->use_team,
                        client->use_channel, client->use_thread);

    for (thread->reply; thread->reply && thread->reply->next;
        thread->reply = thread->reply->next);
    thread->reply = create_reply_nod(client, thread->reply, body,
                    thread->creator);
    new_thread_message_event(server, client, thread->reply);
    for (thread->reply; thread->reply->prev;
        thread->reply = thread->reply->prev);
}

int create_bis(char **cmd, t_server *server, t_client *client)
{
    if (client->use_value == TEAM) {
        for (server->team_list; server->team_list && server->team_list->next;
                server->team_list = server->team_list->next);
        server->team_list = create_team_nod(client, server->team_list,
                            cmd[1], cmd[2]);
        for (server->team_list; server->team_list->prev;
            server->team_list = server->team_list->prev);
        return 0;
    }
    if (is_subscribed(client, client->use_team)) {
        if (client->use_value == CHANNEL) {
            create_channel(client, server, cmd[1], cmd[2]);
        }
        if (client->use_value == THREAD) {
            create_thread(client, server, cmd[1], cmd[2]);
        }
    } else
        write(client->sfd, "308 User not subscribed to the team\n", 36);
}

int create(char **cmd, t_server *server, t_client *client)
{
    if (client->isConnected) {
        if (tablen(cmd) == 3)
            create_bis(cmd, server, client);
        else if (tablen(cmd) == 2)
            create_tris(cmd, server, client);
        else
            write(client->sfd, "302 Invalid arguments\n", 22);
    } else
        write(client->sfd, "300 Please login with /login\n", 29);
    return (0);
}