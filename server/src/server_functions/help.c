/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** help.c
*/

#include "my_ftp.h"

int help(char **cmd, t_server *server, t_client *client)
{
    if (tablen(cmd) == 1) {
        if (!client->isConnected)
            write(client->sfd, "300 Please login with /login\n", 29);
        else {
            write(client->sfd, "200 Help message\n", 18);
            write(client->sfd, "The following commands are recognized :\n",
                    40);
            write(client->sfd, "/help /login /logout /user /users /send ", 40);
            write(client->sfd, "/messages /subscribe\n", 21);
            write(client->sfd, "/subscribed /unsubscribe /use /create ", 38);
            write(client->sfd, "/list /info\n", 12);
        }
    } else
        write(client->sfd, "302 Invalid arguments.\n", 23);
}