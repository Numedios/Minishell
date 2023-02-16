/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakariyahamdouchi <zakariyahamdouchi@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:36:12 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/16 18:35:35 by zakariyaham      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//new_env = do_export("FOO=bar", new_env);
//gerer le cas "+="
//que faire si on utilise export sans rien derriere (imprimer env)

int	parse_value(char *tab, int i, int a)
{
	if (tab[i] == '+')
	{
		a = 3;
		i = i + 2;
	}
	else
		i++;
	if (tab && (tab[i] == '\0' || tab[i] == ' ' || (tab[i] < 14 && tab[i] > 7)))
	{
		if (a == 3)
			return (5);
		else
			return (4);
	}
	while (tab && tab[i])
	{
		i = skip_quote(tab, i);
		if (i == -1)
			return (1);
		i++;
	}
	return (a);
}

//return 2 si il y a rien et donc imprimer env,  1 pour erreur, 0 pour remplacer
//et 3 pour ajouter a c qu'il existe deja, return (4) si apres '=' il a un espace,
//5 si il ya '+=' et apres un ' '

int	parse_export(char *tab, int i, int a)
{
	while (tab && tab[i] == ' ')
		i++;
	if (!tab)
		return (2);
	if (ft_isdigit(tab[i]) == 2)
		return (1);
	while (tab && tab[i])
	{
		if ((tab[i] == '+' && tab[i + 1] != '=') || tab[0] == '=')
			return (1);
		if (tab[i] == '+' && tab[i + 1] == '=' && i == 0)
			return (1);
		if ((tab[i] == '+' && tab[i + 1] == '=') || tab[i] == '=')
		{
			a = parse_value(tab, i, 0);
			break ;
		}
		//TESTER LES 2 IF
		if (tab[i] == ' ' || (tab[i] < 14 && tab[i] > 7))
			return (1);
		if ((tab[i] > 32 && tab[i] < 48) || (tab[i] > 57 && tab[i] < 65)
			|| (tab[i] > 90 && tab[i] < 97) || (tab[i] > 122 && tab[i] < 127))
			return (1);
		i++;
	}
	return (a);
}

char	**replace_value(int j, int a, char *tab, char **env)
{
	int	i;

	i = 0;
	if (a == 0)
	{
		free(env[j]);
		env[j] = ft_strdup(tab);
		return (env);
	}
	if (a == 3)
	{
		while (tab && tab[i] != '=')
			i++;
		i++;
		env[j] = ft_strjoin(env[j], &tab[i]);
		return (env);
	}
	if (a == 4) //a verifier, correspond a un espace apres un '='
	{
		free(env[j]);
		env[j] = ft_strdup(tab);//ca depend comment je recois tab
		return (env);
	}
	else
		return (env);
}

char	**new_value(int i, int a, char *tab, char **env)
{
	int	j;

	j = 0;
	if (a == 0)
	{
		env[i] = ft_strdup(tab);
		return (env);
	}
	if (a == 3)
	{
		while (tab && tab[j] != '=')
			j++;
		j++;
		env[i] = ft_strjoin(env[i], &tab[j]);
		return (env);
	}
	if (a == 4) //a verifier
	{
		env[i] = ft_strdup(tab);//ca depend comment je recois tab
		return (env);
	}
	else
		return (env);
}

char	**do_export(char *tab, char **env_copy, int i, int a)
{
	int		j;
	char	**new_env;

	if (parsing_of_export(tab, env_copy, &a, &j) == 1)
		return (env_copy);
	if (j != -1)
	{
		env_copy = replace_value(j, a, tab, env_copy);
		return (env_copy);
	}
	else
	{
		while (env_copy && env_copy[i])
			i++;
		new_env = malloc ((i + 2) * sizeof(char *));
		i = 0;
		while (env_copy && env_copy[i])
		{
			new_env[i] = ft_strdup_const(env_copy[i]);
			i++;
		}
		new_env = new_value(i, a, tab, new_env);
		new_env[i + 1] = NULL;
		return (ft_free_tab(env_copy), new_env);
	}
}

	// if (ft_strchr(tab, '=') == NULL)//pas d'espace avant le "="
	// {
	// 	printf("export: `%s': not a valid identifier\n", tab);
	// 	return (env_copy);
	// }
	// a = parse_export(tab, 0, 1);
	// if (a == 1)
	// {
	// 	printf("export: `%s': not a valid identifier\n", tab);
	// 	return (env_copy);
	// }
	// if (a == 2)
	// {
	// 	do_env(env_copy);
	// 	return (env_copy);
	// }
	// if (check_if_tab_exist(tab, env_copy) == 1)
	// {
	// 	printf("export: '%s' : already defined\n", tab);
	// 	return (env_copy);
	// }
