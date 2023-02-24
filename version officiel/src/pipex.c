/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:20:55 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/22 16:53:35 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code[3];

int	dup_fd(int new_stdin, int new_stdout)
{
	if (dup2(new_stdin, STDIN_FILENO) == -1
		|| dup2(new_stdout, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}

static	int	check_no_sep(t_input_output	*output)
{
	return (find_if_have_output(output, ">") != 1 && find_if_have_output(output, "<") != 1 && find_if_have_output(output, ">>") != 1 && find_if_have_output(output, "<<") != 1);

}

int	pipex(t_maillons *maillons, char ***env, t_garbage *garbage)
{
	int	len;
	int	wstatus;

	wstatus = 0;
	len = ft_strlen_maillons(maillons);
	if (len == 0)
		return (0);
	if (len == 1)
	{
		if (check_no_sep(maillons->output) && str_cmp(maillons->command, "exit") && check_builtin(maillons->args) == 0)
			do_exit(maillons->args[1], garbage, 0);
		else
			pipex_one(maillons, env, garbage);
	}
	else if (len != 1)
		pipex_multiple(len, garbage, 0, wstatus);
	return (0);
}
/*
int	pipex(t_maillons *maillons, char ***env, t_garbage *garbage)
{
	int	len;
	int	wstatus;

	wstatus = 0;
	len = ft_strlen_maillons(maillons);
	if (len == 0)
		return (0);
	if (len == 1)
	{
		if (find_if_have_output(maillons-> output, ">") != 1 && find_if_have_output(maillons -> output, "<") != 1 && (check_echo(maillons->args, 0, 0, 1) == 0 || check_builtin(maillons->args) == 0))
		{
			check_if_builtin(garbage->new_env, \
			&(garbage->new_env), 0, garbage);
			check_echo(garbage->maillons->args, 0, 0, 0);
		}
		else
			pipex_one(maillons, env, garbage);
	}
	else if (len != 1)
		pipex_multiple(len, garbage, 0, wstatus);
	return (0);
}
*/