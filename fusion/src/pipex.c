/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:20:55 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/19 17:37:35 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code[2];

int	dup_fd(int new_stdin, int new_stdout)
{
	if (dup2(new_stdin, STDIN_FILENO) == -1
		|| dup2(new_stdout, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}

int	pipex(t_maillons *maillons, char ***env, t_garbage *garbage)
{
	int	*pipes;
	int	len;

	len = ft_strlen_maillons(maillons);
	if (check_access(maillons) == 1)
		return (1);
	if (len == 0)
		return (0);
	if (len == 1)
		pipex_one(maillons, env, garbage);
	else if (len != 1)
		pipex_multiple(len, garbage, 0);
	return (0);
}
