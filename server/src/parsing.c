/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** parsing.c
*/

#include "my_ftp.h"

int tablen(char **tab)
{
    int count = 0;

    for (int y = 0; tab && tab[y]; y++, count++);
    return (count);
}

char *str_to_upper(char *str)
{
    for (int i = 0; str[i]; i++)
        str[i] = toupper(str[i]);
    return (str);
}

char *get_input(char *line)
{
    char *input = NULL;
    int idx = 0;

    input = malloc(sizeof(char *) *(strlen(line + 1)));
    for (int i = 0; line[i]; i++) {
        if (line[i] != '\r' && line[i] != '\n' && line[i] != '\0') {
            input[idx] = line[i];
            idx++;
        }
    }
    input[idx] = '\0';
    return (input);
}

int parsing_manager(t_server *server, int sfd)
{
    t_client *tmp = double_list_get_elem_at_position(server->client_list, sfd);
    FILE *fs = fdopen(dup(fileno(fdopen(sfd, "r"))), "r");
    char *line = NULL;
    int code = 0;
    int r = 0;
    size_t line_nb = 0;

    if (fs == NULL)
        return (84);
    r = getline(&line, &line_nb, fs);
    if (r == -1 || r == 0 || r == 1)
        return (84);
    line[r] = '\0';
    line = get_input(line);
    code = parse_comm(line, tmp, server);
    if (code == 403)
        write(tmp->sfd, "403 Quotes are missing\n", 23);
    if (code == 84) {
        exit_client(server, tmp);
    }
}

int server_functions(char **arg, t_client *client, t_server *server)
{
    int (*server_functions[14])(char **arr, t_server *server,
        t_client *client) = {help, login, logout, user, users,
        send_function, messages, subscribe, subscribed, unsubscribe,
        use, create, list, info};
    char *functions_name[15] = {"/help", "/login", "/logout", "/user",
            "/users", "/send", "/messages", "/subscribe", "/subscribed",
            "/unsubscribe", "/use", "/create", "/list", "/info", NULL};
    if (strcmp(arg[0], "/exit") == 0)
        return (84);
    for (int i = 0; functions_name[i]; i++) {
        if (strcmp(functions_name[i], arg[0]) == 0) {
            return (*server_functions[i])(arg, server, client);
        }
    }
    if (!client->isConnected) {
        write(client->sfd, "300 Please login with /login\n", 29);
        return (300);
    } else if (client->isConnected) {
        write(client->sfd, "301 Unknown command\n", 20);
        return (301);
    }
}