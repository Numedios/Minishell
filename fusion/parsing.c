/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:39:06 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/01/04 17:40:26 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parenthesis_close_2(char *str);
int parenthesis_close_1 (char *str);
//test : fkfs;sf      '''ho"''''l"a'''    'ho"''l"a'
int check_2(char *line)
{
	int i;
	int j;

	i = 0;
	while (line && line[i])
	{
		while ((line[i] == '"' && line[i + 1] != '"') || (line[i] == '\'' && line[i + 1] != '\''))//ne fonctionne pas quand je met line[i + 1] doit etre different de '\0', pour ce test '''ho"''''l"a'''
		{
			if(line[i] == '"' && line[i + 1] != '"')
			{
				i++;
				if (!line[i])
					return (0);
				while (line[i] != '"')
					i++;
			}
			if((line[i] == '\'' && line[i + 1] != '\''))
			{
				i++;
				if (!line[i])
					return (0);
				while (line[i] != '\'')
					i++;
			}
			i++;
		}
		if((line[i] == '"' && line[i + 1] == '"') || (line[i] == '\'' && line[i + 1] == '\''))
		{
			j = i;
			while (line && line[j])
			{
				line[j] = line[j + 2];
				line [j + 1] = line [j + 3]; 
				j++;
			}
			i = 0;
		}
		else
			i++;
	}
}

int check_1(char *line)
{
	int i;
	int j;

	i = 0;
	while (line && line[i])
	{
		while ((line[i] == '"' && line[i + 1] != '"') || (line[i] == '\'' && line[i + 1] != '\''))
		{
			if(line[i] == '"' && line[i + 1] != '"')
			{
				i++;
				if (!line[i])
					return (0);
				while (line[i] != '"')
					i++;
			}
			if((line[i] == '\'' && line[i + 1] != '\''))
			{
				i++;
				if (!line[i])
					return (0);
				while (line[i] != '\'')
					i++;
			}
			i++;
		}
		if(line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (1);
		}
		if(line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (1);
		}
		if(line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '|')
		{
			printf("bash: syntax error near unexpected token `|'\n");
			return (1);
		}
		if(line[i] == '|' && line[i + 1] == ' ' && line[i + 2] == '|')
		{
			printf("bash: syntax error near unexpected token `|'\n");
			return (1);
		}
		if(line[i] == '&' && line[i + 1] == '&' && line[i + 2] == '&')
		{
			printf("bash: syntax error near unexpected token `&&'\n");
			return (1);
		}
		if(line[i] == ';' && line[i + 1] == ';')
		{
			printf("bash: syntax error near unexpected token `;;'\n");
			return (1);
		}
		while (line[i] == '"' && line[i + 1] == '"' && line[i+ 2]== '"')
			i++;
		while (line[i] == '\'' && line[i + 1] == '\'' && line[i+ 2]== '\'')
			i++;
		i++;
	}
	return(0);
}

int parse (char *line)
{
	if (quote_close(line) == 0)
	{
		printf("quote not close\n");
		return (1);
	}
	if (parenthesis_close_2(line) == 1 || parenthesis_close_1(line) == 1)
		return (1);
	if (line[0] == ';')
	{
		printf("bash: syntax error near unexpected token `;'\n");
		return (1);
	}
	if (check_1(line) == 1)
        return (1);
	check_2(line);
    if (ft_strlen(line) == 1)
    {
        if (line[0] == '>' || line[0] == '<')
        {
            printf("bash: syntax error near unexpected token `newline'\n");
            return (1);
        }
        return (0);
    }
    if (str_cmp(line,"<<") == 1 || str_cmp(line,">>") == 1)
    {
        printf("bash: syntax error near unexpected token `newline'\n");
        return (1);
    }
    return (0);
}

int ft_strlen_const(const char *str)
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

int quote_close_2(char *str)
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

int parenthesis_close_1 (char *str)
{
	int i;
	int count_1;
	
	i = 0;
	count_1 = 0;

	while (str && str[i])
	{
		if (str[i] == '(')
			count_1++;
		i++;
	}
	i = 0;
	while (str && str[i])
	{
		if (str[i] == ')')
			count_1--;
		i++;
	}
	if (count_1 < 0)
	{
		printf("bash: syntax error near unexpected token `)'\n");
		return (1);
	}
	return (0);
}

int parenthesis_close_2 (char *str)
{
	char    c;
	int i;
	int count;

	i = 0;
	count = 0;
	if (!str)
			return (0);
	while(str && str[i])
	{
		while (str[i] == '(')
		{
			i++;
			count++;
		}
		if (count > 0)
		{
			while(str[i] == ')' || str[i] == ' ')
			{
				if (str[i] == ')')
					count--;
				i++;
			}
			if (count <= 0)
			{
				printf("bash: syntax error near unexpected token `)'\n");
				return (1);
			}
			return(0);
		}
		i++;
	}
	return (0);
}