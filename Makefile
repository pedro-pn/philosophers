SOURCES = philosophers.c init.c actions.c utils.c
NAME = philo
OBJS = ${SOURCES:.c=.o}
FLAGS = -g
CC = gcc

all:  ${NAME}

%.o: %.c
	${CC} ${FLAGS} -c $<  -pthread -o $@ 

${NAME}: ${OBJS}
		${CC} ${FLAGS} ${OBJS} -o $@

clean:
		rm -rf ${OBJS}

fclean: clean
		rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re