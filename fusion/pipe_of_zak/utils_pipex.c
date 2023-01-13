#include "../minishell.h"

int find_stdin_2(t_maillons *maillons, int * fd_in, two_pipe *two_pipe)
{
	dprintf(2, "res = %d\n", find_if_have_output(maillons -> output, '<'));
    if (find_if_have_output(maillons -> output, '<') == 1)
    {
		(*fd_in) = open(find_name_sep(maillons -> output, '<'),  O_RDWR, O_DSYNC, !O_DIRECTORY);
		return ((*fd_in));
	}
	else if (!(maillons-> prev))
	{
		return (0);
	}
	else if (find_if_have_output(maillons -> output -> prev, '>') || !(maillons->prev->command))
	{
		(*fd_in) = open("/dev/null",  O_RDWR, O_DSYNC, !O_DIRECTORY);
		return ((*fd_in));
	}
	else
	{
		dup2(two_pipe->pipe_fd[0], STDIN_FILENO);
		return (0);
		// return pipes[0] du maillons d'avant
	}
	return (-1);
}

int find_stdout_2(t_maillons *maillons, int *fd_out, two_pipe *two_pipe)
{
    if (find_if_have_output(maillons -> output, '>'))
    {
		(*fd_out) = open(find_name_sep(maillons -> output, '>'),  O_RDWR, O_DSYNC, !O_DIRECTORY);
		return ((*fd_out));
	}
	else if (!(maillons-> next))
	{
		return (0);
	}
	else
	{
		dup2(two_pipe->pipe_fd[1], STDOUT_FILENO);
		return (0);
		// return pipes[1] du maillons d'avant
	}
	return (-1);
}

int	check_access(char *command, two_pipe *two_pipe)
{
	int	j;

	j = 0;
	j = access(command, F_OK | X_OK);
	if (command[0] == '.' && command[1] == '/' && j != 0)
	{
		//write_error_2(argv[i], 3, two_pipe);
		return (2);
	}
	if (access(command, F_OK | X_OK) == 0)
	{
		two_pipe->the_path = ft_strdup(command);
		return (0);
	}
	return (1);
}

char	*put_path(char **cmd_path, int i, char *c)
{
	char	*tmp;

	tmp = ft_strjoin(cmd_path[i], c);
	free(cmd_path[i]);
	return (tmp);
}

void	found_path(char **env, two_pipe *two_pipe, int i)
{
	while (env[i])
	{
		two_pipe->path = ft_strnstr(env[i], "PATH=", 5);
		if (two_pipe->path != NULL)
			break ;
		free(two_pipe->path);
		i++;
	}
}

char	*get_the_path(char **env, char *cmd, two_pipe *two_pipe)
{
	int		i;
	char	tmp;

	i = 0;
	tmp = ':';
	found_path(env, two_pipe, i);
	two_pipe->path = ft_substr(two_pipe->path, 5, (ft_strlen(two_pipe->path) - 5));
	two_pipe->cmd_path = ft_split(two_pipe->path, &tmp);
	if (two_pipe->cmd_path == NULL)
	{
		free_all(two_pipe);
		return (NULL);
	}
	i = 0;
	while (two_pipe->cmd_path[i])
	{
		two_pipe->cmd_path[i] = put_path(two_pipe->cmd_path, i, "/");
		two_pipe->cmd_path[i] = put_path(two_pipe->cmd_path, i, cmd);
		if (access(two_pipe->cmd_path[i], F_OK | X_OK) == 0)
			return (two_pipe->cmd_path[i]);
		i++;
	}
	free_all(two_pipe);
	return (NULL);
}