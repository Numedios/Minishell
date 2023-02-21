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

int	pipex_multiple(int len, t_garbage *g, int i)
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
		waitpid(-1, NULL, 0);
	g->maillons = tmp;
	pipex_multiple_free(g);
	return (1);
}
