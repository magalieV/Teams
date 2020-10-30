/*
** EPITECH PROJECT, 2019
** my_map
** File description:
** my_map
*/

#ifndef __NWP_MYTEAMS_2019_MY_MAP_H__
#define __NWP_MYTEAMS_2019_MY_MAP_H__

#include "client_header.h"

typedef struct item_cstr_s {
    int key;
    void *value;
} item_cstr_t;

typedef struct item_s {
    int key;
    void *value;
} item_t;

typedef struct map_s {
    item_t *tab;
    bool (*find_that)(struct map_s *this, int key);
    void *(*get_value)(struct map_s *this, int key);
} map_t;

map_t init_map(item_cstr_t *tab, unsigned int len);

#endif //__NWP_MYTEAMS_2019_MY_MAP_H__
