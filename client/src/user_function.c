/*
** EPITECH PROJECT, 2019
** temp
** File description:
** temp
*/

#include "client_header.h"
#include "my_map.h"
#include "features_map.h"
#include <stdio.h>
#include <string.h>

void recover_user_uuid(string_t reply, client_information_t *client_info)
{
    char *tmp = strdup(reply.m_content);
    char *uuid = get_next(&tmp);
    char *user_name = get_next(&tmp);

    client_event_loggedin(uuid, user_name);
}

void user_logout(string_t reply, client_information_t *client_info)
{
    char *tmp = strdup(reply.m_content);
    char *uuid = get_next(&tmp);
    char *user_name = get_next(&tmp);

    client_event_loggedout(uuid, user_name);
}

static void command_parsing(string_t reply, client_information_t *client_info,
    int reply_code)
{
    map_t create_parsing = init_map((item_cstr_t *)create_cmd, 5);
    map_t passive_cmd = init_map((item_cstr_t *)passive_protocol, 13);
    create_fun func;
    create_fun fun;

    if (create_parsing.find_that(&create_parsing, reply_code)
        and (func = (create_parsing.get_value(&create_parsing, reply_code)))) {
        func(client_info, reply, reply_code);
    } else if (passive_cmd.find_that(&passive_cmd, reply_code)
    and (fun = (passive_cmd.get_value(&passive_cmd, reply_code)))) {
        fun(client_info, reply, reply_code);
    } else {
        event_user(reply_code, reply);
    }
}

void continue_command(string_t reply, client_information_t *client_info,
    int reply_code)
{
    map_t unauthorized = init_map((item_cstr_t *)server_error, 13);
    map_t sub = init_map((item_cstr_t *)subscibe_cmd, 3);
    unauthorized_fun func;
    sub_fun fun;
    char *tmp = strdup(reply.m_content);
    char *one;

    if (unauthorized.find_that(&unauthorized, reply_code)
        and (func = (unauthorized.get_value(&unauthorized, reply_code)))) {
        func();
    } else if (sub.find_that(&sub, reply_code)
    and (fun = (sub.get_value(&sub, reply_code)))) {
        one = get_next(&tmp);
        fun(one, get_next(&tmp));
    } else {
        command_parsing(reply, client_info, reply_code);
    }
}

void check_reply_code(int reply_code, char *str,
    client_information_t *cl, char *tmp)
{
    map_t function_map = init_map((item_cstr_t *)features_str, 3);
    map_t error_map = init_map((item_cstr_t *)error_feature, 5);
    fun func;
    error_fun err;

    if (function_map.find_that(&function_map, reply_code)
        and (func = function_map.get_value(&function_map, reply_code)) !=
        NULL) {
        func(init_str(str), cl);
    } else if (error_map.find_that(&error_map, reply_code)
        and (err = error_map.get_value(&error_map, reply_code)) !=
        NULL) {
        err(get_next(&tmp));
    } else {
        continue_command(init_str(str), cl, reply_code);
    }
}