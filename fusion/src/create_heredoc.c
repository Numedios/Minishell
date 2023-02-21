/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:28 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/20 12:58:04 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code[2];

void	create_heredoc(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
}

void	print_minishell_warning_heredoc(char *stop)
{
	write(2, "minishell: warning wanted :", 27);
	write(2, stop, ft_strlen(stop));
	write(2, "\n", 1);
}

// void	prompt_eof(void)
// {
// 	g_exit_code[1] = 8;
// 	// write(2, "\n", 1);
// 	printf("minishell: warning eof\n");
// 	close (0);
// }

int	heredoc(char *stop)
{
	int		pipe_fd[2];
	char	*str;

	create_heredoc(pipe_fd);
	str = NULL;
	while (1)
	{
		str = readline("> ");
		if (g_exit_code[1] == 7)
			break ;
		if (ft_strcmp(stop, str) || str == NULL)
		{
			if (!str)
				print_minishell_warning_heredoc(stop);
			break ;
		}
		else
		{
			write(pipe_fd[1], str, ft_strlen(str));
			write(pipe_fd[1], "\n", 1);
			free(str);
		}
	}
	free(str);
	return (close(pipe_fd[1]), pipe_fd[0]);
}
