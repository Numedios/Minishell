/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:44:42 by sbelabba          #+#    #+#             */
/*   Updated: 2023/02/22 17:37:05 by zhamdouc         ###   ########.fr       */
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
	else if (check_echo(g->maillons->args, 0, 0, 0) == 0)
		return (1);
	return (0);
}

void	catch_status(int wstatus, t_maillons *command)
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
	{
		wstatus = WEXITSTATUS(wstatus);
		g_exit_code[0] = wstatus;
	}
}

static int	check_access_one(t_maillons *maillons)
{
	if (check_builtin(maillons->args) == 2)
	{
		return (0);
	}
	if (check_echo(maillons->args, 0, 0, 1) == 0
		|| check_builtin(maillons->args) == 0)
	{
		return (0);
	}
	if (maillons->command == NULL)
		return (0);
	if (access(maillons->command, F_OK | X_OK) == -1)
	{
		dprintf(2, "bash: syntax error near unexpected token `newline'\n");
		g_exit_code[0] = 127;
		s_fd("bash: ", 2);
		s_fd(maillons->command, 2);
		s_fd(": command not found\n", 2);
		return (1);
	}
	return (0);
}

static int	condition_access(t_maillons *maillons, char ***env, t_garbage *garbage)
{
	if (check_access_one(maillons) == 0)
	{
		pipex_one_dup(&maillons);
		if (check_echo(maillons->args, 0, 0, 1) == 0
			|| check_builtin(maillons->args) == 0)
		{
			check_if_builtin(garbage->new_env, &(garbage->new_env), 0, garbage);
			check_echo(garbage->maillons->args, 0, 0, 0);
			free_garbage_env_exit(garbage, g_exit_code[0]);
		}
		if (maillons->command != NULL
			&& execve(maillons->command, maillons->args, *env) == -1)
			perror("execve");
		return (free_garbage_env_exit(garbage, g_exit_code[0]), 1);
	}
	else
		return (1);
}

int	pipex_one(t_maillons *maillons, char ***env, t_garbage *garbage)
{
	pid_t	pid;
	int		wstatus;

	wstatus = 0;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	signal(SIGQUIT, signal_quit_child);
	signal(SIGINT, signal_quit_child);
	if (pid == 0 && check_input_output2(&(garbage->maillons)->output, NULL, NULL, garbage->maillons->output) == -1)
	{
		g_exit_code[0] = 1;
		free_garbage_env_exit(garbage, g_exit_code[0]);
	}
	else if (pid == 0)
	{
		if (condition_access(maillons, env, garbage) == 1)
			return (free_garbage_env_exit(garbage, g_exit_code[0]), 1);
	}
	waitpid(-1, &wstatus, 0);
	catch_status(wstatus, maillons);
	return (0);
}
