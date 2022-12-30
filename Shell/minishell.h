
#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WHITE_SPACE "\t\n\v\f\r "

typedef struct  split_elem
{
    char				*arg;
   	struct split_elem	*next;
}       t_split_elem;


typedef struct input_output
{
    char				*file_name;
    char				*operator;
    struct input_output	*next;
}			t_input_output;

typedef struct  maillons
{
    struct input_output  *output;
    char        *command;
    struct split_elem        *args;
    struct maillons  *next;
}       t_maillons;

typedef struct garbage
{
    char    **split;
    struct split_elem    *split__lst;
    struct input_output  *output;
    struct maillons     *maillons;
}       t_garbage;

# define BUFFER_SIZE 5

/* main.c */

char	*rl_gets();
int		main(int argc, char **argv, char **env);

/* libft.c */

int ft_strlen(char *str);
int		ft_strcmp(char *str, char *str2);
char    *ft_strdup(char *str);

/* split.c */

int		check_sep(char c, char *sep);
int		count_words(char *str, char *sep);
char	*create_word_quote(char *str, char *sep);
char	*create_word_all(char *str, char *sep);
char	*create_word(char *str, char *sep);
char	**ft_split(char *str, char *sep);

/* split_list.c */

char	*create_word_list(char *str, char *sep);
t_split_elem	*ft_split_list(char *str, char *sep);

/* find_output.c */

int     is_white_space(char c);
char	*find_output(char **tab);

/* find_command.c */

char    *find_command(t_split_elem *lst);
t_split_elem    *find_argument(t_split_elem *lst);

/* find_input_output.c */

t_input_output  *find_input_output(t_split_elem *lst);

/* free.c */

void    free_split_elem(t_split_elem *lst);
void    ft_free_tab(char **tab);
void    ft_free_split_arg(t_split_elem  **lst);
void    free_input_output(t_input_output *lst);
void    free_inputs_outputs(t_input_output **lst);
void    free_maillon(t_maillons *lst);
void    free_maillons(t_maillons **lst);

/* list_split_elem.c */

t_split_elem	*create_split_elem(char	*str);
t_split_elem	*create_split_elem_dup(char	*str);
t_split_elem	*lstlast_split_elem(t_split_elem *lst);
void	add_end_split_elem(t_split_elem	**list, t_split_elem *add);
void    free_split_elem(t_split_elem *lst);
void ft_strjoin_list(t_split_elem *list, t_split_elem **add, t_split_elem **first);

/* list_input_output.c */

t_input_output  *create_input_output(char *name, char *operator);
t_input_output  *lstlast_input_output(t_input_output *lst);
void    add_end_input_output(t_input_output **list, t_input_output *add);

/* create_split_argc */

int	just_quote(char *str);
int	chek_sep_str(char *str, char *sep);
void	create_word_sep(t_split_elem **lst, char *str, int len);
t_split_elem	**split_redirection(char *str, char *sep);
void redirection(t_split_elem *lst);
void	create_split_arg(t_split_elem **lst);

/* create_maillons.c */

t_maillons  *create_maillons(t_split_elem **split);
t_maillons  *lstlast_maillons(t_maillons *lst);
void    add_end_maillons(t_maillons **lst, t_maillons *add);

/* quote.c */

int quote_close(char *str);
void	change_quote(char *str);

/* bultins_echo.c */

int check_option_n(char *str, int *space);
void echo(char **arg);

/* bultins_echo.c */

void    cd(char **arg);

/* builtins_pwd.c */

void    pwd();

/* garbage_collector.c  */

void	initialize_garbage(t_garbage *garbage);

/* supp.c */

void    ft_print_tab(char **tab);
void	ft_print_split_elem(t_split_elem *list);
void	ft_print_input_output(t_input_output *list);
void ft_print_maillons(t_maillons	*maillons);

#endif