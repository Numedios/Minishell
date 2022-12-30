# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 16:21:54 by zakariyaham       #+#    #+#              #
#    Updated: 2022/12/30 15:50:52 by zhamdouc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

SRC_PATH = ./srcs/
SRC =   minishell.c builtin_cd.c builtin_echo.c builtin_env.c builtin_exit.c builtin_pwd.c builtin_unset.c builtin_export.c
SRCS = $(addprefix ${SRC_PATH}, ${SRC})

OBJ_PATH	= obj/
OBJ = ${SRC:.c=.o}
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

DEPS = $(addprefix ${OBJ_PATH}, ${SRC:.c=.d})

INC = -I./includes/

FLAGS =  -MMD -MP -lreadline -g3

${NAME} : ${OBJS}
	gcc $(OBJS) -o ${NAME} ${FLAGS}

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p ${OBJ_PATH}
	gcc ${FLAGS} ${INC} -o $@ -c $<

all : ${NAME}

clean :
	rm -rf ${OBJ_PATH}

fclean : clean
	rm -rf ${NAME}

re : fclean all

-include ${DEPS}

.SECONDARY : $(OBJS)

.PHONY: all clean fclean re
