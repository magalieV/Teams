/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** test
*/

#include "my_ftp.h"

int parse_comm(char *str, t_client *client, t_server *server)
{
    char **tab = NULL;
    int return_value = 0;

    if (nb_dquote(str) % 2 != 0) {
        return (403);
    }

    tab = get_comm_arg(str);
    return_value = server_functions(tab, client, server);
    for (int i = 0; tab && tab[i]; i++)
        free(tab[i]);
    free(tab);
    return (return_value);
}

char **get_comm_arg(char *str)
{
    const char *sep = "\"";
    list_t *list = NULL;

    for (char *tmp = strtok(str, sep); tmp != NULL; tmp = strtok(NULL, sep)) {
        if (is_right_arg(tmp))
            list = create_nod(list, tmp);
    }

    for (; list && list->prev; list = list->prev);
    return (list_to_array(list));
}

int nb_dquote(char *str)
{
    int nb = 0;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '\"') {
            nb++;
        }
    }

    return (nb);
}

bool is_right_arg(char *str)
{
    int cpt = 0;

    if (!strlen(str))
        return (false);
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '\t' || str[i] == ' ') {
            cpt++;
        }
    }
    if (cpt == strlen(str))
        return (false);
    return (true);
}

char **list_to_array(list_t *list)
{
    int len = 0;
    int i = 0;
    char **tab = NULL;

    for (list_t *tmp = list; tmp; tmp = tmp->next, len++);
    tab = malloc(sizeof(char *) * (len + 1));
    tab[len] = NULL;
    for (list_t *tmp = list; tmp; tmp = tmp->next, i++) {
        if (!i && strlen(tmp->arg) && tmp->arg[strlen(tmp->arg) - 1] == ' ') {
            tab[i] = malloc(sizeof(char) * (strlen(tmp->arg)));
            memcpy(tab[i], tmp->arg, strlen(tmp->arg) - 1);
            tab[i][strlen(tmp->arg) - 1] = 0;
        } else {
            tab[i] = malloc(sizeof(char) * (strlen(tmp->arg) + 1));
            memcpy(tab[i], tmp->arg, strlen(tmp->arg));
            tab[i][strlen(tmp->arg)] = 0;
        }
    }
    free_list(list);
    return (tab);
}