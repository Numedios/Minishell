/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakariyahamdouchi <zakariyahamdouchi@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:14:46 by sbelabba          #+#    #+#             */
/*   Updated: 2023/01/19 22:33:59 by zakariyaham      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_line(int fd)
{
	int			rd;
	char		*line;
	static char	buf[BUFFER_SIZE + 1];

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	rd = BUFFER_SIZE;
	line = ft_strjoin_gnl(line, buf);
	while (rd == BUFFER_SIZE && check_end(line) == 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd < 0)
			return (NULL);
		buf[rd] = '\0';
		line = ft_strjoin_gnl(line, buf);
	}
	if (!line[0])
	{
		free(line);
		return (NULL);
	}
	else
		get_line(line, buf);
	return (line);
}
