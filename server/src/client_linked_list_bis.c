/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** client_linked_list_bis
*/

#include "my_ftp.h"

void double_list_dump(client_list_t list)
{
    printf("Liste des clients connectés :\n");
    for (; list; list = list->next) {
        printf("Client : sfd = %d \n", list->client->sfd);
        printf("Commande recu : \n");
        for (int i = 0; list->client->cmd && list->client->cmd[i]; i++)
            printf("%s\n", list->client->cmd[i]);
        printf("Username : %s\n", list->client->username);
    }
}