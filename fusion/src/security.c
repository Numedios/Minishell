/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:40:14 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/20 13:57:32 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code[2];

int	check_builtin(char **args)
{
	int	cmp;
	int	i;

	cmp = 0;
	i = 0;
	while (args && args[cmp])
	{
		if (args[cmp][0] == '-')
			return (1);
		cmp++;
	}
	if (args[0] && str_cmp(args[0], "cd") == 1 && cmp == 2)
		return (0);
	if (args[0] && str_cmp(args[0], "env") == 1)
		return (0);
	if (args[0] && str_cmp(args[0], "pwd") == 1)
		return (0);
	if (args[0] && str_cmp(args[0], "exit") == 1)
	{
		if (cmp < 3)
			return (0);
		else
		{
			g_exit_code[0] = 130;
			dprintf(2, "exit\nbash: exit: too many arguments\n");
			return (2);
		}
	}
	if (args[0] && str_cmp(args[0], "unset") == 1)
		return (0);
	if (args[0] && str_cmp(args[0], "export") == 1)
		return (0);
	return (1);
}

int	which_builtin(char **args, char **env, int i, int cmp, t_garbage *garbage)
{
	if (args[0] && str_cmp(args[0], "cd") == 1 && cmp == 2)
		return (do_cd(env, args[1]), 0);
	if (args[0] && str_cmp(args[0], "env") == 1)
		return (do_env(env), 0);
	if (args[0] && str_cmp(args[0], "pwd") == 1)
		return (do_pwd(), 0);
	if (args[0] && str_cmp(args[0], "exit") == 1 && cmp < 3)
		return (do_exit(args[1], garbage), 0);
	if (args[0] && str_cmp(args[0], "unset") == 1)
	{
		while (args[++i])
			do_unset(args[i], env, 0, 0);
		return (0);
	}
	return (1);
}

int	check_if_builtin(char **args, char **env, char ***new_env, int i, t_garbage *garbage)
{
	int	cmp;

	cmp = 0;
	while (args && args[cmp])
	{
		if (args[cmp][0] == '-')
			return (1);
		cmp++;
	}
	if (args[0] && str_cmp(args[0], "export") == 1)
	{
		while (args[++i])
		{
			cmp = 0;
			while (args[i][cmp] && args[i][cmp] != '=')
				cmp++;
			if (args[i][cmp] == '=')
			{
				(*new_env) = do_export(args[i], env, 0, 0);
				env = (*new_env);
			}
		}
		return (0);
	}
	return (which_builtin(args, env, i, cmp, garbage));
}

int	check_if_exit(char **args, char **env, t_garbage *garbage)
{
	int	cmp;
	int	i;

	cmp = 0;
	i = 0;
	while (args && args[cmp])
	{
		if (args[cmp][0] == '-')
			return (1);
		cmp++;
	}
	if (args[0] && str_cmp(args[0], "exit") == 1 && cmp < 3)
		return (do_exit(args[1], garbage), 0);
	return (1);
}
//cmp = 0 et i = 0

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
