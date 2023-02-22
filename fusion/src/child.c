/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:27:51 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/19 17:41:48 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code[2];

int	check_access(t_maillons *maillons)
{
	t_maillons *tmp;

	tmp = maillons;
	while (maillons)
	{
		if (check_builtin(maillons->args) == 2)
			return (1);
		if (check_echo(maillons->args, 0, 0, 1) == 0
			|| check_builtin(maillons->args) == 0)
			maillons = maillons->next;
		if (maillons->command != NULL
			&& access(maillons->command, F_OK | X_OK) != 0)
		{
			g_exit_code[0] = 127;
			s_fd("bash: ", 2);
			s_fd(maillons->command, 2);
			s_fd(": command not found\n", 2);
			maillons = tmp; // restaurer l'état initial de maillons
			return (1);
		}
		else
			maillons = maillons->next;
	}
	maillons = tmp; // restaurer l'état initial de maillons
	dprintf(2, "maillons->file_name = %s\n", maillons->command);
	return (0);
}

int	check_echo(char **args, int cmp, int i, int execute)
{
	while (args && args[cmp])
	{
		while (args[cmp][i])
		{
			if (args[cmp][0] == '-')
			{
				while (args[cmp][i] && args[cmp][i] == 'n')
					i++;
				if (args[cmp][i] == 'e' || args[cmp][i] == 'E')
					return (1);
			}
			if (args[cmp][i])
				i++;
		}
		i = 0;
		cmp++;
	}
	if (args[0] && str_cmp(args[0], "echo") == 1)
	{
		if (execute == 0)
			do_echo(&args[1]);
		return (0);
	}
	return (1);
}

int	first_pipe_check(char *line)
{
	int	i;

	i = 0;
	while ((line[i] > 7 && line[i] < 14) || line[i] == 32)
		i++;
	if (line[i] == '|')
	{
		s_fd("bash: syntax error near unexpected token `|'\n", 2);
		g_exit_code[0] = 2;
		return (1);
	}
	return (0);
}

int	after_pipe(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '|')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '\0')
			{
				s_fd("minishell: syntax error near unexpected token `|'\n", 2);
				g_exit_code[0] = 2;
				return (g_exit_code[0]);
			}
		}
		i++;
	}
	return (0);
}

int	only_white_space(char *line_read)
{
	int	i;

	i = 0;
	while (line_read[i])
	{
		if (line_read[i] != ' ' )
			return (0);
		i++;
	}
	return (1);
}
