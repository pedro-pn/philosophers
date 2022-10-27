SOURCES = main.c philo.c init.c run.c  actions.c actions_utils.c utils.c
NAME = philo
OBJS = ${SOURCES:.c=.o}
FLAGS = -Wall -Werror -Wextra
CC = cc

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

norma:
		norminette ${SOURCES}

.PHONY: all clean fclean re