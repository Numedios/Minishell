/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clean_split_arg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:46:05 by sbelabba          #+#    #+#             */
/*   Updated: 2023/02/20 17:46:06 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	renvoie 1 si str comporte un separateur chercher
*	renvoie 0 si vide ou si elle n'en comporte pas
*/

int	chek_sep_str(char *str, char *sep)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!check_sep(str[i], sep))
			return (1);
		i++;
	}
	return (0);
}

void	create_word_sep(t_split_elem **lst, char *str, int len)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return ;
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	add_end_split_elem(lst, create_split_elem(res));
}

void	handle_redirection(t_split_elem **add, char **str)
{
	if (**str == '<' || **str == '>')
	{
		if (*str && (*str)[1] && **str == (*str)[1])
		{
			create_word_sep(add, *str, 2);
			(*str)++;
		}
		else
			create_word_sep(add, *str, 1);
		(*str)++;
	}
}

void	split_redirection_quote(char **str)
{
	char	quote;

	quote = **str;
	if (quote == '\"' || quote == '\'')
	{
		(*str)++;
		while (**str && **str != quote)
			(*str)++;
	}
	(*str)++;
}

t_split_elem	**split_redirection(char *str, char *sep)
{
	t_split_elem	**add;
	int				i;

	add = malloc(sizeof(*add));
	if (!add)
		return (NULL);
	*add = NULL;
	i = 0;
	while (str && *str)
	{
		handle_redirection(add, &str);
		if (*str && check_sep(*str, "<>"))
		{
			add_end_split_elem(add, create_split_elem(ft_strtab(str, 0, sep)));
			i++;
		}
		while (*str && check_sep(*str, "<>"))
			split_redirection_quote(&str);
	}
	return (add);
}
