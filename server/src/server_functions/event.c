/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** event.c
*/

#include "my_ftp.h"

void thread_created_event(t_server *server, t_client *client, thread_t *thread)
{
    char uuid[1024];
    for (client_list_t tmp = server->client_list; tmp; tmp = tmp->next) {
        if (is_subscribed(tmp->client, client->use_team) &&
            uuid_compare(thread->creator, tmp->client->uuid) != 0) {
            uuid_unparse(thread->uuid, uuid);
            write(tmp->client->sfd, "294 Thread created \"", 20);
            write(tmp->client->sfd, uuid, strlen(uuid));
            write(tmp->client->sfd, "\" \"", 3);
            uuid_unparse(thread->creator, uuid);
            write(tmp->client->sfd, uuid, strlen(uuid));
            write(tmp->client->sfd, "\" \"", 3);
            write(tmp->client->sfd, ctime(&thread->creation_time),
                    strlen(ctime(&thread->creation_time)) - 1);
            write(tmp->client->sfd, "\" \"", 3);
            write(tmp->client->sfd, thread->title, strlen(thread->title));
            write(tmp->client->sfd, "\" \"", 3);
            write(tmp->client->sfd, thread->message, strlen(thread->message));
            write(tmp->client->sfd, "\"\n", 2);
        }
    }
}

void channel_created_event(t_server *server, t_client *client,
                            channel_t *channel)
{
    char uuid[1024];

    for (client_list_t user_tmp = server->client_list; user_tmp;
            user_tmp = user_tmp->next) {
        if (is_subscribed(user_tmp->client, client->use_team) &&
            uuid_compare(channel->creator, user_tmp->client->uuid) != 0) {
            uuid_unparse(channel->uuid, uuid);
            write(user_tmp->client->sfd, "293 Channel created \"", 21);
            write(user_tmp->client->sfd, uuid, strlen(uuid));
            write(user_tmp->client->sfd, "\" \"", 3);
            write(user_tmp->client->sfd, channel->name, strlen(channel->name));
            write(user_tmp->client->sfd, "\" \"", 3);
            write(user_tmp->client->sfd, channel->description,
                    strlen(channel->description));
            write(user_tmp->client->sfd, "\"\n", 2);
        }
    }
}

void new_thread_message_event(t_server *server, t_client *client,
                                reply_t *reply)
{
    char uuid[1024];

    for (client_list_t user_tmp = server->client_list; user_tmp;
        user_tmp = user_tmp->next) {
        if (is_subscribed(user_tmp->client, client->use_team) &&
            uuid_compare(reply->creator, user_tmp->client->uuid) != 0) {
            uuid_unparse(client->use_team, uuid);
            write(user_tmp->client->sfd, "291 New thread message \"", 24);
            write(user_tmp->client->sfd, uuid, strlen(uuid));
            write(user_tmp->client->sfd, "\" \"", 3);
            uuid_unparse(client->use_thread, uuid);
            write(user_tmp->client->sfd, uuid, strlen(uuid));
            write(user_tmp->client->sfd, "\" \"", 3);
            uuid_unparse(reply->creator, uuid);
            write(user_tmp->client->sfd, uuid, strlen(uuid));
            write(user_tmp->client->sfd, "\" \"", 3);
            write(user_tmp->client->sfd, reply->body, strlen(reply->body));
            write(user_tmp->client->sfd, "\"\n", 2);
        }
    }
}

void new_private_message_event(t_client *sender, t_client *receiver,
                                char *body)
{
    char uuid_sender[1024];
    char uuid_receiver[1024];

    uuid_unparse(sender->uuid, uuid_sender);
    uuid_unparse(receiver->uuid, uuid_receiver);
    write(receiver->sfd, "290 Private message received \"", 30);
    write(receiver->sfd, uuid_sender, strlen(uuid_sender));
    write(receiver->sfd, "\" \"", 3);
    write(receiver->sfd, body, strlen(body));
    write(receiver->sfd, "\"\n", 2);
    server_event_private_message_sended(uuid_sender, uuid_receiver, body);
}

int create_tris(char **cmd, t_server *server, t_client *client)
{
    if (is_subscribed(client, client->use_team)) {
        if (client->use_value == REPLY)
            create_reply(client, server, cmd[1]);
    } else
        write(client->sfd, "308 User not subscribed to ", 27);
        write(client->sfd, "the team\n", 9);
}