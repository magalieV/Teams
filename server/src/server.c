/*
** EPITECH PROJECT, 2020
** PSU_nmobjdump_2019
** File description:
** objdump.c
*/

#include "my_ftp.h"

t_server *init_server(int socket, char *port, char *hdir)
{
    t_server *server = malloc(sizeof(t_server));

    server->socket = socket;
    server->client_list = NULL;
    server->team_list = NULL;
    server->server_configuration.sin_family = AF_INET;
    server->server_configuration.sin_port = htons(atoi(port));
    server->server_configuration.sin_addr.s_addr = htonl(INADDR_ANY);
    mkdir("private", 0777);

    return (server);
}

t_client *init_client(int sfd, char *wdir)
{
    t_client *client = malloc(sizeof(t_client));

    client->sfd = sfd;
    client->isConnected = false;
    client->use_value = TEAM;
    client->cmd = NULL;
    client->username = NULL;

    return (client);
}

int create_server(t_server *server)
{
    if (server->socket == -1) {
        exit(84);
    }
    if (bind(server->socket, (struct sockaddr *) &server->server_configuration,
            sizeof(server->server_configuration)) == -1) {
        exit(84);
    }
    if (listen(server->socket, 1) == -1) {
        exit(84);
    }
}

int client_manager(t_server *server, int i)
{
    int new_socket = 0;
    int size = 0;
    if (i == server->socket) {
        size = sizeof(server->server_configuration);
        new_socket = accept(server->socket,
        (struct sockaddr *)&server->server_configuration, (socklen_t *)&size);
        if (new_socket <= -1) {
            return (84);
        }
        FD_SET(new_socket, &server->active_fd_set);
        double_list_add_elem_at_front(&server->client_list,
                    init_client(new_socket, ""));
    }
    else {
        parsing_manager(server, i);
    }
}

int start_server(t_server *server)
{
    FD_ZERO(&server->active_fd_set);
    FD_SET(server->socket, &server->active_fd_set);

    signal(SIGINT, end_server);
    while (1) {
        server->read_fd_set = server->active_fd_set;
        server->write_fd_set = server->write_fd_set;
        select(FD_SETSIZE, &server->read_fd_set, &server->write_fd_set,
                NULL, NULL);
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &server->read_fd_set)) {
                client_manager(server, i);
            }
        }
    }
    close(server->socket);
}