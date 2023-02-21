/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:07 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/20 13:08:45 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_env(char **env)
{
	int	i;

	i = 0;
	if (env == NULL)
	{
		//printf("\n");
		return ;
	}
	while (env[i])
	{
		s_fd(env[i], 1);
		s_fd("\n", 1);
		i++;
	}
}

char	**my_env(char **env, t_garbage *garbage)
{
	int		i;
	char	**env_copy;

	i = 0;
	if (!env || env[i] == NULL)
		return (NULL);
	while (env[i])
		i++;
	env_copy = malloc((i + 1) * sizeof(char *));
	if (!env_copy)
		free_garbage_env_exit(garbage, 0);
	i = 0;
	while (env[i])
	{
		env_copy[i] = ft_strdup_const(env[i]);
		if (env_copy[i] == NULL)
		{
			ft_free_tab(env_copy);
			free_garbage_env_exit(garbage, 0);
		}
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}
