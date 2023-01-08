/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:39:06 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/01/08 17:42:46 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parenthesis_close_2(char *str);
int parenthesis_close_1 (char *str);
//test : fkfs;sf      '''ho"''''l"a'''    'ho"''l"a'
//si rien apres pipe = probleme 
// pour chaque if du parsinf check meme en skipant tout les espace qui separes les char 
//comment gerer les "()"
// remplacer prinf par ft_putstr_fd pour ecrire sur la sortie d'erreur
//pour $HOLA il fonctionne tout seul ou avec "$HOLA", on ne peut pas declarer une variable globale en commencant par un chiffre ou $, pas de caractere speciale, mais on peut mettre un chiffre dedans

int after_pipe(char *line)
{
	int i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '|')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '\0')
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}


int check_parenthesis(char *line)//(")"0 ;;; (")" 0) -> est ce qu'il traiter les "()" comment les guillemets
{
	int i;
	int	count_1;
	int	count_2;

	i = 0;
	count_1 = 0;
	count_2 = 0;
	while (line && line[i])
	{
		i = skip_quote(line, i);
		if (i == -1)
			return (0);
		if (line[i] == '(')
			count_1++;
		if (line[i] == ')')
			count_2++;
		if (count_2 > count_1)
			return (1);
		i++;
	}
	if (count_1 != count_2)
		return (1);
	return (0);
}


int del_quote(char *line)
{
	int i;
	int j;

	i = 0;
	while (line && line[i])
	{
		i = skip_quote(line, i);
		if (i == -1)
			return (0);
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

int	check_error_2_space(char *line, char c, char c_bis, int i)
{
	if (line[i] == c)
	{
		i++;
		while (line[i] == ' ')
			i++;
		if (line[i] == c_bis)
			return (2);
		else 
			return (0);
	}
	return (0);
}

int	check_error_space(char *line, char c, int i)
{
	if (line[i] == c)
	{
		i++;
		while(line[i] == ' ')
			i++;
		if (line[i] == c)
			return (2);
		else 
			return (0);
	}
	return (0);
}

int check_1(char *line)
{
	int i;
	int j;

	i = 0;
	while (line && line[i])
	{
		i = skip_quote(line, i);
		if (i == -1)
			return (0);
		if(check_error_2_space(line, '(', ')', i) == 2)
		{
			printf("bash: syntax error near unexpected token `)'\n");
			return (1);
		}
		if(check_error_2_space(line, '<', '>', i) == 2)
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (1);
		}
		if(check_error_2_space(line, '>', '<', i) == 2)
		{
			printf("bash: syntax error near unexpected token `<'\n");
			return (1);
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
		if(line[i] == '<' && line[i + 1] == ' ' && line[i + 2] == '>')
		{
			printf("bash: syntax error near unexpected token `>'\n");
			return (1);
		}
		if(line[i] == '<' && line[i + 1] == '>' && line[i + 2] == '>')
		{
			printf("bash: syntax error near unexpected token `>'\n");
			return (1);
		}
		if(line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '|')
		{
			printf("bash: syntax error near unexpected token `|'\n");
			return (1);
		}
		if(check_error_space(line, '|', i) == 2)//while space
		{
			printf("bash: syntax error near unexpected token `|'\n");
			return (1);
		}
		// if(line[i] == '|' && line[i + 1] == ' ' && line[i + 2] == '|')//while space
		// {
		// 	printf("bash: syntax error near unexpected token `|'\n");
		// 	return (1);
		// }
		if(line[i] == '&')
		{
			printf("bash: syntax error near unexpected token `&'\n");
			return (1);
		}
		if(line[i] == '\\')
		{
			printf("bash: syntax error near unexpected token `\'\n");
			return (1);
		}
		if(line[i] == ';')
		{
			printf("bash: syntax error near unexpected token `;'\n");
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

/*
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
		if(line[i] == '<' && line[i + 1] == '>')
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (1);
		}
		if(line[i] == '>' && line[i + 1] == '<')
		{
			printf("bash: syntax error near unexpected token `<'\n");
			return (1);
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
		if(line[i] == '<' && line[i + 1] == ' ' && line[i + 2] == '>')
		{
			printf("bash: syntax error near unexpected token `>'\n");
			return (1);
		}
		if(line[i] == '<' && line[i + 1] == '>' && line[i + 2] == '>')
		{
			printf("bash: syntax error near unexpected token `>'\n");
			return (1);
		}
		if(line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '|')
		{
			printf("bash: syntax error near unexpected token `|'\n");
			return (1);
		}
		if(line[i] == '|' && line[i + 1] == ' ' && line[i + 2] == '|')//while space
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
*/

int parse (char *line)
{
	if (quote_close(line) == 0)
	{
		printf("quote not close\n");
		return (1);
	}
	if (check_parenthesis(line) == 1)
	{
		printf("parenthesis not close\n");
		return (1);
	}
	if (after_pipe(line) ==1)
		return (1);
	if (line[0] == ';')
	{
		printf("bash: syntax error near unexpected token `;'\n");
		return (1);
	}
	if (check_1(line) == 1)
        return (1);
	del_quote(line);
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
/*
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
*/