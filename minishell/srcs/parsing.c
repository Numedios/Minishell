/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:39:06 by zhamdouc          #+#    #+#             */
/*   Updated: 2022/12/30 14:56:31 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int ft_strlen(char *str);
int str_cmp(char *s1, char *s2);


int parse (char *line)
{
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

// int main(int argc, char **argv)
// {
//     parse(argv[1]);
// }