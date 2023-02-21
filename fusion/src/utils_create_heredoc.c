/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_create_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:45:50 by sbelabba          #+#    #+#             */
/*   Updated: 2023/02/20 17:45:51 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code[2];

void	sigint_heredoc(int unused)
{
	(void) unused;
	g_exit_code[1] = 7;
	g_exit_code[0] = 130;
	write(2, "\n", 1);
	close(0);
}

void	find_all_heredoc_loop(t_maillons **maillons, int *copy_fd)
{
	t_input_output	*tmp;

	tmp = (*maillons)->output;
	while ((*maillons)->output)
	{
		if (ft_strcmp(((*maillons)->output->operator), "<<"))
		{
			if ((*maillons)->heredoc != -1)
				close((*maillons)->heredoc);
			(*maillons)->heredoc = heredoc((*maillons)->output->file_name);
			if (g_exit_code[1] == 7)
			{
				dup2(*copy_fd, 0);
				break ;
			}
		}
		(*maillons)->output = (*maillons)->output->next;
	}
	(*maillons)->output = tmp;
	(*maillons) = (*maillons)->next;
}

//remttre la fonction des signaux du parent, que se passe il apres ctrl+c 
void	find_all_heredoc(t_maillons *maillons)
{
	int				copy_fd;

	g_exit_code[1] = 9;
	copy_fd = dup(0);
	signal(SIGINT, sigint_heredoc);
	while (maillons && g_exit_code[1] != 7)
		find_all_heredoc_loop(&maillons, &copy_fd);
	close(copy_fd);
}
