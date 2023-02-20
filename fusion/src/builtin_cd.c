/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:35:56 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/19 16:55:32 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* erreur rajouter free garbage sur le return 
*
*/

static void	update_pwd(char **new_env, char *pwd)
{
	char	dir[4096];

	if (getcwd(dir, sizeof(dir)) != NULL)
	{
		pwd = ft_strjoin("PWD=", dir);
		if (!pwd)
			return ;
		new_env = do_export(pwd, new_env, 0, 0);
		free(pwd);
	}
}

/*
* erreur rajouter ligne 51 free garbage sur le return 
* erreur ligne 59 //error _cd
*/

int	do_cd_change_directory(char *path, char **oldpwd)
{
	if (chdir(path) == -1)
	{
		s_fd("bash: cd: ", 2);
		s_fd(path, 2);
		s_fd(" No such file or directory\n", 2);
		free (*oldpwd);
		return (1);
	}
	return (0);
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
			return (1);
	}
	if (do_cd_change_directory(path, &oldpwd) == 1)
		return (1);
	if (path[0] == '.' && path[1] == '\0')
		return (free(oldpwd), 0);
	if (oldpwd)
	{
		if (check_if_tab_exist(oldpwd, new_env) != 1)
			new_env = do_export(oldpwd, new_env, 0, 0);
		free(oldpwd);
	}
	update_pwd(new_env, pwd);
	return (0);
}
