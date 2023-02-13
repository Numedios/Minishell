/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:10:42 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/13 20:50:19 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//gerer $?
// retirer les autres

int	check_dollar(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] != '\0')
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
/*
void	in_double_quote(char **new_line, char *line, int *i, int *j)
{
	while (line && line[(*i)] != '\0' && line [(*i)] == '"')//faire possiblement attention au cas il la quote n'est pas ferme 
	{
		(*new_line)[(*j)] = line[(*i)];
		(*j)++;
		(*i)++;
		while(line && line[(*i)] != '\0' && line[(*i)] != '"')
		{
			if (line[(*i)] == '$')
			{
				while (line && line[(*i)] != '\0' && line[(*i)] != ' ' && line[(*i)] != '"' && line[(*i)] != '\'')// et des autres espaces
					(*i)++;
			}
			else
			{
				(*new_line)[(*j)] = line[(*i)];
				(*j)++;
				(*i)++;
			}
		}
		if (line && line[(*i)] != '\0')
		{
			(*new_line)[(*j)] = line[(*i)];
			(*j)++;
			(*i)++;
		}
	}
}


char	*delete_dollar(char *line)
{
	int		i;
	int		j;
	char	*new_line;
	//char	*final_line; pour eventuellement faire un str_len de new line a la fin et copy seulement la partie qui nous interessse dans new_line car on a trop malloc

	j = check_dollar(line);
	i = 0;
	if (j == 0)
		return (line);
	j = 0;
	new_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
	//il faut garder le dollar seulement quand on est dans un simple quote qui est en dehors d'une double quote
	while (line && line[i])
	{
		in_double_quote(&new_line, line, &i, &j);
		while (line && line[i] != '\0' && line [i] == '\'')
		{
			new_line[j] = line[i];
			j++;
			i++;
			while (line && line[i] != '\0' && line[i] != '\'')
			{
				new_line[j] = line[i];
				j++;
				i++;
			}
			if (line && line[i] != '\0')
			{
				new_line[j] = line[i];
				j++;
				i++;
			}
		}
		while (line && line[i] != '\0' && line[i] != '\'' && line [i] != '"')
		{
			if (line[i] == '$')
			{
				while (line && line[i] != '\0' && line[i] != ' ' && line[i] != '"' && line[i] != '\'')// et des autres espaces
					i++;
			}
			if (line && line[i] != '\0')
			{
				new_line[j] = line[i];
				j++;
				i++;
			}
		}
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
}
*/



/*
SITUATION DU DELETE DOLLAR
pour linstant je supprime dans les doubes quotes correctement, a tester plus serieusement
faire plein de test
*/

char *apply_delete(int i, int skip, char *tab)
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
			return (tab);//verifier le cas ou le dollars n'est pas retrouve il faut faire avanceer i et continuer de chercher si il y a un autre dollar dans les guillemet par exemple
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

char	*found_dollar_inquote_delete(char *tab, int *i, char ** new_env, t_index *index)//peut etre pas besoin de renvoyer un char* ou alors il faut envoyer l'adresse de tab
{
	int	skip;

	skip = 0;
	(*i)++;
	while (tab[(*i)] && tab[(*i)] != '"' /*&& tab[(*i)] != '\''*/)
	{
		while (tab[(*i)] == '$' && tab[(*i) + 1] == '$')
			i++;
		while (tab[(*i)] == '$')
		{
			skip++;
			index->a = (*i) + 1;
			//dprintf(2, "index->a = %d\nindex->j =%d\n ", index->a, index->j);
			tab = found_it_delete(tab, new_env, index, &skip);
			//dprintf(2, "index->a = %d\nindex->j = %d", index->a, index->j);
			if (index->j != -1)
				(*i) = skip + (*i);
			skip = 0;
		}
		(*i)++;
	}
	return (tab);
}

char	*one_dollar_or_more_delete(char *tab, int *i, char ** new_env, t_index *index)// pas encpre comfigurer pour delete 
{
	int	skip;

	skip = 0;
	while (tab[(*i)] && tab [(*i) + 1] != '\0' && tab[(*i)] == '$')
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
			break;
		skip = 0;
	}
	return (tab);
}

char	*delete_dollar(char *tab, char **new_env)//peu etre possible de pas renvoyer un char mais il faut dans ce cas envoyer l'adresse de tab
{
	int		i;
	int		skip;
	t_index	index;

	skip = check_dollar(tab);
	i = 0;
	if (skip == 0)
		return (tab);
	skip = 0;
	while (tab && tab[i] != '\0')
	{
		if (tab[i] == '"')
			tab = found_dollar_inquote_delete(tab, &i, new_env, &index);
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
		else
			i++;
	}
	return (tab);
}
