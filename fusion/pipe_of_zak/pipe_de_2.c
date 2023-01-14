#include "../minishell.h"
//test : <a ls >a | < b ls > b
//que faire si le fichier in n'exise pas ??
// maillons -> command = /usr/bin/ls\
//maillons -> args = a commmand et les options
int	child1(two_pipe *two_pipe, char **env, int *pipe_fd, t_maillons *maillons)
{
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
	if (maillons -> command == NULL)
		return (1);
	if (execve(maillons -> command, maillons -> args , env) < 0)
	{
		write(2,"execve!\n", 8);
		exit(1);
	}
	return (1);
}

int	child2(two_pipe *two_pipe, char **env, int *pipe_fd, t_maillons *maillons)
{
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
	if (maillons -> command == NULL)
		return ( 1);
	if (execve(maillons-> command , maillons-> args , env) < 0)
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
