/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakariyahamdouchi <zakariyahamdouchi@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:18:12 by zakariyaham       #+#    #+#             */
/*   Updated: 2022/12/23 18:52:38 by zakariyaham      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sig(int sig)
{
	if (sig == SIGINT)//ctrl+c
	{
		printf("\n\nMinishell >");
	}
	if (sig == SIGQUIT)//ctrl+\
		return ;
	if (sig == SIGTSTP)//ctrl+z
		exit(0);
}

//ctrl-D correspond a NULL, donc si l'utilisateur appuie sur ctrl-D sans rien ecrire readline sera egale a NULL
//ctrl+d correspond a EOF
/*
char *command = readline();  // utiliser readline pour lire une ligne de commande
if (command == NULL)  // si l'utilisateur appuie sur ctrl-D
{
    printf("\n");
    exit(0);
}
*/

int main(int argc, char **argv, char **env)
{
	struct sigaction sa;

	sa.sa_handler = handle_sig;
	sigemptyset(&sa.sa_mask);// utiliser sigaddset(&sa.sa_mask, SIGTSTP); si on souhaite bloque un signal en particulier
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction failed");
		return (1);
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction failed");
		return (1);
	}
	if (sigaction(SIGTSTP, &sa, NULL) == -1)
	{
		perror("sigaction failed");
		return (1);
	}
	while (1)
	{
		pause();
	}
	return (0);
}
