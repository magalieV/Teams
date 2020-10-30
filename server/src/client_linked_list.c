/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server_manager.c
*/

#include "my_ftp.h"

t_client *double_list_get_elem_at_position(client_list_t list, int position)
{
    if (!list)
        return (NULL);
    for (; list; list = list->next) {
        if (list->client->sfd == position)
            break;
    }
    return (list->client);
}

bool double_list_add_elem_at_front(client_list_t *front_ptr, t_client *client)
{
    clientlist_node_t *new = malloc(sizeof(clientlist_node_t));

    if (!new)
        return (false);
    new->client = client;
    new->next = NULL;
    new->next = *front_ptr;
    *front_ptr = new;
    return (true);
}

bool double_list_del_elem_at_position(client_list_t *front_ptr, int position)
{
    client_list_t list = *front_ptr;
    client_list_t list_bis = *front_ptr;
    client_list_t tmp_node;
    int i = 0;

    if (!*front_ptr)
        return (false);
    for (i = 0; list; list = list->next, i++) {
        if (list->client->sfd == position) {
            if (i == 0)
                return (double_list_del_elem_at_front(front_ptr));
            break;
        }
    }
    for (int y = 0; y < i - 1; y++, list_bis = list_bis->next);
    tmp_node = list_bis->next;
    list_bis->next = list_bis->next->next;
    free(tmp_node);
    return (true);
}

bool double_list_del_elem_at_front(client_list_t *front_ptr)
{
    client_list_t tmp_bis = *front_ptr;
    client_list_t tmp = *front_ptr;

    if (!*front_ptr)
        return (false);
    tmp = tmp_bis->next;
    *front_ptr = tmp;
    free(tmp_bis);
    return (true);
}

unsigned int double_list_get_size(client_list_t list)
{
    client_list_t tmp = list;
    int count = 0;

    for (; tmp; tmp = tmp->next, count++);
    return (count);
}