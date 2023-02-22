/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:51:41 by sbelabba          #+#    #+#             */
/*   Updated: 2023/02/20 17:51:42 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code[2];


/* crer une fonction qui just strcmp un char avec tout les bultins*/
void	pipex_multiple_check(t_garbage *g, t_maillons *cmd)
{
	if (cmd->heredoc != -1)
		close((cmd)->heredoc);
	if (cmd->command == NULL)
		free_garbage_env_exit(g, g_exit_code[0]);
	else if (check_if_builtin(g->new_env, &(g->new_env), 0, g) == 0)
		free_garbage_env_exit(g, g_exit_code[0]);
	else if (check_echo(g->maillons->args, 0, 0, 0) == 0)
		free_garbage_env_exit(g, g_exit_code[0]);
	else if (access(g->maillons->command, F_OK | X_OK) == -1)
		free_garbage_env_exit(g, g_exit_code[0]);
	else if (execve(cmd->command, cmd->args, g->new_env) == -1)
		perror("execve");
	free_garbage_env_exit(g, 1);
}

void	pipex_multiple_close_pipe(t_garbage *garbage, int len, int i)
{
	if (i > 0 && (garbage)->pipes->pipe[i * 2 - 2])
	{
		close((garbage)->pipes->pipe[i * 2 - 2]);
		(garbage)->pipes->pipe[i * 2 - 2] = -1;
	}
	if (i != (len -1) && (garbage)->pipes->pipe[i * 2 + 1])
	{
		close((garbage)->pipes->pipe[i * 2 + 1]);
		(garbage)->pipes->pipe[i * 2 + 1] = -1;
	}
}

void	handle_child_process(int i, int len, t_garbage *g, t_maillons *cmd)
{
	if ((g->maillons)->command != NULL)
	{
		switch_dup2_fd_in(g->maillons, g->pipes, i);
		switch_dup2_fd_out(g->maillons, g->pipes, i);
	}
	free_all_pipes((len - 1), g->pipes);
	g->pipes = NULL;
	pipex_multiple_check(g, cmd);
}
