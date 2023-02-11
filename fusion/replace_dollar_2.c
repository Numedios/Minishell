/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakariyahamdouchi <zakariyahamdouchi@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:10:42 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/01/22 20:25:50 by zakariyaham      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//gerer $?
// retirer les autres

char	*delete_dollar(char *line)
{
	int		i;
	int		j;
	char	*new_line;
	//char	*final_line; pour eventuellement faire un str_len de new line a la fin et copy seulement la partie qui nous interessse dans new_line car on a trop malloc

	i = 0;
	j = 0;
	while (line && line[i] != '\0')
	{
		if (line[i] != '$')
			i++;
		else
		{
			j = 1;
			break ; 
		}
	}
	i = 0;
	if (j == 0)
		return (line);
	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
	//il faut garder le dollar seulement quand on est dans un simple quote qui est en dehors d'une double quote
	while (line && line[i])
	{
		while (line && line[i] != '\0' && line [i] == '"')//faire possiblement attention au cas il la quote n'est pas ferme 
		{
			new_line[j] = line[i];
			j++;
			i++;
			while(line && line[i] != '\0' && line[i] != '"')
			{
				if (line[i] == '$')
				{
					while (line && line[i] != '\0' && line[i] != ' ' && line[i] != '"' && line[i] != '\'')// et des autres espaces
						i++;
				}
				else
				{
					new_line[j] = line[i];
					j++;
					i++;
				}
			}
			new_line[j] = line[i];
			j++;
			i++;
		}
		while (line && line[i] != '\0' && line [i] == '\'')
		{
			new_line[j] = line[i];
			j++;
			i++;
			while (line && line[i] != '\0' && line[i] != '\'')
			{
				new_line[j] = line[i];
				j++;
				i++;
			}
			new_line[j] = line[i];
			j++;
			i++;
		}
		while (line && line[i] != '\0' && line[i] != '\'' && line [i] != '"')
		{
			if (line[i] == '$')
			{
				while (line && line[i] != '\0' && line[i] != ' ' && line[i] != '"' && line[i] != '\'')// et des autres espaces
					i++;
			}
			new_line[j] = line[i];
			i++; 
			j++;
		}
		// if (line && line[i] != '\0')
		// {
		// 	i++;
		// 	j++;
		// }
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
}
