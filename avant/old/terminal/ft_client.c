/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:29:50 by zhamdouc          #+#    #+#             */
/*   Updated: 2022/12/21 18:10:05 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned int bits = 0;

void    ft_end(int signum)
{
	if (signum == SIGUSR1)
		ft_printf("%d bits successfully sent !\n ", bits);
}

void    ft_send_bit(int pid, char octet)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (octet & 128)
		{
			if (kill(pid, SIGUSR1) == -1)
				error(2);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				error(2);
		}
		octet = octet << 1;
		usleep(400);
		i++;
	}
}

void    error(int i)
{
	if (i == 1)
	{
		ft_printf("Usage: ./client [PID] [MESSAGE]");
		exit(EXIT_FAILURE);
	}
	if (i == 2)
	{
		ft_printf("Error: kill() failed");
		exit(EXIT_FAILURE);
	}
	if (i == 3)
	{
		ft_printf("Error: sigaction() failed");
		exit(EXIT_FAILURE);
	}
	if (i == 4)
	{
		ft_printf("Error: malloc() failed");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{
	int i;
	int pid;
	struct sigaction act;

	i = 0;
	if (argc != 3)
		error(1);
	act.sa_handler = ft_end;
	pid = atoi(argv[1]);
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		error(3);
	while (argv[2][i])
	{
		ft_send_bit(pid, argv[2][i]);
		i++;
		bits = bits + 8;
	}
	ft_send_bit(pid, '\0');
	return (0);
 }