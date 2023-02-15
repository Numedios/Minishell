/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:10:42 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/15 16:24:01 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//gerer $?
// retirer les autres

/*
SITUATION DU DELETE DOLLAR
pour linstant je supprime dans les doubes quotes correctement, a tester plus serieusement
faire plein de test
tetser dans differetes situations le $?
*/

char	*apply_delete(int i, int skip, char *tab)
{
	while (tab[i - skip])
	{
		if (tab[i] != '\0')
		{
			tab[i - skip] = tab[i];
			i++;
		}
		else
		{
			tab[i - skip] = '\0';
			break ;
		}
	}
	return (tab);
}

char	*found_it_delete(char *tab, char **new_env, t_index *index, int *skip)
{
	int	i;

	i = index->a;
	while (tab[i])
	{
		if (tab[i] == '\'' || tab[i] == '"' || tab[i] == ' ' || tab[i] == '-' || tab[i] == '!' || tab[i] == '@' || tab[i] == '#' || tab[i] == '$' || tab[i] == '%' || tab[i] == '^' || tab[i] == '&' || tab[i] == '*' || tab[i] == '(' || tab[i] == ')' || tab[i] == '{' || tab[i] == '}' || tab[i] == '[' || tab[i] == ']' || tab[i] == '|' || tab[i] == ';' || tab[i] == ':' || tab[i] == '<' || tab[i] == '>' || tab[i] == '?' || tab[i] == '/'|| tab[i] == '~' || tab[i] == '\\')
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
		while (tab[(*i)] == '$' && (tab[(*i) + 1] != '\0' && tab[(*i) + 1] != ' ' && tab[(*i) + 1] != '"' && tab[(*i) + 1] != '\''))// skip tout les espaces
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

char	*one_dollar_or_more_delete(char *tab, int *i, char **new_env, t_index *index)// pas encpre comfigurer pour delete 
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

char	*delete_dollar(char *tab, char **new_env, int i, int skip)
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
		tab = one_dollar_or_more_delete(tab, &i, new_env, &index);
		if (i == -1)
			i = 0;
		else if (tab && tab[i] != '\0')
			i++;
	}
	return (tab);
}
