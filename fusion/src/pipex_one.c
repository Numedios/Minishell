/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:44:42 by sbelabba          #+#    #+#             */
/*   Updated: 2023/02/20 17:44:44 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code[2];

int	find_stdin(t_maillons *maillons)
{
	int	res;

	res = -1;
	if (find_if_have_output(maillons -> output, "<") == 1)
	{
		res = open(find_s(maillons -> output, "<"),
				O_RDWR, O_DSYNC, !O_DIRECTORY);
		return (res);
	}
	else if (find_if_have_output(maillons -> output, "<<") == 1)
	{
		res = maillons -> heredoc;
		return (res);
	}
	else if (!(maillons-> prev))
	{
		return (res);
	}
	else if (find_if_have_output(maillons -> output -> prev, ">")
		|| !(maillons->prev->command))
	{
		res = open("/dev/null", O_RDWR, O_DSYNC, !O_DIRECTORY);
		return (res);
	}
	return (-1);
}

int	find_stdout(t_maillons *maillons)
{
	int	res;

	res = -1;
	if (find_if_have_output(maillons -> output, ">"))
	{
		res = open(find_s(maillons -> output, ">"),
				O_WRONLY | O_CREAT | O_TRUNC, 0644, !O_DIRECTORY);
		return (res);
	}
	else if (find_if_have_output(maillons -> output, ">>"))
	{
		res = open(find_s(maillons -> output, ">>"),
				O_WRONLY | O_CREAT | O_APPEND, 0644, !O_DIRECTORY);
		return (res);
	}
	else if (!(maillons-> next))
		return (res);
	return (res);
}

int	pipex_one_condition(t_maillons *m, char ***e, t_garbage *g)
{
	if (check_if_exit(m->args, g) == 0)
		return (1);
	if (check_if_builtin(*e, e, 0, g) == 0)
		return (1);
	return (0);
}

void	catch_status(t_garbage *data, int wstatus, t_maillons *command)
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
			if (command)
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
	if (!is_builtin_parent(data, command, command->command))
		g_exit_code[0] = status_code;
}

int	pipex_one(t_maillons *maillons, char ***env, t_garbage *garbage)
{
	pid_t	pid;
	int		wstatus;

	if (pipex_one_condition(maillons, env, garbage) == 1)
		return (free_garbage(garbage), 0);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	signal(SIGQUIT, signal_quit_child);
	signal(SIGINT, signal_quit_child);
	if (pid == 0 && check_input_output(&(maillons->output), garbage) != -1)
	{
		pipex_one_dup(&maillons);
		if (check_echo(maillons->args, 0, 0, 0) == 0)
			free_garbage_env_exit(garbage, g_exit_code[0]);
		if (maillons->command != NULL
			&& execve(maillons->command, maillons->args, *env) == -1)
			perror("execve");
		free_garbage_env_exit(garbage, g_exit_code[0]);
	}
	waitpid(-1, &wstatus, 0);
	//catch_status(garbage, wstatus, maillons);
	free_garbage(garbage);
	return (0);
}
