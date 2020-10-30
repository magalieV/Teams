/*
** EPITECH PROJECT, 2019
** features_map
** File description:
** features_map
*/

#ifndef __NWP_MYTEAMS_2019_FEATURES_MAP_H__
#define __NWP_MYTEAMS_2019_FEATURES_MAP_H__

#include "my_map.h"
#include <stdlib.h>
#include "client_header.h"
#include "../../libs/myteams/logging_client.h"

const item_cstr_t features_str[] = {
    {210, &recover_user_uuid},
    {215, &user_logout},
    {250, NULL},
    {-1, NULL}
};

const item_cstr_t error_feature[] = {
    {303, &client_error_unknown_user},
    {304, &client_error_unknown_team},
    {305, &client_error_unknown_channel},
    {306, &client_error_unknown_thread},
    {-1, NULL}
};

const item_cstr_t server_error[] = {
    {300, &client_error_unauthorized},
    {301, &client_error_unauthorized},
    {302, &client_error_unauthorized},
    {308, &client_error_unauthorized},
    {307, &client_error_already_exist},
    {316, &client_error_unauthorized},
    {311, &client_error_unauthorized},
    {331, &client_error_unauthorized},
    {341, &client_error_unauthorized},
    {400, &client_error_unauthorized},
    {401, &client_error_unauthorized},
    {402, &client_error_unauthorized},
    {403, &client_error_unauthorized},
    {-1, NULL}
};

const item_cstr_t subscibe_cmd[] = {
    {230, &client_print_subscribed},
    {240, &client_print_unsubscribed},
    {-1, NULL}
};

const item_cstr_t create_cmd[] = {
    {255, &cmd_parser},
    {256, &cmd_parser},
    {257, &cmd_parser},
    {258, &cmd_parser},
    {-1, NULL}
};

const item_cstr_t passive_protocol[] = {
    {201, &get_passive_information},
    {202, &get_passive_information},
    {225, &get_passive_information},
    {235, &get_passive_information},
    {236, &get_passive_information},
    {260, &get_passive_information},
    {261, &get_passive_information},
    {262, &get_passive_information},
    {263, &get_passive_information},
    {265, &get_passive_information},
    {266, &get_passive_information},
    {267, &get_passive_information},
    {268, &get_passive_information},
    {-1, NULL}
};

#endif //__NWP_MYTEAMS_2019_FEATURES_MAP_H__
