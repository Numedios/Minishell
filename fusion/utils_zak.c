/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_zak.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:27:55 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/01/04 17:38:10 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//verifier que le 
#include "minishell.h"

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



void handle_sig(int sig)
{
	if (sig == SIGINT)//ctrl+c
	{
		printf("\nMinishell >");
	}
	if (sig == SIGTSTP)//ctrl+z
	{
		exit(0);
	}
}

void setup_signal_handlers(void)
{
  // Définissez handle_sig() comme le gestionnaire de signal pour SIGINT.
  if (signal(SIGINT, handle_sig) == SIG_ERR)
  {
    perror("signal failed");
    exit (1);
  }

  // Définissez SIG_IGN comme le gestionnaire de signal pour SIGQUIT.
  if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
  {
    perror("signal failed");
    exit (1);
  }

  // Définissez handle_sig() comme le gestionnaire de signal pour SIGTSTP.
  if (signal(SIGTSTP, handle_sig) == SIG_ERR)
  {
    perror("signal failed");
    exit (1);
  }
}

