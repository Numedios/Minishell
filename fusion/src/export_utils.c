/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:22:11 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/20 22:26:02 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code[2];

int	str_len_env(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '+' || str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	c_copy;

	if (s == NULL)
		return (NULL);
	c_copy = (unsigned char) c;
	i = 0;
	if (c_copy == 0)
		return ((char *)&s[ft_strlen((char *)s)]);
	while (s[i])
	{
		if (s[i] != c_copy)
			i++;
		else
			return ((char *)&s[i]);
	}
	return (NULL);
}

int	check_if_tab_exist(char *tab, char **env)
{
	int	len_tab;
	int	len_env;
	int	i;

	if (!env)
		return (0);
	len_tab = ft_strlen(tab);
	i = 0;
	while (env && env[i])
	{
		len_env = ft_strlen(env[i]);
		if (len_tab != len_env || ft_strncmp(env[i], tab, len_tab) != 0)
			i++;
		else
			return (1);
	}
	return (0);
}

int	parsing_of_export(char *tab, char **env_copy, int *a, int *j)
{
	if (ft_strchr(tab, '=') == NULL)
	{
		printf("export: `%s': not a valid identifier\n", tab);
		g_exit_code[0] = 1;
		return (1);
	}
	(*a) = parse_export(tab, 0, 1);
	if ((*a) == 1)
	{
		printf("export: `%s': not a valid identifier\n", tab);
		g_exit_code[0] = 1;
		return (1);
	}
	if (env_copy && (*a) == 2)
	{
		do_env(env_copy);
		return (1);
	}
	if (env_copy && check_if_tab_exist(tab, env_copy) == 1)
	{
		printf("export: '%s' : already defined\n", tab);
		return (1);
	}
	if (env_copy)
		(*j) = what_to_do(tab, env_copy);
	return (0);
}

int	what_to_do(char *tab, char **env)
{
	int	len_tab;
	int	len_env;
	int	i;
	int	j;

	j = 0;
	i = 0;
	len_tab = str_len_env(tab);
	while (env && env[j])
	{
		len_env = str_len_env(env[j]);
		while (tab[i] == env[j][i])
		{
			if (env[j][i] == '=' || env[j][i] == '+')
				break ;
			i++;
		}
		if (i == len_env && len_env == len_tab
			&& (tab[i] == '=' || tab[i] == '+'))
			return (j);
		j++;
		i = 0;
	}
	return (-1);
}
