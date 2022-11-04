SOURCES =	main.c philo.c init.c run.c  actions.c actions_utils.c utils.c \
			monitor_utils.c input.c ft_isdigit.c ft_atoi.c
NAME = philo
OBJS = ${addprefix ${OBJS_PATH}/, ${SOURCES:.c=.o}}
OBJS_PATH = objs
FLAGS = -Wall -Werror -Wextra
CC = cc

# Colors
GREEN = \33[1;32m
L_CYAN = \33[1;36m
L_BLUE = \33[1;34m
L_GREEN = \33[1;92m
L_PURPLE = \33[1;35m
BROWN = \33[1;33m
NC = \033[0m

all:  ${NAME}

${OBJS_PATH}/%.o: %.c
		@ mkdir -p ${OBJS_PATH}
		@ printf "${BROWN}Compiling: $< %10s\r${NC}"
		@ ${CC} ${FLAGS} -c $< -o $@ 

${NAME}: ${OBJS}
		@ ${CC} ${FLAGS} ${OBJS} -lpthread -o $@
		@ echo "\12${GREEN}${NAME} successfully compiled!${NC}"

clean:
		@ rm -rf ${OBJS_PATH}

fclean: clean
		rm -rf ${NAME}

re: fclean all

norma:
		norminette ${SOURCES}

.PHONY: all clean fclean re
