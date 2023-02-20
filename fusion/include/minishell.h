/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:49:59 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/20 14:26:16 by zhamdouc         ###   ########.fr       */
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
}		two_pipe;

typedef struct for_dollar
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
}		for_dollar;

# define BUFFER_SIZE 5

/*      pipe_of_zak     */
int				pipex_2(t_maillons  *maillons, char ***env, t_garbage *garbage);
int				find_stdin_2(t_maillons *maillons, int * fd_in, two_pipe *two_pipe);
int				find_stdout_2(t_maillons *maillons, int *fd_out, two_pipe *two_pipe);
void			init(two_pipe *two_pipe);
int				dup_fd(int new_stdin, int new_stdout);
void			signal_quit_child(int useless);

/*      child.c    */
int				child1(two_pipe *two_pipe, char ***env, t_maillons *maillons, t_garbage *garbage);
int				child2(two_pipe *two_pipe, char ***env, t_maillons *maillons, t_garbage *garbage);
int				check_access(t_maillons *maillons);
int				first_pipe_check(char *line);
int				after_pipe(char *line);
int				only_white_space(char *line_read);

/*      free_garbage     */

void   		 free_garbage(t_garbage *garbage);
void		free_garbage_exit(t_garbage *garbage, int exit_code);
void		free_garbage_and_env(t_garbage *garbage);
void		free_garbage_env_exit(t_garbage *garbage, int exit_code);

/*  ft_itoa */
char			*ft_itoa(int n);

/*  export_utils.c */
int				str_len_env(char *str);
char			*ft_strchr(const char *s, int c);
int				check_if_tab_exist(char *tab, char **env);
int				parsing_of_export(char *tab, char **env_copy, int *a, int *j);
int				what_to_do(char *tab, char **env);

/*  security */
int				check_if_builtin (char **env, char ***new_env, int i, t_garbage *garbage);
int				check_echo (char **args,int cmp, int i, int execute);
int				check_if_exit(char **args, char **env, t_garbage *garbage);
int				check_builtin(char **args);

/* main.c */

char			*rl_gets();
int				main(int argc, char **argv, char **env);
t_maillons		*loop_create_maillons(char *line, t_garbage *garbage, int i);
void			end_quote(t_garbage *garbage);

/* delete_quote.c */
char			*del_q(char *line, int j, int len);

/*  built in cd */
int				do_cd(char **new_env, char *path);

/*  built in env */
void			do_env(char **env);
char			**my_env(char **env);

/*  built in exit */
void			do_exit(char *statut, t_garbage *garbage);

/*  built in export */
char			**do_export(char *tab, char **env_copy, int i, int a);
int				parse_export(char *tab, int i, int a);

/*  built in pwd */
int				do_pwd(void);

/*  built in unset */
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			do_unset(char *tab, char **env_copy, int i, int found_line);

/*  signals */
void			setup_signal_handlers(void);
void			handle_sig(int sig);
void			setup_signal_handlers_child(void);

