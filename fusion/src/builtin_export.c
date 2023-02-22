/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:12 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/22 18:47:52 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_value(char *tab, int i, int a)
{
	if (tab[i] == '+')
	{
		a = 3;
		i = i + 2;
	}
	else
		i++;
	if (tab && (tab[i] == '\0' || tab[i] == ' ' || (tab[i] < 14 && tab[i] > 7)))
	{
		if (a == 3)
			return (5);
		else
			return (4);
	}
	while (tab && tab[i])
	{
		i = skip_quote(tab, i);
		if (i == -1)
			return (1);
		i++;
	}
	return (a);
}

int	parse_export(char *tab, int i, int a)
{
	while (tab && tab[i] == ' ')
		i++;
	if (!tab)
		return (2);
	if (ft_isdigit(tab[i]) == 2)
		return (1);
	while (tab && tab[i])
	{
		if ((tab[i] == '+' && tab[i + 1] != '=') || tab[0] == '=')
			return (1);
		if (tab[i] == '+' && tab[i + 1] == '=' && i == 0)
			return (1);
		if ((tab[i] == '+' && tab[i + 1] == '=') || tab[i] == '=')
		{
			a = parse_value(tab, i, 0);
			break ;
		}
		if (tab[i] == ' ' || (tab[i] < 14 && tab[i] > 7))
			return (1);
		if ((tab[i] > 32 && tab[i] < 48) || (tab[i] > 57 && tab[i] < 65)
			|| (tab[i] > 90 && tab[i] < 97) || (tab[i] > 122 && tab[i] < 127))
			return (1);
		i++;
	}
	return (a);
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

static int	str_len_tab(char **env_copy)
{
	int	i;

	i = 0;
	while (env_copy && env_copy[i])
		i++;
	return (i);
}

char	**do_export(char *tab, char **env_copy, int i, t_garbage *g)
{
	int		j;
	char	**new_env;
	int		a;

	if (parsing_of_export(tab, env_copy, &a, &j) == 1)
		return (env_copy);
	if (env_copy && j != -1)
	{
		env_copy = replace_value(j, a, tab, env_copy);
		return (env_copy);
	}
	if (check_if_tab_exist(tab, env_copy) != 1 && a == 3)
		return (env_copy);
	new_env = malloc ((str_len_tab(env_copy) + 2) * sizeof(char *));
	if (new_env == NULL)
		return (free_garbage_env_exit(g ,1), NULL);
	i = 0;
	while (env_copy && env_copy[i])
	{
		new_env[i] = ft_strdup_const(env_copy[i], g);
		i++;
	}
	new_env = new_value(i, a, tab, new_env);
	if (new_env == NULL)
		return (free_garbage_env_exit(g, 1) ,NULL);
	new_env[i + 1] = NULL;
	return (ft_free_tab(env_copy), new_env);
}


// inishell > export yo=yooo y=yooo yooo=yooo
// Minishell > unset y
// Minishell > env
