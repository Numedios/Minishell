/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:29:20 by sbelabba          #+#    #+#             */
/*   Updated: 2023/02/22 22:05:18 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**replace_value(int j, int a, char *tab, char **env)
{
	int	i;

	i = 0;
	if (a == 0)
	{
		free(env[j]);
		env[j] = ft_strdup(tab);
		return (env);
	}
	if (a == 3)
	{
		while (tab && tab[i] != '=')
			i++;
		i++;
		env[j] = strjoin_and_free(env[j], &tab[i]);
		return (env);
	}
	if (a == 4)
	{
		free(env[j]);
		env[j] = ft_strdup(tab);
		return (env);
	}
	else
		return (env);
}

char	**new_value(int i, int a, char *tab, char **env)
{
	int	j;

	j = 0;
	if (a == 0)
	{
		env[i] = ft_strdup(tab);
		return (env);
	}
	if (env[i] && a == 3)
	{
		while (tab && tab[j] != '=')
			j++;
		j++;
		env[i] = strjoin_and_free(env[i], &tab[j]);
		return (env);
	}
	if (a == 4)
	{
		env[i] = ft_strdup(tab);
		return (env);
	}
	else
		return (env);
}

int	which_builtin(char **env, int i, int cmp, t_garbage *g)
{
	(void)cmp;
	if (g->maillons->args[0] && str_cmp(g->maillons->args[0], "env") == 1)
		return (do_env(env), 0);
	if (g->maillons->args[0] && str_cmp(g->maillons->args[0], "pwd") == 1)
		return (do_pwd(), 0);
	if (g->maillons->args[0] && str_cmp(g->maillons->args[0], "unset") == 1)
	{
		while (env && g->maillons->args[++i])
			g->new_env = do_unset(g->maillons->args[i], g->new_env, 0, g);
		return (0);
	}
	return (1);
}

int	check_if_exit(char **args, t_garbage *garbage)
{
	int	cmp;

	cmp = 0;
	while (args && args[cmp])
	{
		cmp++;
	}
	if (args[0] && str_cmp(args[0], "exit") == 1 && cmp < 3)
		return (do_exit(args[1], garbage), 0);
	return (1);
}
