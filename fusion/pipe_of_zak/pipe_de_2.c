#include "../minishell.h"
//test : <a ls >a | < b ls > b
//que faire si le fichier in n'exise pas ??

int	child1(two_pipe *two_pipe, char **env, int *pipe_fd, t_maillons *maillons)
{
	int	n;
	char	tmp;
	
	tmp = ' ';
	two_pipe->cmd1 = ft_split(maillons->command, &tmp);
	if (find_stdin_2(maillons, &two_pipe->fd_in, two_pipe) != 0)
		dup2(two_pipe->fd_in, STDIN_FILENO);
	if(two_pipe->fd_in != -3 && two_pipe->fd_in != -1)
        close(two_pipe->fd_in);
	if (close(two_pipe->pipe_fd[0]) < 0)
	{
		write(2,"close1\n", 7);
		exit (1);
	}
	if(find_stdout_2(maillons, &two_pipe->fd_out, two_pipe) != 0)
		dup2(two_pipe->fd_out, STDOUT_FILENO);
	if (close(two_pipe->pipe_fd[1]) < 0)
	{
		write(2,"close2\n", 7);
		exit (1);
	}	
    if(two_pipe->fd_out != -3 && two_pipe->fd_out != -1)
        close(two_pipe->fd_out);
	n = 0;
	n = check_access(maillons->command, two_pipe);
	if (n == 1)
	{
		two_pipe->the_path = get_the_path(env, maillons->command, two_pipe);
		if (two_pipe->the_path == NULL)
			return (1);
	}
	if (n != 2 && execve(two_pipe->the_path, two_pipe->cmd1 , env) < 0)
	{
		write(2,"execve!\n", 8);
		exit(1);
	}

	return (1);
}

int	child2(two_pipe *two_pipe, char **env, int *pipe_fd, t_maillons *maillons)
{
	int	n;
	char	tmp;
	int	i;
	
	
	tmp = ' ';
	two_pipe->cmd2 = ft_split(maillons->command, &tmp);
	n = 0;
	if (find_stdout_2(maillons, &two_pipe->fd_out, two_pipe) != 0)
		dup2(two_pipe->fd_out, STDOUT_FILENO);
	
    if(two_pipe->fd_out != -3 && two_pipe->fd_out != -1)
        close(two_pipe->fd_out);
	if ( close(two_pipe->pipe_fd[1]) < 0)
	{
		write(2,"close2-2\n", 9);
		exit (1);
	}
	if (find_stdin_2(maillons, &two_pipe->fd_in, two_pipe) != 0)
		dup2(two_pipe->fd_in, STDIN_FILENO);
	if(two_pipe->fd_in != -3 && two_pipe->fd_in != -1)
        close(two_pipe->fd_in);
	if(close(two_pipe->pipe_fd[0]) < 0)
	{
		write(2,"close1-2\n", 9);
		exit (1);
	}
	n = check_access(maillons->command, two_pipe);
	if (n == 1)
	{
		two_pipe->the_path = get_the_path(env, maillons->command, two_pipe);
		if (two_pipe->the_path == NULL)
			return ( 1);
	}
	if (n != 2 && execve(two_pipe->the_path, two_pipe->cmd2, env) < 0)
	{
		write(2,"execve!\n", 8);
		exit(1);
	}
	return (1);
}


int	loop(two_pipe *two_pipe, char **env, t_maillons *maillons, pid_t pid)
{
	int	n;

	n = 0;
	
	if (two_pipe->i == 0 && pid == 0)
	{
		n = child1(two_pipe, env, two_pipe->pipe_fd, maillons);
		if (n == 1)
			return (1);
	}
	if (two_pipe->i == 1 && pid == 0)
	{
		n = child2(two_pipe, env, two_pipe->pipe_fd, maillons->next);
		if (n == 1)
			return (1);
	}
	return (0);
}

int pipex_2(t_maillons  *maillons, char **env)
{
	two_pipe	two_pipe;
	pid_t	pid[2];
	int		n;

	init(&two_pipe);
	n = 0;
	if (pipe(two_pipe.pipe_fd) < 0)
	{
		write(2,"pipe_fd\n", 8);
		exit ;
	}
	while (two_pipe.i < 2)
	{
		pid[two_pipe.i] = fork();
		if (pid[two_pipe.i] < 0)
			return ( 1);
		if (loop(&two_pipe, env, maillons, pid[two_pipe.i]) != 0)
			break ;
		two_pipe.i++;
	}
	close(two_pipe.pipe_fd[1]);
	close(two_pipe.pipe_fd[0]);
	waitpid(pid[0], &two_pipe.status, 0);
	waitpid(pid[1], &two_pipe.status, 0);
	return (0);
}
