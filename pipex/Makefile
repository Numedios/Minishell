NAME = pipex

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCPATH = src/
SRC = main.c \
		parsing.c \
		split_pipex.c \
		libft.c	\
		utils_libft.c \
		utils_tab.c \
		utils_parsing.c \
		create_path.c \
		create_path_utils.c \
		pipex.c \
		create_pipes.c \
		heredoc.c \
		get_next_line.c \
		get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@echo "\033[36mMaking Pipex \033[0m"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[32mDone\033[0m"

%.o : $(SRCPATH)%.c
	@$(CC) $(CFLAGS) -c $^

bonus : all

clean :
	@echo "\033[35mCleaning Pipex objects...\033[0m"
	@rm -f $(OBJ)
	@echo "\033[32mDone\033[0m"

fclean : clean
	@echo "\033[35mCleaning Pipex...\033[0m"
	@rm -f $(NAME)
	@echo "\033[32mDone\033[0m"

re : fclean
	make all

.PHONY : all clean fclean re bonus