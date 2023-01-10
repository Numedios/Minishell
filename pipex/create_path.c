/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:33:20 by sbelabba          #+#    #+#             */
/*   Updated: 2022/12/02 15:03:29 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**check_acces_loop(char **cpy, char **res, char ***cmd, char **path)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		cpy = cpy_cmd_tab(path, cmd[i][0]);
		if (!cpy)
			return (NULL);
		while (cpy[j])
		{
			res[i] = NULL;
			if (access(cpy[j++], X_OK | F_OK) == 0 && check_is_path(cmd[i][0]))
			{
				res[i] = ft_strdup(cpy[--j]);
				break ;
			}
		}
		if (!res[i])
			res[i] = ft_strdup(cmd[i][0]);
		free_tab(cpy);
		i++;
	}
	return (res[i] = 0, res);
}

char	**check_acces(char **path, char ***cmd)
{
	char	**cpy;
	char	**res;

	res = malloc(sizeof(char *) * (ft_strlen_tab_tab(cmd) +1));
	cpy = NULL;
	if (!res)
		return (NULL);
	res = check_acces_loop(cpy, res, cmd, path);
	if (!res)
		return (NULL);
	return (res);
}

t_data	create_path(char **argv, char **envp)
{
	t_data	res;
	char	**pat;

	if (!ft_strncmp("here_doc", argv[0]))
		argv++;
	pat = split_pipex(get_path(envp), ':');
	res.cmd = recup_arg(++argv);
	if (!res.cmd)
	{
		free_tab(pat);
		exit (1);
	}
	res.path = check_acces(pat, res.cmd);
	if (pat)
		free_tab(pat);
	if (!res.path)
	{
		free_tab_tab(res.cmd);
		exit (1);
	}
	return (res);
}
