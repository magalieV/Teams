/*
** EPITECH PROJECT, 2019
** init_map
** File description:
** init_map
*/

#include "my_map.h"
#include <stdio.h>
#include <stdlib.h>

static bool find_that(struct map_s *this, int key)
{
    for (int index = 0; this->tab[index].key != -1; index++) {
        if (this->tab[index].key == key) {
            return (true);
        }
    }
    return (false);
}

static void *get_value(struct map_s *this, int key)
{
    for (int index = 0; this->tab[index].key != -1; index++) {
        if (this->tab[index].key == key)
            return (this->tab[index].value);
    }
    return (NULL);
}

map_t init_map(item_cstr_t *tab, unsigned int len)
{
    map_t map;
    unsigned int index;

    map.tab = malloc(sizeof(item_t) * (len + 1));
    for (index = 0; tab[index].key != -1; index++) {
        map.tab[index].key = tab[index].key;
        map.tab[index].value = tab[index].value;
    }
    map.tab[index].key = -1;
    map.tab[index].value = NULL;
    map.find_that = &find_that;
    map.get_value = &get_value;
    return map;
}