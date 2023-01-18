/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:10:42 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/01/18 17:00:07 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//gerer $?
// retirer les autres 

char *delete_dollar(char *line)
{
    int i;
    int j;
    char *new_line;
    //char    *final_line; pour eventuellement faire un str_len de new line a la fin et copy seulement la partie qui nous interessse dans new_line car on a trop malloc

    i = 0;
    j = 0;
    new_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
    while (line[i])
    {
        if (line[i] == '$')
        {
            while (line[i] != ' ' && line[i] != '\0' && line[i] != '"' && line[i] != '\'')// et des autres espaces
                i++;
        }
        new_line[j] = line[i];
        i++;
        j++;
    }
    new_line[j] = '\0';
    free(line);
    return (new_line);
}
