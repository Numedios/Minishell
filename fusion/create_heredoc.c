/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:28 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/13 11:26:37 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
char	*ft_strjoin(char *line, char *buf)
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
}*/

extern int	g_exit_code[2];

void	create_heredoc(int *pipe_fd)
{
	//pipe_fd = malloc(sizeof(int) * 2);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
}

int	heredoc(char *stop)
{
	int		pipe_fd[2];
	char	*str;
	char	*comp;

	create_heredoc(pipe_fd);
	comp = ft_strjoin(stop, "\n");
	str = NULL;
	while (1 && g_exit_code[1] != 7)
	{
		write(1, "> ", 2);
		str = get_next_line(1);
		if (ft_strcmp(comp, str))
		{
			free(str);
			break ;
		}
		else
		{
			write(pipe_fd[1], str, ft_strlen(str));
			free(str);
		}
	}
	close(pipe_fd[1]);
	free(comp);
	return (pipe_fd[0]);
}

void	sigint_heredoc(int unused)
{
	(void) unused;
	g_exit_code[1] = 7;
}

void	find_all_heredoc(t_maillons *maillons)
{
	t_input_output	*tmp;

	signal(SIGINT, sigint_heredoc);
	while (maillons)
	{
		tmp = maillons->output;
		while (maillons->output)
		{
			if (ft_strcmp((maillons->output->operator), "<<"))
			{
				if (maillons -> heredoc != -1)
					close(maillons ->heredoc);
				maillons -> heredoc = heredoc(maillons -> output -> file_name);
			}
			maillons -> output = maillons -> output -> next;
		}
		maillons->output = tmp;
		maillons = maillons -> next;
	}
}
