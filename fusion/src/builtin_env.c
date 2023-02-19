/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:07 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/13 11:30:17 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//possibilite de creer sa propre env
//comparer toutes les lignes pour savoir laquelle imprimer en premier
void	do_env(char **env)
{
	int	i;

	i = 0;
	if (env == NULL)
	{
		printf("vide\n");
		return ;
	}
	while (env[i])
	{
		s_fd(env[i], 1);
		s_fd("\n", 1);
		i++;
	}
}

char	**my_env(char **env)
{
	int		i;
	char	**env_copy;

	i = 0;
	if (env[i] == NULL)
		return (NULL);
	while (env[i])
		i++;
	env_copy = malloc((i + 1) * sizeof(char *));
	if (env_copy == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_copy[i] = ft_strdup_const(env[i]);
		if (env_copy[i] == NULL)
			return (NULL);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}
