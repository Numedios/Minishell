# Compilation flags
ifeq ($(DMEM),1)
MEM 		= -fsanitize=address
endif

ifeq ($(DTHREAD),1)
MEM 		= -fsanitize=thread
endif

#==============================================================================#
#                                   TARGETS                                    #
#==============================================================================#

NAME = minishell

#==============================================================================#
#                                   COMMANDS                                   #
#==============================================================================#

CC = gcc
CFLAGS = -g
DFLAGS = -MMD
MKDIR = mkdir -p
RM = rm -f
MAKE_SILENT = make --no-print-directory
INC_LIBFT = -L libft -lft

#==============================================================================#
#                                    COLORS                                    #
#==============================================================================#

PURPLE = \033[35m
GREEN = \033[32m
YELLOW = \033[33m
END = \033[0m

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC_DIR = src/
HEADER_DIR = include/
OBJ_DIR = obj/

#==============================================================================#
#                                   SOURCES                                    #
#==============================================================================#

SRC = main.c \
		libft.c	\
		split.c \
		supp.c \
		free.c \
		quote.c \
		find_commande.c \
		find_input_output.c \
		clean_split_arg.c \
		create_maillons.c \
		split_list.c \
		list_split_elem.c \
		list_input_output.c \
		builtin_echo.c \
		builtin_cd.c  \
		builtin_pwd.c \
		builtin_env.c  \
		builtin_export.c  \
		builtin_exit.c  \
		builtin_unset.c  \
		parsing.c  \
		utils_parsing_bis.c  \
		garbage_collector.c \
		signals.c\
		replace_dollar.c\
		clear_maillons.c \
		list_maillons.c \
		parsing_input.c \
		pipex.c \
		pipex2.c \
		split_pipex.c \
		cmd_to_path.c \
		utils_parsing.c \
		create_heredoc.c \
		replace_dollar_2.c \
		ft_itoa.c \
		free_garbage.c \
		dollars_interrogation.c \
		export_utils.c \
		split2.c \
		pipe_de_2.c \
		security.c  \
		utils_pipex.c \
		child.c \
		utilis_pipex_zak.c \
		check_space.c \
		check_one.c \
		dollars_utils.c \
		delete_quote.c \

#==============================================================================#
#                                   HEADERS                                    #
#==============================================================================#

HEAD_NAME = $(HEADER_DIR)/minishell.h
INC = -I./$(HEADER_DIR)

#==============================================================================#
#                                   OBJECTS                                    #
#==============================================================================#

OBJ = $(addprefix ${OBJ_DIR}, ${SRC:.c=.o})

#==============================================================================#
#                                   MAKEFILE                                   #
#==============================================================================#

all : $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEAD_NAME)
	mkdir -p ${@D}
	$(CC) $(CFLAGS) $(DFLAGS) $(MEM) $(INC) -c $< -o $@

$(NAME) : $(OBJ)
	echo "$(YELLOW)Making Minishell$(END)"
	$(CC) $(CFLAGS) $(OBJ) $(INC) $(MEM) -o $(NAME) -lreadline -g
	echo "$(GREEN)Done$(END)"

bonus : all

clean :
	echo "$(PURPLE)Cleaning Minishell's objects...$(END)"
	$(RM)r $(OBJ_DIR)
	echo "$(GREEN)Done$(END)"

fclean : clean
	echo "$(PURPLE)Cleaning Minishell...$(END)"
	$(RM) $(NAME)
	echo "$(GREEN)Done$(END)"

re : fclean
	$(MAKE_SILENT) all

.PHONY : all clean fclean re bonus
.SILENT :
