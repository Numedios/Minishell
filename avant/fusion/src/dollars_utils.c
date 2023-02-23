/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:20:57 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 16:22:06 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	research(int skip, int a, char *tab, char **new_env)
{
	int	len_env;
	int	i;

	i = 0;
	if (skip == 1 && tab[a] == '?')
		return (-2);
	while (new_env[i])
	{
		len_env = str_len_env(new_env[i]);
		if ((skip - 1) != len_env
			|| ft_strncmp(new_env[i], &tab[a], (skip - 1)) != 0)
			i++;
		else
			return (i);
	}
	return (-1);
}

char	*one_dollar_or_more(char *tab, int *i, char **new_env, t_index *index)
{
	int	skip;

	skip = 0;
	while (tab[(*i)] && tab [(*i) + 1] != '\0'
		&& tab[(*i)] == '$' && tab[(*i) + 1] != ' ')
	{
		skip++;
		index->a = (*i) + 1;
		tab = found_it(tab, new_env, index, &skip);
		skip = 0;
	}
	return (tab);
}
