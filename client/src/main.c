/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include "client_header.h"

static void inline help(void)
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\tip\tis the server ip adress on wich the server "
    "socket listens\n");
    printf("\tport\tis the port number on wich the server socket listens\n");
}

void error_message(string_t *message)
{
    if (message->empty(message))
        return;
    fprintf(stdout, "%s%s%s\n", C_RED, message->content(message), C_RESET);
    message->destroy(message);
}

int main(int ac, char *argv[])
{
    string_t str;

    if (ac < 2 or ac > 3) {
        str = init_str("\t[Invalid number of arguments]\n");
        error_message(&str);
        help();
        return (84);
    } else if (ac == 2 and strcmp(argv[1], "-help") == 0) {
        help();
        return (0);
    }
    run_client(argv);
    return (0);
}