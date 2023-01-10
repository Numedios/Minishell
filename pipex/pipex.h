/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:44:12 by sbelabba          #+#    #+#             */
/*   Updated: 2022/12/07 13:34:06 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define  PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>

# define BUFFER_SIZE 5

typedef struct s_data
{
	char	**path;
	char	***cmd;
}	t_data;

typedef struct s_pipes
{
	int	*pipe;
	int	fd_stdin;
	int	fd_stdout;
}	t_pipes;

/* main.c */

int		main(int argc, char **argv, char **env);

/* create_path.c */

char	**check_acces_loop(char **cpy, char **res, char ***cmd, char **path);
char	**check_acces(char **path, char ***cmd);
t_data	create_path(char **argv, char **envp);

/* create_path_utils.c */

void	free_data(t_data *stock);
char	*get_path(char **envp);
char	***recup_arg(char **argv);
int		check_is_path(char *str);
int		only_space(char *str);

/* create_pipes.c */

void	create_pipe(int *pipes, int i);
int		*create_pipes(int argc);
t_pipes	create_all_pipes(int argc, char **argv, t_data *stock);

/* parsing*/

int		count_space(char *str);
int		check_arg(char **argv);
int		parsing(int argc, char **argv);

/* utils_parsing*/

char	*ft_strjoin_pipex(char *path, char *add);

/* split_pipex*/

int		count_world(char *path, char sep);
char	*create_word(char *path, char sep);
char	**split_pipex(char *path, char sep);

/* utils_libft*/

void	free_tab(char **tab);
void	free_tab_tab(char ***tab);
int		ft_strlen(char *str);
int		ft_strlen_tab(char **tab);
int		ft_strlen_tab_tab(char ***tab);

/* libft.c */

char	*ft_strdup(char *str);
char	*ft_strdup_free(char *str);
int		ft_strcmp(char *str, char *search);

/* utils_tab.c */

void	add_cmd(char **cpy, char *cmd);
char	**create_cpy_tab(char **path);
char	**cpy_cmd_tab(char **path, char *cmd);

/* pipex.c */

int		dup_fd(int new_stdin, int new_stdout);
void	free_all_pipes(int argc, t_pipes pipes);
int		switch_dup2_fd(int argc, t_pipes *pipes, t_data *stock, int i);
int		execute(char **env, t_data *stock, int i);
int		pipex(int argc, char **argv, char **env, t_data *stock);

/* get_next_line */

int		check_end(char *line);
char	*ft_strjoin(char *line, char *buf);
void	get_line(char *line, char *buffer);
char	*get_next_line(int fd);

/* heredoc.c */

int		ft_strncmp(char *s1, char *s2);
int		create_heredoc(void);
int		heredoc(int argc, char **argv);

#endif
