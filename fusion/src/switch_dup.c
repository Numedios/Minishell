/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:36:02 by sbelabba          #+#    #+#             */
/*   Updated: 2023/02/21 20:36:03 by sbelabba         ###   ########.fr       */
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

int	check_if_tab_exist(char *tab, char **env)
{
	int	len_tab;
	int	len_env;
	int	i;

	if (!env)
		return (0);
	len_tab = ft_strlen(tab);
	i = 0;
	while (env && env[i])
	{
		len_env = ft_strlen(env[i]);
		if (len_tab != len_env || ft_strncmp(env[i], tab, len_tab) != 0)
			i++;
		else
			return (1);
	}
	return (0);
}

int	pipex_one_dup(t_maillons **maillons)
{
	int		fd_in;
	int		fd_out;

	if ((*maillons)->command != NULL)
	{
		fd_in = find_stdin(*maillons);
		fd_out = find_stdout(*maillons);
		if (fd_in != -1)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (fd_out != -1)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
	}
	return (1);
}
