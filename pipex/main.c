/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:25:34 by sbelabba          #+#    #+#             */
/*   Updated: 2022/12/06 15:51:01 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **env)
{
	t_data	stock;

	argc--;
	argv++;
	if (!parsing(argc, argv))
		return (0);
	else
	{
		if (!ft_strncmp("here_doc", argv[0]))
		{
			heredoc(argc, argv);
			argc--;
		}
		stock = create_path(argv, env);
		if (!stock.path || !stock.cmd)
			exit (1);
		pipex(argc, argv, env, &stock);
		free_tab(stock.path);
		free_tab_tab(stock.cmd);
		unlink("here_doc");
	}
	return (0);
}
