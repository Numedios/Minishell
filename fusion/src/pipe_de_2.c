/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_de_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:44:01 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/19 15:26:51 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//test : <a ls >a | < b ls > b
//que faire si le fichier in n'exise pas ??
// maillons -> command = /usr/bin/ls
//maillons -> args = a commmand et les options
//probleme avec le heredoc en premiere commande

extern int	g_exit_code[2];
//gerer les enfants avec g_exit_code[1] = 2; si g_exit_code[1] == 3 alors exit(0) ou faire un if dans les enfants pour directement exit si g_exit_code[1] == 3;

void	signal_quit_child(int useless)
{
	//(void)useless;
	if (useless == SIGINT) //ctrl+c
	{
		write(1, "\n", 1);
		g_exit_code[0] = 130;
		//close(STDIN_FILENO);
	}
	if (useless == SIGQUIT) /*ctrl+\*/
	{
		write(2, "Quit (core dumped)\n", 19);
		g_exit_code[0] = 131;
	}
	//write(2, "QUIT\n", 5);
}

int	loop(two_pipe *two_pipe, char ***env, t_maillons *maillons, pid_t pid, t_garbage *garbage)
{
	int	n;

	n = 0;
	if (two_pipe->i == 0 && pid == 0)
	{
		n = child1(two_pipe, env, maillons, garbage);
		if (n == 1)
			return (1);
	}
	if (two_pipe->i == 1 && pid == 0)
	{
		n = child2(two_pipe, env, maillons->next, garbage);
		if (n == 1)
			return (1);
	}
	return (0);
}

void	init(two_pipe *two_pipe)
{
	two_pipe->status = 0;
	two_pipe->i = 0;
	two_pipe->fd_in = -3;
	two_pipe->fd_out = -3;
	if (pipe(two_pipe->pipe_fd) < 0)
	{
		write(2, "pipe_fd\n", 8);
		exit ;
	}
}

int	pipex_2(t_maillons *maillons, char ***env, t_garbage *garbage)
{
	two_pipe	two_pipe;
	pid_t		pid[2];
	int			n;

	init(&two_pipe);
	n = 0;
	while (two_pipe.i < 2)
	{
		pid[two_pipe.i] = fork();
		if (pid[two_pipe.i] < 0)
			return (1);
		signal(SIGQUIT, signal_quit_child);
		if (loop(&two_pipe, env, maillons, pid[two_pipe.i], garbage) != 0)
			break ;
		two_pipe.i++;
	}
	close(two_pipe.pipe_fd[1]);
	close(two_pipe.pipe_fd[0]);
	waitpid(pid[0], &two_pipe.status, 0);
	if (WIFEXITED(two_pipe.status))
		g_exit_code[0] = WEXITSTATUS(two_pipe.status);
	waitpid(pid[1], NULL, 0);
	if (WIFEXITED(two_pipe.status))
		g_exit_code[0] = WEXITSTATUS(two_pipe.status);
	return (0);
}
