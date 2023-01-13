#include "../minishell.h"

void	init(two_pipe *two_pipe)
{
    two_pipe->the_path = NULL;
    two_pipe->cmd1 = NULL;
    two_pipe->cmd2 = NULL;
    two_pipe->cmd_path = NULL;
    two_pipe->path = NULL;
    two_pipe->status = 0;
    two_pipe->i = 0;
    two_pipe->fd_in = -3;
    two_pipe->fd_out = -3;
    
}
/*
void	write_error(char *argv, t_vare *vare, char *tab)
{
	ft_putstr_fd("bash: ", 2);
	perror(argv);
	if (tab[0] == '1')
		close(vare->fd_in);
	if (tab[1] == '1')
		close(vare->fd_out);
	if (tab[2] == '1')
		close(vare->pipe_fd[1]);
	if (tab[3] == '1')
		close(vare->pipe_fd[0]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_all(vare);
	exit(EXIT_FAILURE);
}

void	write_error_2(char *argv, int i, t_vare *vare)
{
	if (i == 1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (i == 2)
	{
		ft_putstr_fd("bash: ", 2);
		perror(argv);
	}
	if (i == 3)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	free_all(vare);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

int	end_close(t_vare *vare)
{
	if (close(vare->pipe_fd[0]) < 0)
		return (write_error("pipe_fd[0]", vare, "1111"), 1);
	if (close(vare->pipe_fd[1]) < 0)
		return (write_error("pipe_fd[1]", vare, "1111"), 1);
	if (close(vare->fd_in) < 0)
		return (write_error("fd_in", vare, "1111"), 1);
	if (close(vare->fd_out) < 0)
		return (write_error("fd_out", vare, "1111"), 1);
	free_all(vare);
	return (0);
}

*/