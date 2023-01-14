/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:58:40 by sbelabba          #+#    #+#             */
/*   Updated: 2022/12/06 15:49:27 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_end(char	*line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *line, char *buf)
{
	char	*res;
	int		i;
	int		j;	

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buf) + 1));
	if (!res)
		return (NULL);
	while (line && line[i])
	{
		res[i] = line[i];
		i++;
	}
	while (buf[j])
		res[i++] = buf[j++];
	res[i] = '\0';
	free(line);
	return (res);
}

void	get_line(char *line, char *buf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\n')
		i++;
	while (line[i])
	{
		buf[j] = line[i];
		line[i] = '\0';
		i++;
		j++;
	}
	buf[j] = '\0';
}
