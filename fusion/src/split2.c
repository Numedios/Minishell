/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:15:47 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 18:18:24 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	**ft_split2(char *str, char *sep)
{
	int		i;
	int		j;
	char	**res;
	char	quote;

	i = 0;
	j = 0;
	res = malloc(sizeof(char *) * (count_words2(str, sep) + 1));
	printf("count_word = %d\n", count_words2(str, sep));
	if (!res)
		return (NULL);
	while (str && *str)
	{
		while (*str && !check_sep2(*str, sep))
			str++;
		if (*str && check_sep2(*str, sep))
		{
			res[i] = create_word_all2(str, sep);
			i++;
		}
		while (*str && check_sep2(*str, sep))
		{
			str++;
		}
	}
	res[i] = 0;
	return (res);
}*/

/*
* renvoie 0 si pas entre cote
* renvoie 1 si c'est single cote
* renvoie 2 si double cote
*/

int	is_inquotes(char *str, int pos)
{
	int	i;
	int	s;
	int	d;

	i = 0;
	s = 0;
	d = 0;
	while (str && i <= pos)
	{
		if (s == 0 && d == 0 && str[i] == '\'')
			s = 1;
		else if (d == 0 && s == 0 && str[i] == '\"')
			d = 1;
		else if (s == 1 && d == 0 && str[i] == '\'')
			s = 0;
		else if (d == 1 && s == 0 && str[i] == '\"')
			d = 0;
		i++;
	}
	if (s == 0 && d == 1 && str && str[pos] != '\"')
		return (2);
	else if (s == 1 && d == 0 && str && str[pos] != '\'')
		return (1);
	return (0);
}

int	check_quote2(char c)
{
	return (c == '\'' || c == '\"');
}

/*
* renvoie 1 si c n'est pas un separateur 
* renvoie 0 sinon
*
*/

int	check_sep2(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep && sep[i])
	{
		if (sep[i] == c)
			return (0);
		i++;
	}
	return (1);
}
/*
int count_words2(char *str, char *sep)
{
    int i;
    int word;
    int in_quote;
    char quote;

    in_quote = 1; // 1 pas dans des cote "0" on est dans des cote
    i = 0;
    word = 0;
    while (str && str[i])
    {
        while (is_inquotes(str, i)) // skip tout les sep |
			i++;
        if (str[i] && check_sep2(str[i], sep)) // incremente count si 
			word++;
        while ((str[i] && check_sep2(str[i], sep) ) || is_inquotes(str, i))
			i++;
    }
    return (word);
}*/

int	count_words2(char *str, char *sep)
{
	int	i;
	int	j;

	if (!str)
		return (0);
	i = 0;
	j = 1;
	while (str[i] && !is_inquotes(str, i) && !check_sep2(str[i], sep))
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!is_inquotes(str, i) && !check_sep2(str[i], sep)
			&& check_sep2(str[i + 1], sep))
			j++;
		i++;
	}
	return (j);
}

int	ft_stablen(char *str, int tor, char *sep)
{
	static int	i;
	int			j;

	if (!str)
		return (0);
	if (tor == 0)
		i = 0;
	j = 0;
	while (str[i] && !is_inquotes(str, i) && !check_sep2(str[i], sep))
		i++;
	while (str[i] && (check_sep2(str[i], sep) || is_inquotes(str, i)))
	{
		if (!is_inquotes(str, i) && !check_sep2(str[i], sep))
			j--;
		i++;
		j++;
	}
	return (j);
}

char	*ft_strtab(char *str, int tor, char *sep)
{
	char		*strtab;
	static int	i;
	int			j;

	if (!str)
		return (0);
	if (tor == 0)
		i = 0;
	j = 0;
	strtab = malloc(sizeof(char) * ft_stablen(str, tor, sep) + 1);
	if (!strtab)
		return (0);
	while (str[i] && !is_inquotes(str, i) && !check_sep2(str[i], sep))
		i++;
	while (str[i] && (check_sep2(str[i], sep) || is_inquotes(str, i)))
	{
		if (!is_inquotes(str, i) && !check_sep2(str[i], sep))
			i++;
		else
			strtab[j++] = str[i++];
	}
	strtab[j] = '\0';
	return (strtab);
}

char	**ft_split2(char *str, char *sep)
{
	char	**tab;
	int		count;
	int		i;

	count = count_words2(str, sep);
	if (count == 0)
		return (NULL);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (count--)
	{
		tab[i] = ft_strtab(str, i, sep);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
