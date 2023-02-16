/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakariyahamdouchi <zakariyahamdouchi@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:06:46 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/16 18:47:59 by zakariyaham      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* join et rajoute un \ entre path et add*/

char	*ft_strjoin_pipex(char *path, char *add)
{
	int		i;
	int		j;
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(add) + 2));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (path && path[i])
	{
		res[i] = path[i];
		i++;
	}
	res[i++] = '/';
	while (add && add[j])
		res[i++] = add[j++];
	res[i] = '\0';
	//free(path);
	return (res);
}

int	ft_strlen_const(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	str_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] != s2[i])
		return (0);
	return (1);
}

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
