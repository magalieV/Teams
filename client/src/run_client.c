/*
** EPITECH PROJECT, 2019
** run_client
** File description:
** run_client
*/

#include "client_header.h"
#include <sys/select.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

bool use_keep_running(bool state, bool value)
{
    static bool keep_running = true;

    if (state == true) {
        keep_running = value;
    }
    return (keep_running);
}

void end_client(int sig)
{
    quit_client(false, 0);
    signal(sig, SIG_IGN);
    use_keep_running(true, false);
    exit(0);
}

static client_information_t init_socket(client_information_t client_info,
    char *argv[])
{
    bzero(&client_info.client_addr, sizeof(client_info.client_addr));
    client_info.client_addr.sin_family = AF_INET;
    client_info.client_addr.sin_addr.s_addr = inet_addr(argv[1]);
    client_info.client_addr.sin_port = htons(atoi(argv[2]));
    return (client_info);
}

static client_information_t init_client(char *argv[])
{
    client_information_t client_info;
    string_t str;

    client_info.input_fd = 0;
    client_info.client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_info.client_fd == -1) {
        str = init_str("\t[Socket creation failed]\n");
        error_message(&str);
        exit(84);
    }
    client_info = init_socket(client_info, argv);
    quit_client(true, client_info.client_fd);
    if (connect(client_info.client_fd,
        (struct sockaddr *)&client_info.client_addr,
            sizeof(client_info.client_addr)) != 0) {
        str = init_str("\t[Connection failed]\n");
        error_message(&str);
        exit(84);
    }
    return client_info;
}

void run_client(char *argv[])
{
    client_information_t client_info;
    fd_set readfd;
    int activity = 0, max_value = 0;

    client_info = init_client(argv);
    signal(SIGINT, end_client);
    while (use_keep_running(false, false)) {
        max_value = set_select(&client_info, &readfd);
        activity = select(max_value + 1, &readfd, NULL, NULL, NULL);
        client_operation(&client_info, &readfd);
    }
}