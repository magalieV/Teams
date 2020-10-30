##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

all:
		make -C client
		make -C server

client:
		make -C client

server:
		make -C server

clean:
		make clean -C client
		make clean -C server

fclean:
		make fclean -C client
		make fclean -C server

re:
		make re -C client
		make re -C server

.PHONY	:	all clean fclean re client server