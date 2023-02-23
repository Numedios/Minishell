/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:06:46 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 17:32:26 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* join et rajoute un \ entre path et add*/

int	quote_close_2(char *str)
{
	char	c;
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
					i++;
			if (str[i] != c)
				return (0);
		}
		i++;
	}
	return (1);
}

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
