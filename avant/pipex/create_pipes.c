/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:17:16 by sbelabba          #+#    #+#             */
/*   Updated: 2022/12/06 15:50:27 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(int *pipes, int i)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
	pipes[i] = pipe_fd[0];
	pipes[i + 1] = pipe_fd[1];
}

int	*create_pipes(int argc)
{
	int	*pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * (argc * 2));
	while (i < argc * 2)
	{
		create_pipe(pipes, i);
		if (!pipes[i] || !pipes[i + 1])
			return (NULL);
		i = i + 2;
	}
	i = 0;
	return (pipes);
}

t_pipes	create_all_pipes(int argc, char **argv, t_data *stock)
{
	t_pipes	pipes;

	pipes.pipe = create_pipes(argc);
	pipes.fd_stdin = open(argv[0], O_RDWR, O_DSYNC, !O_DIRECTORY);
	if (!ft_strncmp("here_doc", argv[0]))
	{
		pipes.fd_stdout = open(argv[ft_strlen_tab(argv) - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644, !O_DIRECTORY);
	}
	else
	{
		pipes.fd_stdout = open(argv[ft_strlen_tab(argv) - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644, !O_DIRECTORY);
	}
	if (!pipes.pipe || pipes.fd_stdin == -1 || pipes.fd_stdout == -1)
	{
		free_tab(stock->path);
		free_tab_tab(stock->cmd);
		free_all_pipes(argc * 2, pipes);
		unlink("here_doc");
		exit (1);
	}
	return (pipes);
}
