/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:11:43 by sbelabba          #+#    #+#             */
/*   Updated: 2022/12/02 15:15:40 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_data(t_data *stock)
{
	if (stock->cmd)
		free_tab_tab(stock->cmd);
	if (stock->path)
		free_tab(stock->path);
}

/* return tout ce qui trouve apres PATH= dans l'env 
si il trouve pas return NULL
  */

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strcmp(envp[i], "PATH="))
			break ;
		i++;
	}
	if (envp[i])
		return (&*envp[i] + 5);
	return (NULL);
}

/*  recupere tout les arg et les mes dans  un char** 
    exemple "ls -a" "pwd" "cat -e" 
	return [[["ls"], ["-a"]],[["pwd"]], [["cat"],["-e"]]
*/

char	***recup_arg(char **argv)
{
	char	***res;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen_tab(argv);
	res = malloc(sizeof(char **) * len + 1);
	while (i < len - 1)
	{
		res[i] = split_pipex(argv[i], ' ');
		if (!res[i])
		{
			free_tab_tab(res);
			return (NULL);
		}
		i++;
	}
	res[i] = 0;
	return (res);
}

/* retun 0 si contien un /
 return 1 sinon*/

int	check_is_path(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

int	only_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
