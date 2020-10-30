/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** messages.c
*/

#include "my_ftp.h"

int *get_list_separator(char *line)
{
    int *separator = malloc(sizeof(int *) * 6);

    for (int i = 0, count = 0; line[i] != '\n'; i++) {
        if (line[i] == '\"') {
            separator[count] = i;
            count++;
        }
    }
    return (separator);
}

char **get_message(char *line)
{
    int *separator = get_list_separator(line);
    char **params = malloc(sizeof(char *) * (4));

    params[0] = split_by_len(line, separator[0] + 1, separator[1] - 1);
    params[1] = split_by_len(line, separator[2] + 1, separator[3] - 1);
    params[2] = split_by_len(line, separator[4] + 1, separator[5] - 1);
    params[3] = NULL;

    return (params);
}

int transfert_message(t_client *client, char **params)
{
    long long timestamp = atoll(params[1]);
    time_t time = (time_t)timestamp;

    write(client->sfd, "225 \"", 5);
    write(client->sfd, params[0], strlen(params[0]));
    write(client->sfd, "\" \"", 3);
    write(client->sfd, ctime(&time), strlen(ctime(&time)) - 1);
    write(client->sfd, "\" \"", 3);
    write(client->sfd, params[2], strlen(params[2]));
    write(client->sfd, "\"\n", 2);
}

int list_all_messages(char **cmd, t_server *server, t_client *client,
                        uuid_t user)
{
    t_client *receiver = get_user_by_uuid(server, cmd[1]);
    char *filename = get_conversation(client->username, receiver->username);
    FILE *fs = fopen(filename, "r");
    char *line = NULL;
    size_t line_nb = 0;

    while (getline(&line, &line_nb, fs) != -1) {
        transfert_message(client, get_message(line));
    }
}

int messages(char **cmd, t_server *server, t_client *client)
{
    uuid_t receiver_uuid;

    if (client->isConnected) {
        if (tablen(cmd) == 2) {
            uuid_parse(cmd[1], receiver_uuid);
            if (is_user_exist_bis(server, receiver_uuid) &&
                uuid_compare(client->uuid, receiver_uuid) != 0) {
                list_all_messages(cmd, server, client, receiver_uuid);
            } else
                write(client->sfd, "303 User uuid invalid\n", 22);
        } else
            write(client->sfd, "302 Invalid arguments\n", 22);
    } else
        write(client->sfd, "300 Please login with /login\n", 29);
    return (0);
}