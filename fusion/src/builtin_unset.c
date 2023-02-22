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

static int ft_tablen(char **env_copy)
{
	int i = 0;

	if(!env_copy)
		return (0);
	while (env_copy[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
// calculer n
	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	// if (s1[i] != '\0' && s2[i] != '=')
	// 	return (1);
	return (0);
}

int	ft_varcompare(char *s1, char *s2)
{
	int i = 0;
	int size = 0;
	
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

char **do_unset(char *tab, char **env_copy, int i, t_garbage *garbage)
{
	int index_var = 0;

	(void)garbage;
	while (env_copy[index_var])
	{
		if (!ft_varcompare(tab, env_copy[index_var]))
			break;
		index_var++;
	}
	if (!env_copy[index_var])
		return(env_copy);
	// 	return (env_copy);
	//printf("index_var = %d", index_var);
	i = 0;
	int j = 0;
	char **new_env = malloc(sizeof(char *) * (ft_tablen(env_copy)));
	while (i < ft_tablen(env_copy))
	{
		if (!ft_varcompare(tab, env_copy[i]))
		{
			printf("env_copy[i] = %s", env_copy[i]);
			i++;
		}
		else
		{
			new_env[j++] = ft_strdup(env_copy[i]);
			i++;
		}
	}
	new_env[j] = '\0';
	ft_free_tab(env_copy);
	return (new_env);
}

// void	do_unset(char *tab, char **env_copy, int i, t_garbage *garbage)
// {
// 	env_copy = ft_unset(tab, env_copy, i, garbage);
// }
// void	do_unset(char *tab, char **env_copy, int i, t_garbage *garbage)
// {
// 	int	n;

// 	n = 0;
// 	if (tab == NULL)
// 		return ;
// 	if (!env_copy || env_copy[i] == NULL)
// 		return ;
// 	while (tab && tab[n])
// 		n++;
// 	while (ft_strncmp(tab, env_copy[i], n) == 1)
// 		i++;
// 	//printf(" i = %d\n", i);
// 	if(env_copy[i] == NULL)
// 		return ;
// 	i = 0;
// 	while (env_copy[i])
// 	{
// 		if (ft_strncmp(tab, env_copy[i], n) == 0)
// 		{
// 			free(env_copy[i]);
// 			env_copy[i] = ft_strdup(env_copy[i + 1]);
// 			found_line++;
// 		}
// 		if (found_line == 1)
// 		{
// 			free(env_copy[i]);
// 			env_copy[i] = ft_strdup(env_copy[i + 1]);
// 		}
// 		i++;
// 	}
// 	env_copy[i-1] = '\0';
// 	//printf("size = %d\n", i);
// }
