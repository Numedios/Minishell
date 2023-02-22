/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:40:14 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/21 14:06:49 by zhamdouc         ###   ########.fr       */
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
	return (1);
}

int	check_builtin(char **args)
{
	int	cmp;
	int	sign;

	sign = 0;
	cmp = 0;
	while (args && args[cmp])
	{
		if (args[cmp][0] == '-')
			sign = 1;
		cmp++;
	}
	if (sign != 1 && control_builtin(args, cmp) == 0)
		return (0);
	if (args[0] && str_cmp(args[0], "exit") == 1)
	{
		if (cmp < 3)
			return (0);
		else
		{
			g_exit_code[0] = 130;
			s_fd("exit\nbash: exit: too many arguments\n", 2);
			return (2);
		}
	}
	return (1);
}

static void	first_loop(int *j, int *sign, t_garbage *g)
{
	(*j) = 0;
	(*sign) = 0;
	while (g->maillons->args && g->maillons->args[(*j)])
	{
		if (g->maillons->args[(*j)][0] == '-')
			(*sign) = 1;
		(*j)++;
	}
}

static void	second_loop(char ***new_env, int i, t_garbage *g, char **env)
{
	int	j;

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
}

int	check_if_builtin(char **env, char ***new_env, int i, t_garbage *g)
{
	int	j;
	int	sign;

	first_loop(&j, &sign, g);
	if (g->maillons->args[0]
		&& str_cmp(g->maillons->args[0], "exit") == 1 && j < 3)
	{
		dprintf(2, "do_exit\n");
		return (do_exit(g->maillons->args[1], g), 0);
	}
	if (sign != 1 && g->maillons->args[0]
		&& str_cmp(g->maillons->args[0], "export") == 1)
	{
		second_loop(new_env, i, g, env);
		return (0);
	}
	if (g->maillons->args[0]
		&& str_cmp(g->maillons->args[0], "cd") == 1 && j == 2)
		return (do_cd(new_env, g->maillons->args[1]), 0);
	if (sign != 1)
		return (which_builtin(env, i, j, g));
	else
		return (1);
}
