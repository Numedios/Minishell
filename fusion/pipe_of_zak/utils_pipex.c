#include "../minishell.h"

int find_stdin_2(t_maillons *maillons, int * fd_in, two_pipe *two_pipe)
{
	dprintf(2, "res = %d\n", find_if_have_output(maillons -> output, "<"));
    if (find_if_have_output(maillons -> output, "<") == 1)
    {
		(*fd_in) = open(find_name_sep(maillons -> output, "<"),  O_RDWR, O_DSYNC, !O_DIRECTORY);
		if ((*fd_in) == -1)
		{
			dup2(two_pipe->pipe_fd[0], STDIN_FILENO);
			return (0);
		}
		return ((*fd_in));
	}
	else if (!(maillons-> prev))
	{
		return (0);
	}
	else if (find_if_have_output(maillons -> prev -> output, ">") || !(maillons->prev->command))
	{
		dprintf(2,"je suis rentre\n");
		dup2(two_pipe->pipe_fd[0], STDIN_FILENO);
	//	(*fd_in) = open("/dev/null",  O_RDWR, O_DSYNC, !O_DIRECTORY);
		return ((*fd_in));
	}
	else
	{
		dup2(two_pipe->pipe_fd[0], STDIN_FILENO);
		return (0);
	}
	return (-1);
}

int find_stdout_2(t_maillons *maillons, int *fd_out, two_pipe *two_pipe)
{
	if (((two_pipe-> fd_in) == -1))
	{
		(*fd_out) = open("/dev/null",  O_RDWR, O_DSYNC, !O_DIRECTORY);
		return ((*fd_out));
	}
    if (find_if_have_output(maillons -> output, ">"))
    {
		(*fd_out) = open(find_name_sep(maillons -> output, ">"),  O_RDWR, O_DSYNC, !O_DIRECTORY);
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
	}
	return (-1);
}
