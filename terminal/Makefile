# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 17:26:21 by zhamdouc          #+#    #+#              #
#    Updated: 2022/12/21 20:44:12 by zhamdouc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server

CLIENT = client

SRC_SERVER = ft_serveur.c\

SRC_CLIENT = ft_client.c\

SRC_PRINTF = ft_printf/f_pba.c\
			 ft_printf/ft_printf.c\
			 ft_printf/ft_putnbr_base.c\
			 ft_printf/ft_putnbr_printf.c\
			 ft_printf/ft_strlen.c\

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ)
		 $(CC) $(CFLAGS) -o $(SERVER) $(SRC_SERVER) $(SRC_PRINTF)

$(CLIENT): $(OBJ)
		   $(CC) $(CFLAGS) -o $(CLIENT) $(SRC_CLIENT) $(SRC_PRINTF)

clean:
		rm -rfv $(OBJ)

fclean: clean
		rm -rfv $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re