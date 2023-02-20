/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:14:35 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/20 13:58:40 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code[2];

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		if (g_exit_code[1] == 9)
		{
			g_exit_code[1] = 0;
		}
		else
		{
			rl_replace_line("", 0);
			write(1, "\n", 1);
			rl_on_new_line();
			rl_redisplay();
			g_exit_code[0] = 130;
		}
	}
}

void	setup_signal_handlers(void)
{
	if (signal(SIGINT, handle_sig) == SIG_ERR)
	{
		perror("signal failed");
		exit (1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal failed");
		exit (1);
	}
}
