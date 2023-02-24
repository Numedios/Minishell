/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:10:42 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/24 14:24:20 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*found_it_delete(char *tab, char **new_env, t_index *index, int *skip)
{
	int	i;

	i = index->a;
	while (tab[i])
	{
		if (tab[i] == ' ' || (tab[i] < 14 && tab[i] > 7)
			|| (tab[i] > 32 && tab[i] < 48) || (tab[i] > 57 && tab[i] < 65)
			|| (tab[i] > 90 && tab[i] < 97) || (tab[i] > 122 && tab[i] < 127))
		{
			index->j = research(*skip, index->a, tab, new_env);
			if (index->j == -1)
			{
				apply_delete(i, (*skip), tab);
			}
			return (tab);
		}
		(*skip)++;
		i++;
	}
	index->j = research(*skip, index->a, tab, new_env);
	if (index->j == -1)
	{
		apply_delete(i, (*skip), tab);
	}
	return (tab);
}

static int	check_in_quote(char *tab, int i)
{
	if (tab[i] == '$' && ((tab[i + 1] > 14 || tab[i + 1] < 7)
			&& (tab[i + 1] < 32 || tab[i + 1] > 47)
			&& (tab[i + 1] < 57 || tab[i + 1] > 62)
			&& (tab[i + 1] < 91 || tab[i + 1] > 96)
			&& (tab[i + 1] < 123 || tab[i + 1] > 126)
			&& tab[i + 1] != '\0' && tab[i + 1] != ' '
			&& tab[i + 1] != '"' && tab[i + 1] != '\'') && tab[i + 1] != '@')
	{
		return (0);
	}
	else
		return (1);
}

char	*dollar_inquote_del(char *tab, int *i, char **new_env, t_index *index)
{
	int	skip;

	skip = 0;
	(*i)++;
	while (tab[(*i)] && tab[(*i)] != '"')
	{
		while (tab[(*i)] == '$'
			&& (tab[(*i) + 1] == '$' || tab[(*i) + 1] == ' '))
			(*i)++;
		while (check_in_quote(tab, (*i)) == 0)
		{
			skip++;
			index->a = (*i) + 1;
			tab = found_it_delete(tab, new_env, index, &skip);
			if (index->j != -1)
				(*i) = skip + (*i);
			skip = 0;
		}
		(*i)++;
	}
	return (tab);
}

char	*dollar_or_more_del(char *tab, int *i, char **new_env, t_index *index)
{
	int	skip;

	skip = 0;
	while (tab[(*i)] && tab [(*i) + 1] != '\0'
		&& tab[(*i)] == '$' && tab[(*i) + 1] != ' ')
	{
		skip++;
		index->a = (*i) + 1;
		tab = found_it_delete(tab, new_env, index, &skip);
		if (index->j == -1)
		{
			(*i) = -1;
			break ;
		}
		else
			break ;
		skip = 0;
	}
	return (tab);
}

char	*delete_dollar(char *tab, char **new_env, int i)
{
	t_index	index;

	if (check_dollar(tab))
		return (tab);
	while (tab && tab[i] != '\0')
	{
		if (tab[i] == '"')
			tab = dollar_inquote_del(tab, &i, new_env, &index);
		if (tab && tab[i] && tab[i] == '\'')
		{
			i++;
			while (tab && tab[i] != '\0' && tab[i] != '\'' && tab[i] != '\'')
				i++;
			if (tab && tab[i] && tab[i] == '\'')
				i++;
		}
		while (tab && tab[i] != '\0' && tab[i] == '$' && tab[i + 1] == '$')
			i++;
		tab = dollar_or_more_del(tab, &i, new_env, &index);
		if (i == -1)
			i = 0;
		else if (tab && tab[i] != '\0')
			i++;
	}
	return (tab);
}
