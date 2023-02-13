/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:35:56 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/13 12:46:29 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(char **new_env, char *pwd)
{
	char	dir[4096];

	if (getcwd(dir, sizeof(dir)) != NULL)
	{
		pwd = ft_strjoin("PWD=", dir);
		if (!pwd)
			return;//appeller la fonction error_malloc
		new_env = do_export(pwd, new_env);
		free(pwd);
	}
}

int	do_cd(char **new_env, char *path)
{
	char	dir[4096];
	char	*oldpwd;
	char	*pwd;

	oldpwd = NULL;
	pwd = NULL;
	if (getcwd(dir, sizeof(dir)) != NULL)
	{
		oldpwd = ft_strjoin("OLDPWD=", dir);
		if (!oldpwd)
			return (1);//appeler la fonction error_malloc
	}
	if (chdir(path) == -1)
		return (1);//error _cd
	if (oldpwd)
	{
		new_env = do_export(oldpwd, new_env);
		//free(oldpwd);
	}
	update_pwd(new_env, pwd);
	return (0);
}
