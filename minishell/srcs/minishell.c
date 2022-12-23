/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakariyahamdouchi <zakariyahamdouchi@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:18:12 by zakariyaham       #+#    #+#             */
/*   Updated: 2022/12/23 16:51:41 by zakariyaham      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void prompt(char **env)
{

}

int main(int argc, char **argv, char **env)
{
	while (1)
	{
		//affichage du prompt a chaque fois
		prompt(env);
	}
}
