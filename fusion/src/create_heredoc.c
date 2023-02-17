/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:28 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/13 18:58:55 by zhamdouc         ###   ########.fr       */
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

int	heredoc(char *stop)
{
	int		pipe_fd[2];
	char	*str;
	char buf[1000];

	create_heredoc(pipe_fd);
	str = NULL;
	while (1)
	{
		str = readline("> ");
		if (g_exit_code[1] == 7)
		{
			return (-9);
		}
		if (ft_strcmp(stop, str))
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
	//read(pipe_fd[0], buf, 500);
	//printf("buf = %s\n", buf);
	return (pipe_fd[0]);
}

void	sigint_heredoc(int unused)
{
	(void) unused;
	g_exit_code[1] = 7;
	write(2, "\n", 1);
	close(0);
}

void	find_all_heredoc(t_maillons *maillons) //remttre la fonction des signaux du parent, que se passe il apres ctrl+c 
{
	t_input_output	*tmp;
	int				copy_fd;
	
	copy_fd = dup(0);
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
				if (maillons->heredoc == -9)
				{
					dprintf(2, "fin heredoc");
					dup2(copy_fd, 0);
					g_exit_code[1] = 0;//pour ne pas bloquer au prochain prompt
					return ;
				}
			}
			maillons -> output = maillons -> output -> next;
		}
		maillons->output = tmp;
		maillons = maillons -> next;
	}
	close(copy_fd);
	g_exit_code[1] = 0;
}