/*  utils parsing_bis */
char			*ft_strdup_const(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
int				skip_quote(char *line, int i);
int				print_tab(char **tab);

/*  parsing */
int				parse(char *line);

/*	parsing_utils.c	*/
int				str_cmp(char *s1, char *s2);
int				quote_close_2(char *str);
int				ft_strlen_const(const char *str);

/*	check_space.c	*/
int				check_error_2_space(char *line, char c, char c_bis, int i);
int				check_error_3_space(char *line, char c, char *c_bis, int i);
int				check_error_space(char *line, char c, int i);

/* child.c */

void			child1_end(two_pipe *two_pipe, char ***env, t_maillons *maillons, t_garbage *garbage);
int				child1(two_pipe *two_pipe, char ***env, t_maillons *maillons, t_garbage *garbage);
void			child2_end(two_pipe *two_pipe, char ***env, t_maillons *maillons, t_garbage *garbage);
int				child2(two_pipe *two_pipe, char ***env, t_maillons *maillons, t_garbage *garbage);
int				check_access(t_maillons *maillons);

/*  replace dollar */
char			*replace_dollar(char *tab, char **new_env, int i, int skip);
char			*found_it(char *tab, char **new_env, t_index *index, int *skip);

/*  dollars_interrogation */
void			new_in_old(for_dollar *var, t_index *index, char **new_env, int *skip);
void			new_in_old_interrogation(for_dollar *var);
char			*interrogation(char *tab, char **new_env, int skip, t_index index);
char			*do_replace(char *tab, char **new_env, int skip, t_index index);

/*  replace dollar 2 */
char			*delete_dollar(char *tab, char **new_env, int i, int skip);
char			*apply_delete(int i, int skip, char *tab);
//char			*delete_dollar(char *line);

/*  dollars_utils.c */
char			*one_dollar_or_more(char *tab, int *i, char **new_env, t_index *index);
int				research(int skip, int a, char *tab, char **new_env);

/*  check_one.c */
int				check_1(char *line);
int				after_redirection(char *line);
int				check_parenthesis(char *line);


/* libft.c */

int				ft_strlen(char *str);
int				ft_strcmp(char *str, char *str2);
char			*ft_strdup(char *str);
void			s_fd(char *s, int fd);
int				ft_isdigit(int c);

/* split.c */

int				check_sep(char c, char *sep);
int				count_words(char *str, char *sep);
char			*create_word_quote(char *str, char *sep);
char			*create_word_all2(char *str, char *sep);
char			*create_word_all(char *str, char *sep);
char			*create_word(char *str, char *sep);
char			**ft_split(char *str, char *sep);

/* split2.c */

int				is_inquotes(char *str, int pos);
int				check_quote2(char c);
int				check_sep2(char c, char *sep);
int				count_words2(char *str, char *sep);
int				ft_stablen(char *str, int tor, char *sep);
char			*ft_strtab(char *str, int tor, char *sep);
char			**ft_split2(char *str, char *sep);

/* split_list.c */

char			*create_word_list(char *str, char *sep);
t_split_elem	*ft_split_list(char *str, char *sep);

/* find_output.c */

int				is_white_space(char c);
char			*find_output(char **tab);

/* find_command.c */

char			*find_command(t_split_elem *lst);
char			**find_argument(t_split_elem *lst);

/* find_input_output.c */

t_input_output	*find_input_output(t_split_elem *lst);

/* free.c */

void			free_split_elem(t_split_elem *lst);
void			ft_free_tab(char **tab);
void			ft_free_split_arg(t_split_elem **lst);
void			free_input_output(t_input_output **lst);
void			free_input_output_middle(t_input_output **lst, t_input_output **first);
void			free_inputs_outputs(t_input_output **lst);
void			free_maillon(t_maillons *lst);
void			free_maillons(t_maillons *lst);

/* list_split_elem.c */

t_split_elem	*create_split_elem(char	*str);
t_split_elem	*create_split_elem_dup(char	*str);
t_split_elem	*lstlast_split_elem(t_split_elem *lst);
void			add_end_split_elem(t_split_elem	**list, t_split_elem *add);
void			free_split_elem(t_split_elem *lst);
void			ft_strjoin_list(t_split_elem *list, t_split_elem **add, t_split_elem **first);

/* list_input_output.c */

t_input_output	*create_input_output(char *name, char *operator, t_input_output *prev);
t_input_output	*lstlast_input_output(t_input_output *lst);
void			add_end_input_output(t_input_output **list, t_input_output *add);

/* list_mailllons.c */

int				ft_strlen_maillons(t_maillons *lst);

/* create_split_argc */

int				just_quote(char *str);
int				chek_sep_str(char *str, char *sep);
void			create_word_sep(t_split_elem **lst, char *str, int len);
t_split_elem	**split_redirection(char *str, char *sep);
void			redirection(t_split_elem *lst);
void			create_split_arg(t_split_elem **lst);

/* clear_maillons.c */

char			*find_s(t_input_output *lst, char *sep);
int				find_if_have_output(t_input_output *lst, char *sep);
void			find_maillon_without_cmd(t_maillons **maillons);

/* create_maillons.c */

t_maillons		*create_maillons(t_split_elem **split, t_maillons *prev);
t_maillons		*lstlast_maillons(t_maillons *lst);
void			add_end_maillons(t_maillons **lst, t_maillons *add);

/* quote.c */

int				quote_close(char *str);
void			change_quote(char *str, int i, int single, int doubl);

/* parsing_input_output.c */

int				check_output(t_input_output *output);
int				check_input(t_input_output *output);
int				check_input_output(t_input_output **input_output, t_garbage *garbage);
int				check_inputs_outputs(t_maillons *maillons);

/* bultins_echo.c */

int				check_option_n(char *str, int *space);
void			do_echo(char **arg);

void			cd(char **arg);

/* pipex.c */

int				pipex(t_maillons *maillons, char ***env, t_garbage *garbage);

/* pipex_one.c */

int	pipex_one(t_maillons *maillons, char ***env, t_garbage *garbage);

/* pipex2.c */

void	sigint_child(int unused);
int	switch_dup2_fd_in(t_maillons *m, t_pipes *pipes, int i, int len);
int	switch_dup2_fd_out(t_maillons *maillons, t_pipes *pipes, int i, int len);
int	pipex_multiple(int len, t_garbage *g, int i);

/*utils_pipex_two.c */

void	pipex_multiple_check(t_garbage *g);
void	pipex_multiple_free(t_garbage *garbage);
void	pipex_multiple_close_pipe(t_garbage *garbage, int len, int i);
void	handle_child_process(int i, int len, t_garbage *g);

/* utils_pipex.c */

void			free_all_pipes(int argc, t_pipes *pipes);
void			create_pipe(int *pipes, int i);
int				*create_pipes(int len);
t_pipes			*create_all_pipes(int len);

/*split_pipex.c */

char			**split_pipex(char *path, char sep);
int				ft_strcmp_pipex(char *str, char *search);

/* cmd_to_path.c */

int				cmd_to_path(t_maillons *maillons, char **env);

/* create_heredoc.c*/

void			create_heredoc(int *pipe_fd);
int				heredoc(char *stop);
void			find_all_heredoc(t_maillons *maillons);

/* builtins_pwd.c */

void			pwd(void);

/* get_next_line */

int				check_end(char *line);
char			*ft_strjoin_gnl(char *line, char *buf);
void			get_line(char *line, char *buffer);
char			*get_next_line(int fd);

/*utils_parsing.c */

char			*ft_strjoin_pipex(char *path, char *add);
int				check_dollar(char *line);

/* garbage_collector.c  */

void			initialize_garbage(t_garbage *garbage);

/* supp.c */

void			ft_print_maillon(t_maillons *maillons);
void			ft_print_tab(char **tab);
void			ft_print_split_elem(t_split_elem *list);
void			ft_print_input_output(t_input_output *list);
void			ft_print_maillons(t_maillons *maillons);
char			*create_word_and_quote2(char *str, char *sep);
void			ft_print_garbage(t_garbage	*garbage);

#endif
