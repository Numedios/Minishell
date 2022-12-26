/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:18:12 by zakariyaham       #+#    #+#             */
/*   Updated: 2022/12/26 19:34:26 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

int ft_strlen(char *str);
int str_cmp(char *s1, char *s2);
int parse (char *line);
int quote_close(char *str);
//ajouter la pre_check des quote ferme ou ouverte 
void handle_sig(int sig)
{
	if (sig == SIGINT)//ctrl+c
	{
		printf("\nMinishell >");
	}
	if (sig == SIGQUIT)
	{
		return ;
	}
	if (sig == SIGTSTP)//ctrl+z
	{
		exit(0);
	}
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

int main(void)
{
	struct sigaction sa;
	char *command;  // utiliser readline pour lire une ligne de commande

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
		command = readline("Minishell >");  // utiliser readline pour lire une ligne de commande
		if (command == NULL)  // si l'utilisateur appuie sur ctrl-D
		{
    		printf("\n");
    		exit(0);
		}
		if (command != NULL)  // si l'utilisateur appuie sur ctrl-D
		{
			parse(command);  // utiliser readline pour lire une ligne de commande
			command = NULL;
		}
	}
	return (0);
}

int check_1(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if(line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (0);
		}
		if(line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (0);
		}
		if(line[i] == '|' && line[i + 1] == '|')
		{
			printf("bash: syntax error near unexpected token `||'\n");
			return (0);
		}
		if(line[i] == '&' && line[i + 1] == '&')
		{
			printf("bash: syntax error near unexpected token `&&'\n");
			return (0);
		}
		if(line[i] == ';' && line[i + 1] == ';')
		{
			printf("bash: syntax error near unexpected token `;;'\n");
			return (0);
		}
		if(line[i] == '"' && line[i + 1] == '"')
		{
			line[i] = ' ';
			line[i + 1] = ' ';
			i++;
		}
		i++;
	}
}

int parse (char *line)
{
	if (quote_close(line) == 0)
	{
		printf("quote not close\n");
		return (0);
	}
	if (line[0] == ';')
	{
		printf("bash: syntax error near unexpected token `;'\n");
		return (0);
	}
	check_1(line);
    if (ft_strlen(line) == 1)
    {
        if (line[0] == '>' || line[0] == '<')
        {
            printf("bash: syntax error near unexpected token `newline'\n");
            return (0);
        }
        return (0);
    }
    if (str_cmp(line,"<<") == 1 || str_cmp(line,">>") == 1)
    {
        printf("bash: syntax error near unexpected token `newline'\n");
        return (0);
    }
	printf("%s\n", line);
    return (0);
}


int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int str_cmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    if (s1[i] != s2[i])
        return (0);
    return (1);
}

int quote_close(char *str)
{
        char    c;
		int i;

		i = 0;
        if (!str)
                return (0);
        while(str && str[i])
		{
				if (str[i] == '\'' || str[i] == '\"')
				{
						c = str[i];
						i++;
						while (str[i] && str[i] != c)
								i++;
						if (str[i] != c)
								return (0);
				}
				i++;
		}
        return (1);
}
