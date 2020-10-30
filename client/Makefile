##
## EPITECH PROJECT, 2019
## make file
## File description:
## make file
##

RM		=	rm -f

TOOLS_PATH	=	src/tools/

CLASS_PATH	=	class/src/

SRC_TOOLS	=	$(TOOLS_PATH)convert.c	\
				$(TOOLS_PATH)memory.c	\

SRCS_CLASS	=	$(CLASS_PATH)my_string.c	\
				$(CLASS_PATH)string_function.c	\
				$(CLASS_PATH)string_init_getter.c	\
				$(CLASS_PATH)string_init_setter.c	\
				$(CLASS_PATH)string_operator.c	\
				$(CLASS_PATH)init_map.c	\

SRC		=	src/main.c	\
			src/run_client.c	\
			src/check_new_input.c	\
			src/user_function.c	\
			src/create_cmd.c	\
			$(SRC_TOOLS)	\
			$(SRCS_CLASS)	\

OBJ		=	$(SRC:.c=.o)

NAME	=	myteams_cli

CC		=	gcc

CFLAGS	+=	-I ./inc/ -I./class/inc/ -g3

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) -I ./inc/ -I ./class/inc/ -g3 -L../libs/myteams -lmyteams
	cp ${NAME} ../${NAME}

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)
			$(RM) ../$(NAME)

re:			fclean all

.PHONY	:	all clean fclean re