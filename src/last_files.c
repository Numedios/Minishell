/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 23:33:22 by sbelabba          #+#    #+#             */
/*   Updated: 2023/02/22 23:33:23 by sbelabba         ###   ########.fr       */
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

char	*ft_strdup_g(char *str, t_garbage *g)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		free_garbage_env_exit(g, 1);
	while (str && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	pipex_one_condition(t_maillons *m, char ***e, t_garbage *g)
{
	if (check_if_exit(m->args, g) == 0)
		return (1);
	if (check_if_builtin(*e, e, 0, g) == 0)
		return (1);
	else if (check_echo(g->maillons->args, 0, 0, 0) == 0)
		return (1);
	return (0);
}

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
