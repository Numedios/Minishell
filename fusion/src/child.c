/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:27:51 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/19 17:41:48 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code[2];

int	check_access(t_maillons *maillons)
{
	while (maillons)
	{
		if (check_builtin(maillons->args) == 2)
			return (1);
		if (check_echo(maillons->args, 0, 0, 1) == 0
			|| check_builtin(maillons->args) == 0)
			maillons = maillons->next;
		else if (maillons->command != NULL
			&& access(maillons->command, F_OK | X_OK) != 0)
		{
			g_exit_code[0] = 127;
			s_fd("bash: ", 2);
			s_fd(maillons->command, 2);
			s_fd(": command not found\n", 2);
			return (1);
		}
		else
			maillons = maillons->next;
	}
	return (0);
}
