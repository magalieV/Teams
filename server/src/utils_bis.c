/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** utils_bis
*/

#include "my_ftp.h"

int my_strlen(char *str)
{
    int i = 0;

    for (i = 0; str && str[i]; i++);
    return (i);
}

char *my_strcat(char *dest, char *src)
{
    int a = my_strlen(dest);
    char *new = malloc(sizeof(char) * my_strlen(dest) + my_strlen(src) + 1);

    for (int i = 0; dest != NULL && dest[i]; i++)
        new[i] = dest[i];
    for (int i = 0; src != NULL && src[i]; i++) {
        new[a] = src[i];
        a++;
    }
    new[a] = '\0';
    return (new);
}

void end_server(int sig)
{
    signal(sig, SIG_IGN);
    exit(0);
}

int exit_client(t_server *server, t_client *client)
{
    char uuid[1024];

    FD_CLR(client->sfd, &server->active_fd_set);
    if (client->username != NULL) {
        client->isConnected = false;
        uuid_unparse(client->uuid, uuid);
        server_event_user_logged_out(uuid);
    }
    return (215);
}