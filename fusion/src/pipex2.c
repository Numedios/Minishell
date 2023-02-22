/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:30:40 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/22 17:57:17 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code[2];

/* rajouter exit code */

t_maillons	*get_last_maillons(t_maillons *maillons)
{
	t_maillons	*tmp;

	tmp = maillons;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

static void	call_signal_pipex(void)
{
	signal(SIGQUIT, signal_quit_child);
	signal(SIGINT, sigint_child);
}

int	check_access_two(t_maillons *maillons)
{
	if (check_builtin(maillons->args) == 2)
		return (0);
	if (check_echo(maillons->args, 0, 0, 1) == 0
		|| check_builtin(maillons->args) == 0)
		return (0);
	if (maillons->command == NULL)
		return (0);
	if (access(maillons->command, F_OK | X_OK) == -1)
	{
		g_exit_code[0] = 127;
		s_fd("bash: ", 2);
		s_fd(maillons->command, 2);
		s_fd(": command not found\n", 2);
		return (1);
	}
	return (0);
}

static void	exec_child_pid(t_garbage *g, t_maillons *tmp, int i)
{
	if (check_input_output2(&(g->maillons)->output, NULL,
			NULL, g->maillons->output) == -1)
	{
		g->maillons = tmp;
		free_garbage_env_exit(g, 1);
	}
	else
	{
		if (check_access_two(g->maillons) == 0)
			handle_child_process(i, g, g->maillons, tmp);
		g->maillons = tmp;
		free_garbage_env_exit(g, 1);
	}
}

int	pipex_multiple(int len, t_garbage *g, int i, int wstatus)
{
	pid_t		pid;
	t_maillons	*tmp;

	tmp = g->maillons;
	g->pipes = create_all_pipes(len - 1);
	while (g->maillons)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		call_signal_pipex();
		if (pid == 0)
			exec_child_pid(g, tmp, i);
		pipex_multiple_close_pipe(g, len, i);
		i++;
		g->maillons = g->maillons->next;
	}
	i = -1;
	while (++i < len)
		waitpid(-1, &wstatus, 0);
	g->maillons = tmp;
	return (1);
}
