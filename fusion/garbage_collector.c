/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:34:00 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/13 11:34:29 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_garbage(t_garbage *garbage)
{
	garbage->split_pipe = NULL;
	garbage->split_lst = NULL;
	garbage->maillons = NULL;
	garbage->pipes = NULL;
}
