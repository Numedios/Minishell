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

void	sigint_child(int unused)
{
	(void)unused;
	write(1, "\n", 1);
}

/*
* 		if (ft_strcmp(find_s(maillons-> prev-> output, ">"), "/dev/stdout"))
*			return (dprintf(2, "1 pas dup input\n"), 1);
*
*/

int	switch_dup2_fd_in(t_maillons *m, t_pipes *pipes, int i)
{
	int	res;

	res = -2;
	if (find_if_have_output(m -> output, "<") == 1)
	{
		res = open(find_s(m->output, "<"), O_RDWR, O_DSYNC, !O_DIRECTORY);
		dup2(res, STDIN_FILENO);
	}
	else if (find_if_have_output(m -> output, "<<") == 1)
	{
		if (m -> heredoc != -1)
			dup2(m -> heredoc, STDIN_FILENO);
	}
	else if (!(m-> prev))
		return (1);
	else if ((find_if_have_output(m->prev->output, ">") || !(m->prev->command)))
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

/*
*if(!ft_strcmp(find__s(maillons -> output, ">"), "/dev/stdout"));
*	return (dprintf(2, "2 pas dup output\n"),1);
*
*/

int	switch_dup2_fd_out(t_maillons *maillons, t_pipes *pipes, int i)
{
	int	res;

	res = -2;
	if (find_if_have_output(maillons -> output, ">"))
	{
		res = open(find_s(maillons -> output, ">"),
				O_WRONLY | O_CREAT | O_TRUNC, 0644, !O_DIRECTORY);
		dup2(res, STDOUT_FILENO);
	}
	else if (find_if_have_output(maillons -> output, ">>"))
	{
		res = open(find_s(maillons -> output, ">>"),
				O_WRONLY | O_CREAT | O_APPEND, 0644, !O_DIRECTORY);
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

t_maillons *get_last_maillons(t_maillons *maillons)
{
	t_maillons *tmp;

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


static void	catch_child_status(t_garbage *data, int wstatus, t_maillons *command, t_maillons *last)
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


int	pipex_multiple(int len, t_garbage *g, int i)
{
	pid_t		pid;
	t_maillons	*tmp;
	int		wstatus;

	tmp = g->maillons;
	g->pipes = create_all_pipes(len - 1);
	while (g->maillons)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		signal(SIGQUIT, signal_quit_child);
		signal(SIGINT, sigint_child);
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
		catch_child_status(g, wstatus,tmp, get_last_maillons(g->maillons));
	}
	g->maillons = tmp;
	pipex_multiple_free(g);
	return (1);
}
