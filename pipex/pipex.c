/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:46:05 by sbelabba          #+#    #+#             */
/*   Updated: 2022/12/07 13:47:41 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	dup_fd(int new_stdin, int new_stdout)
{
	if (dup2(new_stdin, STDIN_FILENO) == -1
		|| dup2(new_stdout, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}

void	free_all_pipes(int argc, t_pipes pipes)
{
	int	i;

	i = 0;
	while (i < (argc))
	{
		if (pipes.pipe[i])
			close(pipes.pipe[i]);
		i++;
	}
	if (pipes.pipe)
		free(pipes.pipe);
	if (pipes.fd_stdin)
		close(pipes.fd_stdin);
	if (pipes.fd_stdout)
		close(pipes.fd_stdout);
}

/* jen suis la verifier tout les dup_fd*/

int	switch_dup2_fd(int argc, t_pipes *pipes, t_data *stock, int i)
{
	int	res;

	if (i == 0)
		res = dup_fd(pipes->fd_stdin, pipes->pipe[1]);
	else if (i < argc)
		res = dup_fd(pipes->pipe[i * 2 - 2], pipes->pipe[i * 2 + 1]);
	else if (i == argc)
		res = dup_fd(pipes->pipe[i * 2 - 2], pipes->fd_stdout);
	free_all_pipes(argc * 2, *pipes);
	if (res == 0)
	{
		free_data(stock);
		exit (1);
	}
	return (1);
}

int	execute(char **env, t_data *stock, int i)
{
	if (execve(stock->path[i], stock->cmd[i], env) == -1)
	{
		free_data(stock);
		perror("execve");
		exit (1);
	}
	return (1);
}

int	pipex(int argc, char **argv, char **env, t_data *stock)
{
	t_pipes	pipes;
	pid_t	pid;
	int		i;

	pipes = create_all_pipes(argc - 3, argv, stock);
	i = -1;
	while (++i < argc - 2)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
		{
			switch_dup2_fd(argc - 3, &pipes, stock, i);
			execute(env, stock, i);
		}
		if (i > 0 && pipes.pipe[i * 2 - 2])
			close(pipes.pipe[i * 2 - 2]);
		if (i != argc - 3 && pipes.pipe[i * 2 + 1])
			close(pipes.pipe[i * 2 + 1]);
	}
	i = -1;
	while (++i < argc - 2)
		waitpid(-1, NULL, 0);
	return (free_all_pipes((argc - 3) * 2, pipes), 1);
}
