/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:49:59 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/22 22:04:21 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

# define WHITE_SPACE "\t\n\v\f\r "

typedef struct s_pipes
{
	int	*pipe;
	int	len;
}		t_pipes;

typedef struct split_elem
{
	char				*arg;
	struct split_elem	*next;
}			t_split_elem;

typedef struct input_output
{
	char				*file_name;
	char				*operator;
	struct input_output	*next;
	struct input_output	*prev;
}			t_input_output;

typedef struct maillons
{
	int						heredoc;
	struct input_output		*output;
	char					*command;
	char					**args;
	struct maillons			*next;
	struct maillons			*prev;
}			t_maillons;

typedef struct garbage
{
	char				**split_pipe;
	char				**new_env;
	char				*line;
	struct split_elem	*split_lst;
	struct maillons		*maillons;
	struct s_pipes		*pipes;
}			t_garbage;

typedef struct index
{
	int	j;
	int	a;
}		t_index;

typedef struct quote
{
	int	old_i;
	int	i;
}		t_quote;

typedef struct two_pipe
{
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	int		i;
	int		status;
}		t_two_pipe;

typedef struct t_for_dollar
{
	int		len_tab;
	int		len_value;
	int		new_len;
	char	*new_tab;
	char	*value;
	int		i;
	int		pos;
	int		pos_new_env;
	int		pos_tab;
}		t_for_dollar;

# define BUFFER_SIZE 5

/*  built in cd */

int				do_cd_change_directory(char *path, char **oldpwd);
int				do_cd(char ***new_env, char *path, t_garbage *g);

/* bultins_echo.c */

int				check_option_n(char *str, int *space);
void			do_echo(char **arg);

/*  builtin_env.c */

void			do_env(char **env);
char			**my_env(char **env, t_garbage *garbage);

/*  builtin_exit.c */

long long		ft_atoll_capped(const char *nptr, int *flag, int j, int nb);
void			exit_free(t_garbage *garbage, long long exit_code);
void			do_exit(char *s, t_garbage *garbage);

/*  builtin_export.c */

int				parse_value(char *tab, int i, int a);
int				parse_export(char *tab, int i, int a);
char			*strjoin_and_free(char *s1, char *s2);
char			**do_export(char *tab, char **env_copy, int i, t_garbage *g);

/* bultins_pwd.c */

int				do_pwd(void);

/* bultins_unset.c */

int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			**do_unset(char *tab, char **env_copy, int i, t_garbage *g);

/* check_one.c */

int				after_redirection(char *line);
int				check_parenthesis(char *line);
int				check_1(char *line);

/* check_space.c */

int				check_error_2_space(char *line, char c, char c_bis, int i);
int				check_error_3_space(char *line, char c, char *c_bis, int i);
int				check_error_space(char *line, char c, int i);

/* child.c */

int				check_access(t_maillons *maillons);
int				check_echo(char **args, int cmp, int i, int execute);
int				first_pipe_check(char *line);
int				after_pipe(char *line);
int				only_white_space(char *line_read);

/* clean_split_arg.c */

void			add_el_loop(t_split_elem **d, \
	t_split_elem ***s, t_split_elem ***a);
void			add_el(t_split_elem *lst, \
	t_split_elem **start, t_split_elem *prev);
void			create_split_arg(t_split_elem **lst);

/* clear_maillons.c */

void			free_maillon_middle(t_maillons **lst, t_maillons **first);
int				find_if_have_output(t_input_output *lst, char *sep);
char			*find_s(t_input_output *lst, char *sep);

/* cmd_to_path.c */

char			*get_path(char **envp);
int				check_is_path(char *str);
void			change_cmd(char **str, char **tab);
int				cmd_to_path(t_maillons *maillons, char **env);

/* create_heredoc.c*/

void			create_heredoc(int *pipe_fd);
void			print_minishell_warning_heredoc(char *stop);
int				heredoc(char *stop);

/* create_maillons.c */

t_maillons		*create_maillons(t_split_elem **s, t_maillons *p, t_garbage *g);
t_maillons		*lstlast_maillons(t_maillons *lst);
void			add_end_maillons(t_maillons **lst, t_maillons *add);

/* delete_quote.c */

char			*del_q(char *line, int j, int len);

/* dollars_interrogation.c */

void			new_in_old(t_for_dollar *var, \
	t_index *index, char **new_env, int *skip);
