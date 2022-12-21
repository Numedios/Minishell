/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_serveur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:26:33 by zhamdouc          #+#    #+#             */
/*   Updated: 2022/12/21 20:32:30 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_struct	com;
    
char   *ft_addchar(char *tab, char lettre)
{
    int len;
    int i;
    char *tmp;

    i = 0;
    len = 0;
    while(tab && tab[len])
        len++;
    tmp = malloc(sizeof(char) * (len + 2));
    if (tmp == NULL)
        error(4);
    while (tab && tab[i])
    {
        tmp[i] = tab[i];
        i++;
    }  
    tmp[i] = lettre;
    tmp[i + 1] = '\0';
    free(tab);
    return (tmp);
}

void    ft_handler(int signum, siginfo_t *signal, void *tmp)
{
    static int i = 0;

    (void)tmp;
    com.pid_c = signal->si_pid;
    if (signum == SIGUSR1)
    {
        com.lettre <<= 1;
        com.lettre |= 1;
    }
    if(signum == SIGUSR2)
        com.lettre <<= 1;
    i++;
    if (i == 8)
    {
        if (!com.lettre)
        {
            ft_printf("%s\n", com.tab);
            free(com.tab);
            com.tab = NULL;
            if (kill(com.pid_c, SIGUSR1) == -1)
                error(2);
            usleep(100);
        }
        com.tab = ft_addchar(com.tab, com.lettre);
        i = 0;
    }

}

int main(void)
{
    struct sigaction    act;
    pid_t        pid;
    
    pid = getpid();
    ft_printf("Server PID: %d \n\n", pid);
    act.sa_sigaction = ft_handler;
    act.sa_flags = SA_SIGINFO;
    com.tab = NULL;
    if (sigaction(SIGUSR1, &act, NULL) == -1 || sigaction(SIGUSR2, &act, NULL) == -1)
     {
        error(2);
    }   
    while (42)//est que j'ai vraiment besoin de faire une boucle infinie
        pause();//utiliser sigwait a la plac
    return (0);
}

