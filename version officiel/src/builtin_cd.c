/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:35:56 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/22 18:25:05 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* erreur rajouter free garbage sur le return 
*
*/

extern int	g_exit_code[2];

static void	update_pwd(char ***new_env, char *pwd, t_garbage *g)
{
	char	dir[4096];

	if (getcwd(dir, sizeof(dir)) != NULL)
	{
		pwd = ft_strjoin("PWD=", dir);
		if (!pwd)
		{
			free_garbage_env_exit(g, 1);
			return ;
		}
		(*new_env) = do_export(pwd, (*new_env), 0, g);
		free(pwd);
		pwd = NULL;
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
		g_exit_code[0] = 1;
		free (*oldpwd);
		oldpwd = NULL;
		return (1);
	}
	return (0);
}

int	do_cd(char ***new_env, char *path, t_garbage *g)
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
			return (free_garbage_env_exit(g, 1), 1);
	}
	if (do_cd_change_directory(path, &oldpwd) == 1)
		return (1);
	if (path[0] == '.' && path[1] == '\0')
		return (free(oldpwd), 0);
	if (oldpwd)
	{
		if (check_if_tab_exist(oldpwd, (*new_env)) != 1)
			(*new_env) = do_export(oldpwd, (*new_env), 0, g);
		free(oldpwd);
	}
	update_pwd(new_env, pwd, g);
	return (0);
}
