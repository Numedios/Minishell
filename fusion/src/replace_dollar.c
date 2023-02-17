/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:09:08 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 16:24:51 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/*test a faire : echo $'hola'       echo $"hola"    echo $      
echo $hol (hol n'existe pas)        echo $$SYSTEMD_EXEC_PID
*/
//$"HOME" doit devenir HOME

extern int	g_exit_code[2];

static char	*apply_the_change(char *tab, char **env, t_index *index, int skip)
{
	index->j = research(skip, index->a, tab, env);
	if (index->j != -1)
	{
		if (index->j == -2)
			tab = interrogation(tab, env, skip, (*index));
		else
			tab = do_replace(tab, env, skip, (*index));
	}
}

char	*found_it(char *tab, char **new_env, t_index *index, int *skip)
{
	int	i;

	i = index->a;
	while (tab[i])
	{
		if (tab[i] == ' ' || (tab[i] < 14 && tab[i] > 7)
			|| (tab[i] > 32 && tab[i] < 48) || (tab[i] > 57 && tab[i] < 65)
			|| (tab[i] > 90 && tab[i] < 97) || (tab[i] > 122 && tab[i] < 127))
		{
			tab = apply_the_change(tab, new_env, index, (*skip));
			return (tab);
		}
		(*skip)++;
		i++;
	}
	tab = apply_the_change(tab, new_env, index, (*skip));
	return (tab);
}

static int	check_in_quote(char *tab, int i)
{
	if (tab[i] == '$' && ((tab[i + 1] > 14 || tab[i + 1] < 7)
			&& (tab[i + 1] < 32 || tab[i + 1] > 47)
			&& (tab[i + 1] < 57 || tab[i + 1] > 65)
			&& (tab[i + 1] < 90 || tab[i + 1] > 97)
			&& (tab[i + 1] < 122 || tab[i + 1] > 127)
			&& tab[i + 1] != '\0' && tab[i + 1] != ' '
			&& tab[i + 1] != '"' && tab[i + 1] != '\''))
	{
		return (0);
	}
	else
		return (1);
}

char	*found_dollar_inquote(char *tab, int *i, char **new_env, t_index *index)
{
	int	skip;

	skip = 0;
	(*i)++;
	while (tab[(*i)] && tab[(*i)] != '"')
	{
		while (tab[(*i)] == '$' && tab[(*i) + 1] == '$')
			(*i)++;
		while (check_in_quote(tab, (*i)) == 0)
		{
			skip++;
			index->a = (*i) + 1;
			tab = found_it(tab, new_env, index, &skip);
			if (index->j == -1)
				(*i) = skip + (*i);
			skip = 0;
		}
		(*i)++;
	}
	return (tab);
}

char	*replace_dollar(char *tab, char **new_env, int i, int skip)
{
	t_index	index;

	if (check_dollar(tab))
		return (tab);
	while (tab && tab[i] != '\0')
	{
		if (tab[i] == '"')
			tab = found_dollar_inquote(tab, &i, new_env, &index);
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
		tab = one_dollar_or_more(tab, &i, new_env, &index);
		if (i == -1)
			i = 0;
		else
			i++;
	}
	return (tab);
}
