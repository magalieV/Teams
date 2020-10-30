/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** main.c
*/

#include "my_ftp.h"

void arguments_error(int ac, char **av)
{
    if (ac == 2 && (strcmp("-h", av[1]) == 0 ||
        strcmp("--help", av[1]) == 0)) {
        printf("USAGE:  ./myteams_server port\n\n");
        printf("\tport is the port number on which");
        printf("the server socket listens.\n");
        exit(84);
    }
    if (ac != 2) {
        printf("Bad arguments, please make ./myftp -h ");
        printf("or ./myftp --help for usage\n");
        exit(84);
    }
}

int main(int ac, char **av)
{
    t_server *server = NULL;

    arguments_error(ac, av);
    server = init_server(socket(PF_INET, SOCK_STREAM, 0), av[1], av[2]);
    create_server(server);
    start_server(server);

    return (0);
}