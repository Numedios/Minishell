/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_de_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:44:01 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/19 15:26:51 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//test : <a ls >a | < b ls > b
//que faire si le fichier in n'exise pas ??
// maillons -> command = /usr/bin/ls
//maillons -> args = a commmand et les options
//probleme avec le heredoc en premiere commande

extern int	g_exit_code[2];
//gerer les enfants avec g_exit_code[1] = 2; si g_exit_code[1] == 3
// alors exit(0) ou faire un if dans les enfants pour directement exit
// si g_exit_code[1] == 3;

void	signal_quit_child(int useless)
{
	if (useless == SIGINT)
	{
		write(1, "\n", 1);
		g_exit_code[0] = 130;
	}
	if (useless == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		g_exit_code[0] = 131;
	}
}
