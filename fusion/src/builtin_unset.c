/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:17 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/22 22:09:51 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_tablen(char **env_copy)
{
	int	i;

	i = 0;
	if (!env_copy)
		return (0);
	while (env_copy[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_varcompare(char *s1, char *s2)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s2[size] != '=')
		size++;
	if (ft_strlen(s1) == size)
	{
		while (i < size)
		{
			if (s1[i] != s2[i])
				return (1);
			i++;
		}
	}
	else
		return (1);
	return (0);
}

char	**do_unset(char *tab, char **env_copy, int i, t_garbage *garbage)
{
	int		index_var;
	int		j;
	char	**new_env;

	j = 0;
	new_env = NULL;
	index_var = 0;
	(void)garbage;
	while (env_copy[index_var])
	{
		if (!ft_varcompare(tab, env_copy[index_var]))
			break ;
		index_var++;
	}
	if (!env_copy[index_var])
		return (env_copy);
	i = 0;
	new_env = malloc(sizeof(char *) * (ft_tablen(env_copy)));
	while (i < ft_tablen(env_copy))
	{
		if (!ft_varcompare(tab, env_copy[i]))
			i++;
		else
		{
			new_env[j++] = ft_strdup(env_copy[i]);
			i++;
		}
	}
	new_env[j] = '\0';
	return (ft_free_tab(env_copy), new_env);
}
