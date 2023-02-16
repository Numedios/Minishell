/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:10 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/13 12:50:44 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//gerer des long long, is au dessu affihcer une erreur specifique
//si deux argument afficher une erreur specifique
//pas de char
//utiliser une variable globale pour les codes erreurs
long long	ft_atoll_capped(const char *nptr, int *flag, int j, int nb)
{
	long long	print;

	if (nptr == NULL)
		return (0);
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			j = -j;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		print = LLONG_MAX;
		if (j > 0 && (LLONG_MAX - *nptr + '0') / 10 < nb)
			return (++*flag, 0);
		print = ((LLONG_MAX + *nptr - '0') / 10);
		if (j < 0 && (LLONG_MAX + *nptr - '0') / 10 > -nb)
			return (++*flag, 0);
		nb = nb * 10 + *nptr - '0';
		nptr++;
	}
	return (nb * j);
}

int	do_exit(char *statut, t_garbage *garbage)
{
	long long	exit_code;
	int			flag;

	exit_code = 2;
	flag = 0;
	while (statut && statut[flag])//erreur il y a une lettree
	{
		while (statut[flag] == 32 || (statut[flag] >= 9 && statut[flag] <= 13))
			flag++;
		if (statut[flag] == '-' || statut[flag] == '+')
			flag++;
		if (statut[flag] >= '0' && statut[flag] <= '9')
			flag++;
		else
		{
			free_garbage_and_env(garbage);
			exit(2);
		}
	}
	flag = 0;
	exit_code = ft_atoll_capped(statut, &flag, 1, 0);
	if (flag == 0)
	{
		free_garbage_and_env(garbage);
		exit(exit_code);
	}
	else
	{
		free_garbage_and_env(garbage);
		exit(2);
	}
}

//attention au here_doc, surtout quand on fait CTRL+C dans le premier ca doit tout ferme
//peut etre devoir gerer le CTRL+\ pour le here_doc pour faire coredump, pour ca dir que si le pid est > a 0 alors rien faire dans lautre cas core dump
/*
zhamdouc@e2r12p22:~/Minishell/fusion$ ///
bash: ///: Is a directory
zhamdouc@e2r12p22:~/Minishell/fusion$ .
bash: .: filename argument required
.: usage: . filename [arguments]
*/
/*
exemple du here_doc:
zhamdouc@e2r12p22:~/Minishell/fusion$ cat >> eof | wc >> eof
sadasd
eof
sada
eof

cat
wc

zhamdouc@e2r12p22:~/Minishell/fusion$ cat << eof | wc << eof
> sadlakjd
> eof
> adasl
> eof
	  1       1       6
zhamdouc@e2r12p22:~/Minishell/fusion$ cat << eof | wc << eof
>
bash: warning: here-document at line 10 delimited by end-of-file (wanted `eof')
>
bash: warning: here-document at line 10 delimited by end-of-file (wanted `eof')
	  0       0       0
zhamdouc@e2r12p22:~/Minishell/fusion$ cat << eof | wc << eof
> ^C
zhamdouc@e2r12p22:~/Minishell/fusion$ cat << eof | wc << eof | ls
> ^C
zhamdouc@e2r12p22:~/Minishell/fusion$ echo $>
bash: syntax error near unexpected token `newline'
zhamdouc@e2r12p22:~/Minishell/fusion$ cat << eof | wc << eof | ls
> ^C


*/

/*
tout traiter en un bloc car on ne saura pas quoi envoyer en infile du prochain pipe
exemple :
zhamdouc@e2r12p22:~/Minishell/fusion$ cat Makefile | grep l | grep m > out | grep 2 | wc
	  0       0       0
zhamdouc@e2r12p22:~/Minishell/fusion$ cat Makefile | grep l | grep m > out | wc
	  0       0       0
dans notre solution comment traiter wc
*/
