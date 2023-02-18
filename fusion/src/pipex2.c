/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:30:40 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/15 21:18:44 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	switch_dup2_fd_in(t_maillons *maillons, t_pipes *pipes, int i, int len)
{
	int	res;

	res = -2;
	if (find_if_have_output(maillons -> output, "<") == 1)
	{
		res = open(find_name_sep(maillons->output, "<"), O_RDWR, O_DSYNC, !O_DIRECTORY);
		dup2(res, STDIN_FILENO);
	}
	else if (find_if_have_output(maillons -> output, "<<") == 1)
	{
		if (maillons -> heredoc != -1)
			dup2(maillons -> heredoc, STDIN_FILENO);
	}
	else if (!(maillons-> prev))
		return (1);
	else if (find_if_have_output(maillons -> prev -> output, ">") ||!(maillons->prev->command))
	{
		res = open("/dev/null", O_RDWR, O_DSYNC, !O_DIRECTORY);
		dup2(res, STDIN_FILENO);
	}
	else
		dup2(pipes->pipe[i * 2 - 2], STDIN_FILENO);
	if (res != -2)
		close(res);
	return (1);
}

int	switch_dup2_fd_out(t_maillons *maillons, t_pipes *pipes, int i, int len)
{
	int	res;

	res = -2;
	if (find_if_have_output(maillons -> output, ">"))
	{
		res = open(find_name_sep(maillons -> output, ">"), O_WRONLY | O_CREAT | O_TRUNC, 0644, !O_DIRECTORY);
		if (!ft_strcmp(find_name_sep(maillons -> output, ">"), "/dev/stdout"))
			return (1);
		dup2(res, STDOUT_FILENO);
	}
	else if (find_if_have_output(maillons -> output, ">>"))
	{
		res = open(find_name_sep(maillons -> output, ">>"), O_WRONLY | O_CREAT | O_APPEND, 0644, !O_DIRECTORY);
		dup2(res, STDOUT_FILENO);
	}
	else if (!(maillons-> next))
		return (1);
	else
		dup2(pipes->pipe[i * 2 + 1], STDOUT_FILENO);
	if (res != -2)
		close(res);
	return (1);
}

/* rajouter exit code */

void	sigint_child(int unused)
{
	(void)unused;
	write(1, "\n", 1);
}

void	pipex_multiple_check(t_maillons **m, char ****e, t_garbage **g)
{
	if ((*m)->heredoc != -1)
		close((*m)->heredoc);
	if (check_if_builtin((*m)->args, **e, *e, 0, *g) == 0 && check_echo((*m)->args, 0, 0, 0) == 0)
		free_garbage_exit(*g, 0);
	if ((*m)->command != NULL && execve((*m)->command, (*m)->args, **e) == -1)
		perror("execve");
	free_garbage_exit(*g, 1);
}

void	pipex_multiple_free(t_garbage **garbage)
{
	if ((*garbage)->pipes && (*garbage)->pipes->pipe)
	{
		free((*garbage)->pipes->pipe);
		free((*garbage)->pipes);
		(*garbage)->pipes = NULL;
	}
}

void pipex_multiple_close_pipe(t_garbage **garbage, int len, int i)
{
	if (i > 0 && (*garbage)->pipes->pipe[i * 2 - 2])
		close((*garbage)->pipes->pipe[i * 2 - 2]);
	if (i != (len -1) && (*garbage)->pipes->pipe[i * 2 + 1])
		close((*garbage)->pipes->pipe[i * 2 + 1]);
}

void handle_child_process(t_maillons *maillons, t_pipes *pipes, int i, int len, char ***env, t_garbage *garbage) 
{
    switch_dup2_fd_in(maillons, pipes, i, len);
    switch_dup2_fd_out(maillons, pipes, i, len);
    free_all_pipes((len - 1) * 2, pipes);
    garbage->pipes = NULL;
    pipex_multiple_check(&maillons, &env, &garbage);
}

int	pipex_multiple(t_maillons *maillons, char ***env, int len, t_garbage *garbage)
{
	t_pipes	pipes;
	pid_t	pid;
	int		i;

	garbage->pipes = create_all_pipes(len - 1);
	i = 0;
	while (maillons)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		signal(SIGQUIT, signal_quit_child);
		signal(SIGINT, sigint_child);
		if (pid == 0)
		{
			switch_dup2_fd_in(maillons, garbage->pipes, i, len);
			switch_dup2_fd_out(maillons, garbage->pipes, i, len);
			free_all_pipes((len - 1) * 2, garbage->pipes);
			garbage->pipes = NULL;
			pipex_multiple_check(&maillons, &env, &garbage);
			//handle_child_process(maillons, garbage->pipes, i, len, env, garbage);
		}
		pipex_multiple_close_pipe(&garbage, len, i);
		i++;
		maillons = maillons -> next;
	}
	i = 0;
	while (i < len)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	pipex_multiple_free(&garbage);
	return (1);
}
