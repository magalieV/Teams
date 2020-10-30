/*
** EPITECH PROJECT, 2019
** temp
** File description:
** temp
*/

#include "client_header.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void run_commands(string_t reply, client_information_t *client_info)
{
    int reply_code = 0;
    char *tmp = NULL;
    array list = reply.split(reply, init_str("\n"));

    if (!list)
        return;
    for (unsigned int index = 0; list[index]; index++) {
        1 ? reply_code = atoi(list[index]), tmp = strdup(list[index]) : 0;
        if (reply_code == -1)
            return;
        check_reply_code(reply_code, list[index], client_info, tmp);
    }
}

void quit_client(bool state, int fd)
{
    static int file_desc = 0;

    if (state)
        file_desc = fd;
    else {
        dprintf(file_desc, "/exit\n");
        close(file_desc);
    }
}

void client_operation(client_information_t *client_info, fd_set *readfd)
{
    char *buff = strdup("a");
    string_t reply = init_str("");

    if (FD_ISSET(client_info->client_fd, readfd)) {
        while (buff[0] != '\n' and read(client_info->client_fd, buff, 1) > 0) {
            reply.add(&reply, buff[0]);
        }
        if (reply.empty(&reply)) {
            close(client_info->client_fd);
            use_keep_running(true, false);
        } else {
            run_commands(reply, client_info);
        }
    } else if (FD_ISSET(client_info->input_fd, readfd)) {
        while (buff[0] != '\n' and read(client_info->input_fd, buff, 1) > 0) {
            reply.add(&reply, buff[0]);
        }
        write(client_info->client_fd, reply.m_content, strlen(reply.m_content));
    }
}

int set_select(client_information_t *client_info, fd_set *readfd)
{
    int sd = 0;
    int max_value = client_info->input_fd;

    FD_ZERO(readfd);
    sd = client_info->client_fd;
    max_value = (sd > client_info->input_fd) ? sd : client_info->input_fd;
    FD_SET(sd, readfd);
    FD_SET(client_info->input_fd, readfd);
    return (max_value);
}
