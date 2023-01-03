/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:34:25 by zhamdouc          #+#    #+#             */
/*   Updated: 2022/12/21 20:45:26 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "ft_printf/libftprintf.h"

/* info */
typedef struct s_struct
{
	char		*tab;
	char		lettre;
	pid_t		pid_c;
}		t_struct;

// typedef struct s_struct
// {
// 	char		octet;
// 	char		*message;
// 	pid_t		client_pid;
// }		t_struct;

void	error(int i);
char	*ft_addchar(char *s1, char s2);
void	ft_handler(int signum, siginfo_t *c_pid, void *tmp);

#endif