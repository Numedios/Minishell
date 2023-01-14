#include "minishell.h"
/*
char	*ft_strjoin(char *line, char *buf)
{
	char	*res;
	int		i;
	int		j;	

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buf) + 1));
	if (!res)
		return (NULL);
	while (line && line[i])
	{
		res[i] = line[i];
		i++;
	}
	while (buf[j])
		res[i++] = buf[j++];
	res[i] = '\0';
	free(line);
	return (res);
}*/

int	*create_heredoc(char *str)
{
	int	*pipe_fd;

    pipe_fd = malloc(sizeof(int) * 2);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
	return (pipe_fd);
}

int heredoc(char *stop)
{
    int		*pipe_fd;
	char	*str;
	char	*comp;

	pipe_fd = create_heredoc(stop);
	comp = ft_strjoin(stop, "\n");
    str = NULL;
	while (1)
	{
		write(1, "here_doc> ", 10);
		str = get_next_line(1);
		if (ft_strcmp(comp, str))
		{
			free(str);
			break ;
		}
		else
		{
			write(pipe_fd[1], str, ft_strlen(str));
			free(str);
		}
	}
    close(pipe_fd[1]);
	free(comp);
    return (pipe_fd[0]);
}