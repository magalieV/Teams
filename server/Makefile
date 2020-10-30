##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## main Makefile
##

NAME	=	myteams_server

SRC		=	src/main.c	\
			src/utils.c	\
			src/utils_bis.c	\
			src/parsing.c	\
			src/server.c	\
			src/client_linked_list.c	\
			src/client_linked_list_bis.c	\
			src/server_functions/help.c	\
			src/server_functions/login.c	\
			src/server_functions/logout.c	\
			src/server_functions/users.c	\
			src/server_functions/user.c	\
			src/server_functions/send.c	\
			src/server_functions/messages.c	\
			src/server_functions/subscribe.c	\
			src/server_functions/subscribed.c	\
			src/server_functions/unsubscribe.c	\
			src/server_functions/use.c	\
			src/server_functions/create.c	\
			src/server_functions/list.c	\
			src/server_functions/info.c	\
			src/server_functions/info_bis.c	\
			src/list.c	\
			src/parser.c	\
			src/server_functions/event.c	\
			src/getters.c	\
			src/create_node.c	\
			src/create_node_bis.c	\

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-I./include/ -g3 -luuid -L../libs/myteams -lmyteams

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			gcc -o $(NAME) $(SRC) $(CFLAGS)
			mv ${NAME} ../${NAME}

clean	:
			rm -f $(OBJ)

fclean	:	clean
			rm -f ../$(NAME)

re 		:	fclean all