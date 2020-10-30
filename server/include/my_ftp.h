/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** my_ftp.h
*/

#ifndef MY_FTP_H_
#define MY_FTP_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <uuid/uuid.h>
#include <dirent.h>
#include <signal.h>
#include "../../libs/myteams/logging_server.h"

typedef enum use_s
{
    TEAM,
    CHANNEL,
    THREAD,
    REPLY
} use_t;

typedef struct team_s team_t;
typedef struct channel_s channel_t;
typedef struct thread_s thread_t;
typedef struct reply_s reply_t;

struct team_s {
    struct team_s *next;
    struct team_s *prev;
    uuid_t uuid;
    uuid_t creator;
    time_t creation_time;
    char *name;
    char *description;
    channel_t *channel;
};

struct channel_s {
    struct channel_s *next;
    struct channel_s *prev;
    uuid_t uuid;
    uuid_t creator;
    time_t creation_time;
    char *name;
    char *description;
    thread_t *thread;
};

struct thread_s {
    struct thread_s *next;
    struct thread_s *prev;
    uuid_t uuid;
    uuid_t creator;
    time_t creation_time;
    char *title;
    char *message;
    reply_t *reply;
};

struct reply_s {
    struct reply_s *next;
    struct reply_s *prev;
    uuid_t uuid;
    uuid_t creator;
    time_t creation_time;
    char *body;
};

typedef struct list_s {
    struct list_s *next;
    struct list_s *prev;
    char *arg;
} list_t;

typedef struct list_sub_s
{
    struct list_sub_s *next;
    struct list_sub_s *prev;
    uuid_t uuid;
} list_sub_t;

typedef struct s_client
{
    uuid_t uuid;
    int sfd;
    bool isConnected;
    char **cmd;
    char *username;
    list_sub_t *sub;
    use_t use_value;
    uuid_t use_team;
    uuid_t use_channel;
    uuid_t use_thread;
} t_client;

typedef struct clientlist_node
{
    t_client *client;
    struct clientlist_node *next;
} clientlist_node_t;

typedef clientlist_node_t *client_list_t;

typedef struct s_server
{
    int socket;
    struct sockaddr_in server_configuration;
    client_list_t client_list;
    team_t *team_list;
    fd_set active_fd_set;
    fd_set read_fd_set;
    fd_set write_fd_set;
} t_server;

/* server functions */
int help(char **, t_server *, t_client *);
int login(char **, t_server *, t_client *);
int logout(char **, t_server *, t_client *);
int users(char **, t_server *, t_client *);
int user(char **, t_server *, t_client *);
int send_function(char **, t_server *, t_client *);
int messages(char **, t_server *, t_client *);
int subscribe(char **, t_server *, t_client *);
int subscribed(char **, t_server *, t_client *);
int unsubscribe(char **, t_server *, t_client *);
int use(char **, t_server *, t_client *);
int create(char **, t_server *, t_client *);
int list(char **, t_server *, t_client *);
int info(char **, t_server *, t_client *);

/* server.c */
t_server *init_server(int, char *, char *);
t_client *init_client(int, char *);
int create_server(t_server *);
int start_server(t_server *);
int client_manager(t_server *, int);
int server_functions(char **, t_client *, t_server *);
int exit_client(t_server *, t_client *);


/* client_linked_list.c */
t_client *double_list_get_elem_at_position(client_list_t, int);
bool double_list_add_elem_at_front(client_list_t *, t_client *);
bool double_list_del_elem_at_position(client_list_t *, int);
bool double_list_del_elem_at_front(client_list_t *);
unsigned int double_list_get_size(client_list_t);
void double_list_dump(client_list_t);

/* utils.c */
int count(char *, char);
int count_once(char *, char);
char *clear_str(char *, char);
size_t strlen_n(char *, int, char);
char **split(char *, char);
int tablen(char **);
int my_strlen(char *);
char *my_strcat(char *, char *);
void end_server(int);

/* parsing.c */
int tablen(char **);
char *str_to_upper(char *);
int parsing_manager(t_server *, int);
int server_functions(char **, t_client *, t_server *);
char **get_comm_arg(char *);
int nb_dquote(char *);
bool is_right_arg(char *);
char **list_to_array(list_t *);
int parse_comm(char *, t_client *, t_server *);
int print_team(team_t *);

/* getters.c */
team_t *get_team(t_server *, uuid_t);
channel_t *get_channel(t_server *, uuid_t, uuid_t);
thread_t *get_thread(t_server *, uuid_t, uuid_t, uuid_t);
t_client *get_user_by_uuid(t_server *, char *);
bool is_team_exist(t_server *, uuid_t);

/* event.c */
void thread_created_event(t_server *, t_client *, thread_t *);
void channel_created_event(t_server *, t_client *, channel_t *);
void new_thread_message_event(t_server *, t_client *, reply_t *);
void new_private_message_event(t_client *, t_client *, char *);
int create_tris(char **, t_server *, t_client *);

/* login.c */
bool is_user_exist_bis(t_server *, uuid_t);

/*subscribed */
bool is_subscribed(t_client *, uuid_t);
char *get_conversation(char *, char *);
t_client *get_user_by_uuid(t_server *, char *);

/*list.c */
list_sub_t *delete_sub_node_uuid(list_sub_t *, uuid_t);
list_sub_t *delete_sub_node(list_sub_t *);
list_sub_t *create_sub_node(list_sub_t *begin, uuid_t);
list_t *create_nod(list_t *, char *);
void free_list(list_t *);

/* create_node */
team_t *create_team_nod(t_client *, team_t *, char *, char *);
channel_t *create_channel_nod(t_client *, channel_t *, char *, char *);
thread_t *create_thread_nod(t_client *, thread_t *, char *, char *);
reply_t *create_reply_nod(t_client *, reply_t *, char *, uuid_t);

void free_sub_list(list_sub_t *);
list_sub_t *get_first_elem(list_sub_t **);
client_list_t restore_data(void);
void create_client_node(client_list_t *, char *);
team_t *parse_teams_str(char *);
team_t *restore_teams(void);
int create_reply(t_client *, t_server *, char *);

/*info.c */
int info_team(char **, t_server *, t_client *);
int list_teams(t_server *, t_client *);
char *split_by_len(char *, int, int);
char *get_timestamp(void);
#endif /* !MY_FTP_H_ */