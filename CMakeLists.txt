cmake_minimum_required(VERSION 3.17)
project(NWP_myteams_2019 C)

set(CMAKE_C_STANDARD 11)

include_directories(client/class/inc)
include_directories(client/inc)
include_directories(libs)
include_directories(libs/myteams)
include_directories(server/include)

add_executable(NWP_myteams_2019
        client/class/inc/my_map.h
        client/class/inc/my_string.h
        client/class/src/init_map.c
        client/class/src/my_string.c
        client/class/src/string_function.c
        client/class/src/string_init_getter.c
        client/class/src/string_init_setter.c
        client/class/src/string_operator.c
        client/inc/client_header.h
        client/inc/features_map.h
        client/inc/tools.h
        client/src/tools/convert.c
        client/src/tools/memory.c
        client/src/check_new_input.c
        client/src/create_cmd.c
        client/src/main.c
        client/src/run_client.c
        client/src/user_function.c
        libs/myteams/logging_client.h
        libs/myteams/logging_server.h
        server/include/my_ftp.h
        server/src/server_functions/create.c
        server/src/server_functions/event.c
        server/src/server_functions/help.c
        server/src/server_functions/info.c
        server/src/server_functions/info_bis.c
        server/src/server_functions/list.c
        server/src/server_functions/login.c
        server/src/server_functions/logout.c
        server/src/server_functions/messages.c
        server/src/server_functions/send.c
        server/src/server_functions/subscribe.c
        server/src/server_functions/subscribed.c
        server/src/server_functions/unsubscribe.c
        server/src/server_functions/use.c
        server/src/server_functions/user.c
        server/src/server_functions/users.c
        server/src/client_linked_list.c
        server/src/client_linked_list_bis.c
        server/src/create_node.c
        server/src/create_node_bis.c
        server/src/getters.c
        server/src/list.c
        server/src/main.c
        server/src/parser.c
        server/src/parsing.c
        server/src/server.c
        server/src/utils.c
        server/src/utils_bis.c)
