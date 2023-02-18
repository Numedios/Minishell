/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:27:51 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 18:40:56 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code[2];

void	child1_end(two_pipe *two_pipe, char ***env, t_maillons *maillons, t_garbage *garbage)
{
	if (check_if_builtin(maillons->args, *env, env, 0, garbage) == 0)
	{
		dprintf(2, "yes !\n");
		exit(0);
	}
	if (check_echo(maillons->args, 0, 0, 0) == 0)
	{
		dprintf(2, "yes1\n");
		exit(0);
	}
	if (maillons->command != NULL
		&& execve(maillons -> command, maillons -> args, *env) < 0)
	{
		write(2, "execve!\n", 8);
		exit(1);
	}
	exit (1);
}

int	child1(two_pipe *two_pipe, char ***env, t_maillons *maillons, t_garbage *garbage)
{
	if (find_stdin_2(maillons, &two_pipe->fd_in, two_pipe) != 0)
		dup2(two_pipe->fd_in, STDIN_FILENO);
	if (two_pipe->fd_in != -3 && two_pipe->fd_in != -1)
		close(two_pipe->fd_in);
	if (close(two_pipe->pipe_fd[0]) < 0)
	{
		write(2, "close1\n", 7);
		exit(1);
	}
	if (find_stdout_2(maillons, &two_pipe->fd_out, two_pipe) != 0)
		dup2(two_pipe->fd_out, STDOUT_FILENO);
	if (close(two_pipe->pipe_fd[1]) < 0)
	{
		write(2, "close2\n", 7);
		exit(1);
	}	
	if (two_pipe->fd_out != -3 && two_pipe->fd_out != -1)
		close(two_pipe->fd_out);
	if (maillons->heredoc != -1)//
		close(maillons->heredoc);//
	child1_end(two_pipe, env, maillons, garbage);
}

void	child2_end(two_pipe *two_pipe, char ***env, t_maillons *maillons, t_garbage *garbage)
{
	if (check_if_builtin(maillons->args, *env, env, 0, garbage) == 0)
	{
		dprintf(2, "yes 2!\n");
		exit(0);
	}
	if (check_echo(maillons->args, 0, 0, 0) == 0)
	{
		dprintf(2, "yes3\n");
		exit(0);
	}
	if (maillons->command != NULL
		&& execve(maillons-> command, maillons-> args, *env) < 0)
	{
		write(2, "execve!\n", 8);
		exit(1);
	}
	exit (1);
}

int	child2(two_pipe *two_pipe, char ***env, t_maillons *maillons, t_garbage *garbage)
{
	if (find_stdout_2(maillons, &two_pipe->fd_out, two_pipe) != 0)
		dup2(two_pipe->fd_out, STDOUT_FILENO);
	if (two_pipe->fd_out != -3 && two_pipe->fd_out != -1)
		close(two_pipe->fd_out);
	if (close(two_pipe->pipe_fd[1]) < 0)
	{
		write(2, "close2-2\n", 9);
		exit (1);
	}
	if (find_stdin_2(maillons, &two_pipe->fd_in, two_pipe) != 0)
		dup2(two_pipe->fd_in, STDIN_FILENO);
	if (two_pipe->fd_in != -3 && two_pipe->fd_in != -1)
		close(two_pipe->fd_in);
	if (close(two_pipe->pipe_fd[0]) < 0)
	{
		write(2, "close1-2\n", 9);
		exit (1);
	}
	if (maillons->heredoc != -1)//
		close(maillons->heredoc);//
	child2_end(two_pipe, env, maillons, garbage);
}

int	check_access(t_maillons *maillons)
{
	while (maillons)
	{
		if (check_builtin(maillons->args) == 2)
			return (1);
		if (check_echo(maillons->args, 0, 0, 1) == 0
			|| check_builtin(maillons->args) == 0)
			maillons = maillons->next;
		else if (maillons->command != NULL
			&& access(maillons->command, F_OK | X_OK) != 0)
		{
			g_exit_code[0] = 127;
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(maillons->command, 2);
			ft_putstr_fd(": command not found\n", 2);
			return (1);
		}
		else
			maillons = maillons->next;
	}
	return (0);
}
