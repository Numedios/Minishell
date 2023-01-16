
#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
#include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <limits.h>

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
    struct input_output	*prev;
}			t_input_output;

typedef struct  maillons
{
    struct input_output  *output;
    char        *command;
    char        **args;
    struct maillons  *next;
     struct maillons  *prev;
}       t_maillons;

typedef struct garbage
{
    char    **split;
    struct split_elem    *split__lst;
    struct input_output  *output;
    struct maillons     *maillons;
}       t_garbage;

typedef struct index
{
    int         j;
   	int         a;
}       t_index;

typedef struct two_pipe
{
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	int		i;
	int		status;
}       two_pipe;

typedef struct for_dollar
{
	int len_tab;
    int len_value;
    int new_len;
    char *new_tab;
    int i;
    int pos;
    int pos_new_env;
    int pos_tab;
}       for_dollar;

# define BUFFER_SIZE 5

/*      pipe_of_zak     */
int pipex_2(t_maillons  *maillons, char **env);
int find_stdin_2(t_maillons *maillons, int * fd_in, two_pipe *two_pipe);
int find_stdout_2(t_maillons *maillons, int *fd_out, two_pipe *two_pipe);
void	init(two_pipe *two_pipe);
int	dup_fd(int new_stdin, int new_stdout);

/*  security */
int	check_if_builtin (char **args, char **env);
int check_echo (char **args,int cmp, int i);

/* main.c */

char	*rl_gets();
int		main(int argc, char **argv, char **env);

/* zak */\
/*  built in cd */
int do_cd(char *path);

/*  built in env */
void    do_env(char **env);
char **	my_env(char **env);

/*  built in exit */
int do_exit(char *statut);

/*  built in export */
char	*ft_strchr(const char *s, int c);
int check_if_tab_exist (char *tab, char **env);
char **do_export(char *tab, char **env_copy);
int str_len_env(char *str);

/*  built in pwd */
int do_pwd(void);

/*  built in unset */
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void    do_unset(char *tab, char **env_copy);

/*  signals */
void setup_signal_handlers(void);
void handle_sig(int sig);

/*  utils parsing_bis */
char	*ft_strdup_const(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int	skip_quote (char *line, int i);
int print_tab(char **tab);

/*  parsing */
int str_cmp(char *s1, char *s2);
int parse (char *line);
int quote_close_2(char *str);
int ft_strlen_const(const char *str);

/*  replace dollar */
char *replace_dollar(char *tab, char **new_env);

/* libft.c */

int ft_strlen(char *str);
int		ft_strcmp(char *str, char *str2);
char    *ft_strdup(char *str);
void	ft_putstr_fd(char *s, int fd);

/* split.c */

int		check_sep(char c, char *sep);
int		count_words(char *str, char *sep);
char	*create_word_quote(char *str, char *sep);
char	*create_word_all2(char *str, char *sep);
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
char    **find_argument(t_split_elem *lst);

/* find_input_output.c */

t_input_output  *find_input_output(t_split_elem *lst);

/* free.c */

void    free_split_elem(t_split_elem *lst);
void    ft_free_tab(char **tab);
void    ft_free_split_arg(t_split_elem  **lst);
void    free_input_output(t_input_output *lst);
void    free_input_output_middle(t_input_output **lst, t_input_output **first);
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

t_input_output  *create_input_output(char *name, char *operator, t_input_output *prev);
t_input_output  *lstlast_input_output(t_input_output *lst);
void    add_end_input_output(t_input_output **list, t_input_output *add);


/* list_mailllons.c */

int ft_strlen_maillons(t_maillons *lst);

/* create_split_argc */

int	just_quote(char *str);
int	chek_sep_str(char *str, char *sep);
void	create_word_sep(t_split_elem **lst, char *str, int len);
t_split_elem	**split_redirection(char *str, char *sep);
void redirection(t_split_elem *lst);
void	create_split_arg(t_split_elem **lst);

/* clear_maillons.c */

char    *find_name_sep(t_input_output *lst, char *sep);
int find_if_have_output(t_input_output *lst, char *sep);
void    find_maillon_without_cmd(t_maillons **maillons);

/* create_maillons.c */

t_maillons  *create_maillons(t_split_elem **split, t_maillons *prev);
t_maillons  *lstlast_maillons(t_maillons *lst);
void    add_end_maillons(t_maillons **lst, t_maillons *add);

/* quote.c */

int quote_close(char *str);
void	change_quote(char *str);

/* parsing_input_output.c */

int check_output(t_input_output *output);
int check_input(t_input_output *output);
int check_input_output(t_input_output **input_output);
int check_inputs_outputs(t_maillons *maillons);

/* bultins_echo.c */

int check_option_n(char *str, int *space);
void do_echo(char **arg);

void    cd(char **arg);

/* pipex.c */

int pipex(t_maillons *maillons, char **env);

/*split_pipex.c */

char	**split_pipex(char *path, char sep);
int	ft_strcmp_pipex(char *str, char *search);

/* cmd_to_path.c */

int cmd_to_path(t_maillons *maillons, char **env);

/* create_heredoc.c*/

int	*create_heredoc(char *str);
int heredoc(char *stop);

/* builtins_pwd.c */

void    pwd();

/* get_next_line */

int		check_end(char *line);
char	*ft_strjoin_gnl(char *line, char *buf);
void	get_line(char *line, char *buffer);
char	*get_next_line(int fd);

/*utils_parsing.c */

char	*ft_strjoin_pipex(char *path, char *add);

/* garbage_collector.c  */

void	initialize_garbage(t_garbage *garbage);

/* supp.c */

void ft_print_maillon(t_maillons	*maillons);
void    ft_print_tab(char **tab);
void	ft_print_split_elem(t_split_elem *list);
void	ft_print_input_output(t_input_output *list);
void ft_print_maillons(t_maillons	*maillons);
char	*create_word_and_quote2(char *str, char *sep);

#endif