/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:41:27 by sbelabba          #+#    #+#             */
/*   Updated: 2022/12/06 15:43:54 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* a mettre dans libft_utils.c*/

int	ft_strncmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	create_heredoc(void)
{
	int	fd;

	fd = open("here_doc", O_CREAT | O_WRONLY | O_EXCL, 0647);
	if (fd == -1)
	{
		perror("open");
		exit (1);
	}
	return (fd);
}

int	heredoc(int argc, char **argv)
{
	int		fd;
	char	*str;
	char	*comp;

	argc--;
	fd = create_heredoc();
	comp = ft_strjoin(ft_strdup(argv[1]), "\n");
	str = NULL;
	while (1)
	{
		write(1, "here_doc> ", 10);
		str = get_next_line(1);
		if (ft_strcmp(comp, str))
		{
			free(str);
			break ;
		}
		else
		{
			write(fd, str, ft_strlen(str));
			free(str);
		}
	}
	free(comp);
	return (close(fd), 1);
}
