/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_zak.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zheylkoss <zheylkoss@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:27:55 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/01/09 15:19:15 by zheylkoss        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//verifier que le 
#include "minishell.h"

int print_tab(char **tab)
{
	int i;

	i = 0;
	while (tab && tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
}


int	skip_quote (char *line, int i)//existe deja dans un autre fichier, a ajouter dans le .h et le retirer d'ici
{
	while ((line[i] == '"' && line[i + 1] != '"') || (line[i] == '\'' && line[i + 1] != '\''))//ne fonctionne pas quand je met line[i + 1] doit etre different de '\0', pour ce test '''ho"''''l"a'''
	{
		if(line[i] == '"' && line[i + 1] != '"')
		{
			i++;
			if (!line[i])
				return (-1);
			while (line[i] != '"')
				i++;
		}
		if((line[i] == '\'' && line[i + 1] != '\''))
		{
			i++;
			if (!line[i])
				return (-1);
			while (line[i] != '\'')
				i++;
		}
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		s1_len;
	int		s2_len;
	int		i;

	s1_len = ft_strlen ((char *)s1);
	s2_len = ft_strlen ((char *)s2);
	s = malloc ((s1_len + s2_len + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	i = 0;
	s1_len = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[s1_len])
	{
		s[i] = s2[s1_len];
		i++;
		s1_len++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_strdup_const(const char *s)
{
	char	*s_copy;
	size_t	s_len;

	s_len = 0;
	if (s == NULL)
		return (NULL);
	s_len = ft_strlen_const(s);
	s_copy = malloc((s_len + 1) * sizeof(char));
	if (s_copy == NULL)
		return (NULL);
	s_len = 0;
	while (s[s_len])
	{
		s_copy[s_len] = s[s_len];
		s_len++;
	}
	s_copy[s_len] = '\0';
	return (s_copy);
}
