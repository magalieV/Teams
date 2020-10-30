/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list
*/

#include "my_ftp.h"

int sub_list_len(list_sub_t *begin)
{
    int i = 0;

    for (list_sub_t *tmp = begin; tmp; tmp = tmp->next)
        i++;
    return (i);
}

list_sub_t *delete_sub_node_uuid(list_sub_t *begin, uuid_t uuid)
{
    list_sub_t *ret = begin;
    if (sub_list_len(begin) == 1) {
        free(begin);
        return (NULL);
    }
    for (list_sub_t *tmp = begin; tmp; tmp = tmp->next) {
        if (uuid_compare(uuid, tmp->uuid))
            continue;
        if (tmp->next) {
            tmp->next->prev = tmp->prev;
            ret = tmp->next;
        }
        if (tmp->prev) {
            tmp->prev->next = tmp->next;
            ret = tmp->prev;
        }
        free(tmp);
        break;
    }
    return (ret);
}

list_sub_t *delete_sub_node(list_sub_t *begin)
{
    list_sub_t *ret = NULL;

    if (begin->next) {
        begin->next->prev = begin->prev;
        ret = begin->next;
    }
    if (begin->prev) {
        begin->prev->next = begin->next;
        ret = begin->prev;
    }
    free(begin);
    return (ret);
}

list_sub_t *create_sub_node(list_sub_t *begin, uuid_t uuid)
{
    list_sub_t *new_st = malloc(sizeof(list_sub_t));

    new_st->next = NULL;
    uuid_copy(new_st->uuid, uuid);
    if (begin == NULL) {
        new_st->prev = NULL;
    } else {
        new_st->prev = begin;
        begin->next = new_st;
    }
    return (new_st);
}

list_t *create_nod(list_t *begin, char *arg)
{
    list_t *new_st = malloc(sizeof(list_t));

    new_st->next = NULL;
    new_st->arg = strdup(arg);
    if (begin == NULL) {
        new_st->prev = NULL;
    } else {
        new_st->prev = begin;
        begin->next = new_st;
    }
    return (new_st);
}