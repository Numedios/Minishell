/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:34:40 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/15 17:56:17 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int			len;
	const void	*buf;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	buf = s;
	write(fd, buf, len);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

/* compare renvoie  1 si str == str2 renvoie 0 sinon*/

int	ft_strcmp(char *str, char *str2)
{
	if (!str || !str2)
	{
		if (!str && !str2)
			return (1);
		return (0);
	}
	while (*str || *str2)
	{
		if (*str != *str2)
			return (0);
		str++;
		str2++;
	}
	return (1);
}

char	*ft_strdup(char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	while (str && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	ft_isdigit(int c)
{
	if (47 < c && c < 58)
		return (2);
	else
		return (0);
}
