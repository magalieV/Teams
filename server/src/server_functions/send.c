/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send.c
*/

#include "my_ftp.h"

char *get_filename_conversation(char *first_name, char *second_name,
                                DIR *dir, struct dirent *dp)
{
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            if (strcmp(dp->d_name, first_name) == 0) {
                closedir(dir);
                return (my_strcat("private/", first_name));
            }
            if (strcmp(dp->d_name, second_name) == 0) {
                closedir(dir);
                return (my_strcat("private/", second_name));
            }
        }
    }
    closedir(dir);
    return (NULL);
}

char *get_conversation(char *sender, char *receiver)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir("private");
    char *first_name = NULL;
    char *second_name = NULL;

    first_name = my_strcat(sender, ".");
    first_name = my_strcat(first_name, receiver);
    second_name = my_strcat(receiver, ".");
    second_name = my_strcat(second_name, sender);
    if (!dir)
        return NULL;
    return (get_filename_conversation(first_name, second_name, dir, dp));
}

char *get_line_to_save(char **cmd, uuid_t sender_uuid)
{
    char *line = NULL;

    line = my_strcat("\"", sender_uuid);
    line = my_strcat(line, "\" \"");
    line = my_strcat(line, get_timestamp());
    line = my_strcat(line, "\" \"");
    line = my_strcat(line, cmd[2]);
    line = my_strcat(line, "\"\n");
}

int send_message_to_user(char **cmd, t_server *server, t_client *client)
{
    FILE *file = NULL;
    t_client *receiver = get_user_by_uuid(server, cmd[1]);
    char *line = NULL;
    char *filename = get_conversation(client->username, receiver->username);
    char sender_uuid[1024];

    uuid_unparse(client->uuid, sender_uuid);
    if (filename == NULL) {
        filename = my_strcat(filename, "private/");
        filename = my_strcat(filename, client->username);
        filename = my_strcat(filename, ".");
        filename = my_strcat(filename, receiver->username);
    }
    file = fopen(filename, "a+");
    line = get_line_to_save(cmd, sender_uuid);
    fwrite(line, 1, strlen(line), file);
    fclose(file);
    new_private_message_event(client, receiver, cmd[2]);
}

int send_function(char **cmd, t_server *server, t_client *client)
{
    uuid_t receiver_uuid;

    if (client->isConnected) {
        if (tablen(cmd) == 3) {
            uuid_parse(cmd[1], receiver_uuid);
            if (is_user_exist_bis(server, receiver_uuid) &&
                uuid_compare(client->uuid, receiver_uuid) != 0) {
                send_message_to_user(cmd, server, client);
                write(client->sfd, "220 Message sent to \"", 21);
                write(client->sfd, cmd[1], strlen(cmd[1]));
                write(client->sfd, "\"\n", 2);
            } else
                write(client->sfd, "303 User uuid invalid\n", 22);
        } else
            write(client->sfd, "302 Invalid arguments\n", 22);
    } else
        write(client->sfd, "300 Please login with /login\n", 29);
}