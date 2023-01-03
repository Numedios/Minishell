/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:19:48 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/01/03 17:18:32 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int     do_cd(char *path);
int     do_echo (char *string, int i);
void	do_env(char **env);
int     do_exit(int statut);
int     do_pwd(void);
void	do_unset(char *tab, char **env_copy);
char **do_export(char *tab, char **env_copy);
char	*ft_strdup_const(const char *s);
int ft_strlen(char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