void			new_in_old_interrogation(t_for_dollar *var);
char			*interrogation(char *tab, int skip, t_index index);
char			*do_replace(char *tab, char **new_env, int skip, t_index index);

/* dollars_utils.c */

int				research(int skip, int a, char *tab, char **new_env);
char			*one_dollar_or_more(char *tab, int *i, \
	char **new_env, t_index *index);

/* export_utils */

int				str_len_env(char *str);
char			*ft_strchr(const char *s, int c);
int				parsing_of_export(char *tab, char **env_copy, int *a, int *j);
int				what_to_do(char *tab, char **env);

/* extra_utils */

char			**replace_value(int j, int a, char *tab, char **env);
char			**new_value(int i, int a, char *tab, char **env);
int				which_builtin(char **env, int i, int cmp, t_garbage *g);
int				check_if_exit(char **args, t_garbage *garbage);

/* find_commande.c */

char			*find_command(t_split_elem *lst);
int				count_arg(t_split_elem *lst);
int				find_argument_loop(t_split_elem *lst);
char			**find_argument(t_split_elem *lst, \
	t_garbage *g, int i, int len);

/* find_input_output.c */

int				find_input_output_loop(t_split_elem *lst);
t_input_output	*find_input_output(t_split_elem *lst, t_garbage *g);

/* free_garbage.c */

void			free_garbage_add(t_garbage *garbage);
void			free_garbage(t_garbage *garbage);
void			free_garbage_exit(t_garbage *garbage, int exit_code);
void			free_garbage_and_env(t_garbage *garbage);
void			free_garbage_env_exit(t_garbage *garbage, int exit_code);

/* free_input.c */

void			free_input_output_middle(t_input_output **lst, \
	t_input_output **first);
void			free_inputs_outputs(t_input_output **lst);
void			free_input_output(t_input_output **lst);

/* free.c */

void			free_split_elem(t_split_elem *lst);
void			ft_free_split_arg(t_split_elem **lst);
void			ft_free_tab(char **tab);
void			free_maillon(t_maillons *lst);
void			free_maillons(t_maillons *lst);

/* itoa.c */

char			*ft_itoa(int n);

/* garbage_collector.c */

void			initialize_garbage(t_garbage *garbage, int argc, char **argv);

/* libft.c */

void			s_fd(char *s, int fd);
int				ft_strlen(char *str);
int				ft_strcmp(char *str, char *str2);
char			*ft_strdup(char *str);
int				ft_isdigit(int c);

/* list_input_ouput.c */

t_input_output	*crea_input(char *n, char *o, t_input_output *p, t_garbage *g);
t_input_output	*lstlast_input_output(t_input_output *lst);
void			add_end_input_output(t_input_output **list, \
	t_input_output *add);

/* list_maillons.c*/

int				ft_strlen_maillons(t_maillons *lst);

/* list_split_elem.c */

t_split_elem	*create_split_elem(char	*str);
t_split_elem	*create_split_elem_dup(char	*str);
t_split_elem	*lstlast_split_elem(t_split_elem *lst);
void			add_end_split_elem(t_split_elem	**list, t_split_elem *add);

/* main.c */

int				main(int argc, char **argv, char **env);

/* parsing_input.c  */

int				check_output(t_input_output *output);
int				check_input(t_input_output *output);
int				check_two_input_output(t_input_output *output);

/* parsing.c  */

int				del_quote(char *line, int i, int j);
int				parse(char *line);

/* pipe_de_2.c  */

void			signal_quit_child(int useless);

/* pipex_one.c */

int				find_stdin(t_maillons *maillons);
int				find_stdout(t_maillons *maillons);
int				pipex_one_condition(t_maillons *m, char ***e, \
	t_garbage *g);
int				pipex_one(t_maillons *maillons, \
	char ***env, t_garbage *garbage);

/* pipex.c  */

int				dup_fd(int new_stdin, int new_stdout);
int				pipex(t_maillons *maillons, char ***env, t_garbage *garbage);

/* pipex2.c */

t_maillons		*get_last_maillons(t_maillons *maillons);
int				check_access_two(t_maillons *maillons);
int				pipex_multiple(int len, t_garbage *g, int i, int wstatus);

/* quote.c  */

int				quote_close(char *str);

/* replace_dollar_2.c  */

