/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakariyahamdouchi <zakariyahamdouchi@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:30:40 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/18 23:29:10 by zakariyaham      ###   ########.fr       */
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

int	is_builtin_parent(t_garbage *data, t_maillons *last, char *cmd)
{
	if (!cmd || (last && data->maillons != last))
		return (0);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

static void	catch_child_status(t_garbage *data, int wstatus, \
t_maillons *command, t_maillons *last)
{
	int	status_code;

	status_code = 0;
	if (WIFSIGNALED(wstatus))
	{
		status_code = WTERMSIG(wstatus);
		if (status_code == 2)
			g_exit_code[0] = 130;
		else if (status_code == 3)
		{
			g_exit_code[0] = 131;
			if (command == last)
			{
				s_fd("Quit", 2);
				if (WCOREDUMP(wstatus))
					s_fd(" (core dumped)", 2);
				s_fd("\n", 2);
			}
		}
		return ;
	}
	else if (WIFEXITED(wstatus))
		g_exit_code[0] = WEXITSTATUS(wstatus);
	if (!is_builtin_parent(data, last, command->command))
		g_exit_code[0] = status_code;
}

static void	call_signal_pipex(void)
{
	signal(SIGQUIT, signal_quit_child);
	signal(SIGINT, sigint_child);
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
		if (pid == 0 && check_input_output(&(g->maillons->output), g) != -1)
			handle_child_process(i, len, g);
		pipex_multiple_close_pipe(g, len, i);
		i++;
		g->maillons = g->maillons->next;
	}
	i = -1;
	while (++i < len)
	{
		waitpid(-1, &wstatus, 0);
		//catch_child_status(g, wstatus, tmp, get_last_maillons(g->maillons));
	}
	g->maillons = tmp;
	return (1);
}
