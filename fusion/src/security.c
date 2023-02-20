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

static int	control_builtin(char **args, int cmp)
{
	if (args[0] && str_cmp(args[0], "cd") == 1 && cmp == 2)
		return (0);
	if (args[0] && str_cmp(args[0], "env") == 1)
		return (0);
	if (args[0] && str_cmp(args[0], "pwd") == 1)
		return (0);
	if (args[0] && str_cmp(args[0], "unset") == 1)
		return (0);
	if (args[0] && str_cmp(args[0], "export") == 1)
		return (0);
}

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
	if (control_builtin(args, cmp) == 0)
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
	return (1);
}

int	which_builtin(char **env, int i, int cmp, t_garbage *g)
{
	if (g->maillons->args[0]
		&& str_cmp(g->maillons->args[0], "cd") == 1 && cmp == 2)
		return (do_cd(env, g->maillons->args[1]), 0);
	if (g->maillons->args[0] && str_cmp(g->maillons->args[0], "env") == 1)
		return (do_env(env), 0);
	if (g->maillons->args[0] && str_cmp(g->maillons->args[0], "pwd") == 1)
		return (do_pwd(), 0);
	if (g->maillons->args[0]
		&& str_cmp(g->maillons->args[0], "exit") == 1 && cmp < 3)
		return (do_exit(g->maillons->args[1], g), 0);
	if (g->maillons->args[0] && str_cmp(g->maillons->args[0], "unset") == 1)
	{
		while (g->maillons->args[++i])
			do_unset(g->maillons->args[i], env, 0, 0);
		return (0);
	}
	return (1);
}

int	check_if_builtin(char **env, char ***new_env, int i, t_garbage *g)
{
	int	j;

	j = 0;
	while (g->maillons->args && g->maillons->args[j])
	{
		if (g->maillons->args[j][0] == '-')
			return (1);
		j++;
	}
	if (g->maillons->args[0] && str_cmp(g->maillons->args[0], "export") == 1)
	{
		while (g->maillons->args[++i])
		{
			j = 0;
			while (g->maillons->args[i][j] && g->maillons->args[i][j] != '=')
				j++;
			if (g->maillons->args[i][j] == '=')
			{
				(*new_env) = do_export(g->maillons->args[i], env, 0, 0);
				env = (*new_env);
			}
		}
		return (0);
	}
	return (which_builtin(env, i, j, g));
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
