/*
** EPITECH PROJECT, 2019
** client_header
** File description:
** client_header
*/

#ifndef __MYTEAMS_CLIENT_HEADER_H__
#define __MYTEAMS_CLIENT_HEADER_H__

#define or ||
#define and &&
#define C_RED     "\x1b[31m"
#define C_RESET   "\x1b[0m"

#include "../class/inc/my_string.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

typedef struct client_information_s {
    int client_fd;
    int input_fd;
    struct sockaddr_in client_addr;
} client_information_t;

typedef void (*fun)(string_t, client_information_t *);
typedef int (*error_fun)(char const * id);
typedef int (*unauthorized_fun)(void);
typedef int (*sub_fun)(char const *user_id, char const *team_id);
typedef void (*create_fun)(client_information_t *, string_t, int);

void error_message(string_t *message);
void run_client(char *argv[]);
bool use_keep_running(bool state, bool value);
void client_operation(client_information_t *client_info, fd_set *readfd);
int set_select(client_information_t *client_info, fd_set *readfd);
void recover_user_uuid(string_t reply, client_information_t *client_info);
void run_commands(string_t reply, client_information_t *client_info);
void user_logout(string_t reply, client_information_t *client_info);
void cmd_parser(client_information_t *cl,
    string_t reply, int reply_code);
void get_passive_information(client_information_t *, string_t, int);
char *get_next(char **tmp);
void event_user(int reply_code, string_t reply);
time_t get_time(char **tmp);
void next_event(string_t reply, int reply_code, char **t);
void quit_client(bool state, int fd);
void next_cmd(string_t reply, int reply_code, char **t);
void next_list_cmd(string_t reply, int reply_code, char **t);
void next_cmd_parser(string_t reply, int reply_code, char **t);
void check_reply_code(int reply_code, char *str,
    client_information_t *cl, char *tmp);

#endif //__MYTEAMS_CLIENT_HEADER_H__