char			*found_it_delete(char *tab, char **new_env, \
	t_index *index, int *skip);
char			*dollar_inquote_del(char *tab, int *i, \
	char **new_env, t_index *index);
char			*dollar_or_more_del(char *tab, int *i, \
	char **new_env, t_index *index);
char			*delete_dollar(char *tab, char **new_env, int i);

/*replace_dollar.c */

char			*found_it(char *tab, char **new_env, t_index *index, int *skip);
char			*found_dollar_inquote(char *tab, \
	int *i, char **new_env, t_index *index);
char			*replace_dollar(char *tab, char **new_env, int i);

/* security.c*/

int				check_builtin(char **args);
int				check_if_builtin(char **env, \
	char ***new_env, int i, t_garbage *g);

/*signals.c */

void			handle_sig(int sig);
void			setup_signal_handlers(void);

/* split_list.c*/

t_split_elem	*ft_split_list(char *str, char *sep);

/*split_pipex.c*/

int				ft_strcmp_pipex(char *str, char *search);
int				count_world(char *path, char sep);
char			*create_word_pipex(char *path, char sep);
char			**split_pipex(char *path, char sep);

/*split.c  */

int				check_sep(char c, char *sep);

/*split2.c  */

int				is_inquotes(char *str, int pos);
int				check_quote2(char c);
char			*ft_strtab(char *str, int tor, char *sep);
char			**ft_split2(char *str, char *sep);

/* switch_dup.c */

void			sigint_child(int unused);
int				switch_dup2_fd_in(t_maillons *m, t_pipes *pipes, int i);
int				switch_dup2_fd_out(t_maillons *maillons, t_pipes *pipes, int i);
int				check_if_tab_exist(char *tab, char **env);
int				pipex_one_dup(t_maillons **maillons);

/* utils_clean_split_arg.c  */

int				chek_sep_str(char *str, char *sep);
void			create_word_sep(t_split_elem **lst, char *str, int len);
void			handle_redirection(t_split_elem **add, char **str);
void			split_redirection_quote(char **str);
t_split_elem	**split_redirection(char *str, char *sep);

/* utils_create_heredoc.c */

void			sigint_heredoc(int unused);
void			find_all_heredoc_loop(t_maillons **maillons, int *copy_fd);
void			find_all_heredoc(t_maillons *maillons);

/*  utils_main.c  */

char			*rl_gets(void);
t_maillons		*loop_create_maillons(char *line, t_garbage *garbage, int i);
void			end_quote_add(t_garbage *g, int *i);
void			end_quote(t_garbage *garbage);

/* utils_parsing_bis.c  */

int				skip_quote(char *line, int i);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup_const(const char *s, t_garbage *g);
int				check_dollar(char *line);

/* utils_parsing_bisbis.c */

char			*ft_strjoin_pipex(char *path, char *add);
int				ft_strlen_const(const char *str);
int				str_cmp(char *s1, char *s2);

/* utils_parsing_input.c  */

int				check_input_output2(t_input_output **input_output, \
t_input_output *input, t_input_output *output, t_input_output *first);

/* utils_parsing.c */

int				quote_close_2(char *str);
char			*apply_delete(int i, int skip, char *tab);

/* utils_pipex_two.c */

void			pipex_multiple_check(t_garbage *g, t_maillons *cmd, t_maillons *tmp);
void			pipex_multiple_free(t_garbage *garbage);
void			pipex_multiple_close_pipe(t_garbage *garbage, int len, int i);
void			handle_child_process(int i, int len, t_garbage *g, \
t_maillons *cmd, t_maillons *tmp);

/* utils_pipex.c  */

void			free_all_pipes(int argc, t_pipes *pipes);
void			create_pipe(int *pipes, int i);
int				*create_pipes(int len);
t_pipes			*create_all_pipes(int len);

/* utils_split.c  */

int				check_sep2(char c, char *sep);
int				count_words2(char *str, char *sep);
int				ft_stablen(char *str, int tor, char *sep);

/* supp.c */

void			ft_print_maillon(t_maillons *maillons);
void			ft_print_tab(char **tab);
void			ft_print_split_elem(t_split_elem *list);
void			ft_print_input_output(t_input_output *list);
void			ft_print_maillons(t_maillons *maillons);
char			*create_word_and_quote2(char *str, char *sep);
void			ft_print_garbage(t_garbage	*garbage);

#endif
