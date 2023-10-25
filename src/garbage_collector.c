/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:34:00 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 17:53:27 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_garbage(t_garbage *garbage, int argc, char **argv)
{
	(void) argc;
	(void) argv;
	garbage->split_pipe = NULL;
	garbage->split_lst = NULL;
	garbage->maillons = NULL;
	garbage->pipes = NULL;
	garbage->line = NULL;
	garbage->new_env = NULL;
}
