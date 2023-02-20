#include "minishell.h"

int	find_stdin(t_maillons *maillons)
{
	int	res;

	res = -1;
	if (find_if_have_output(maillons -> output, "<") == 1)
	{
		res = open(find_name_sep(maillons -> output, "<"),
				O_RDWR, O_DSYNC, !O_DIRECTORY);
		return (res);
	}
	else if (find_if_have_output(maillons -> output, "<<") == 1)
	{
		res = maillons -> heredoc;
		return (res);
	}
	else if (!(maillons-> prev))
	{
		return (res);
	}
	else if (find_if_have_output(maillons -> output -> prev, ">")
		|| !(maillons->prev->command))
	{
		res = open("/dev/null", O_RDWR, O_DSYNC, !O_DIRECTORY);
		return (res);
	}
	return (-1);
}

int	find_stdout(t_maillons *maillons)
{
	int	res;

	res = -1;
	if (find_if_have_output(maillons -> output, ">"))
	{
		res = open(find_name_sep(maillons -> output, ">"),
				O_WRONLY | O_CREAT | O_TRUNC, 0644, !O_DIRECTORY);
		return (res);
	}
	else if (find_if_have_output(maillons -> output, ">>"))
	{
		res = open(find_name_sep(maillons -> output, ">>"),
				O_WRONLY | O_CREAT | O_APPEND, 0644, !O_DIRECTORY);
		return (res);
	}
	else if (!(maillons-> next))
		return (res);
	return (res);
}

int	pipex_one_condition(t_maillons *m, char ***e, t_garbage *g)
{
	if (check_if_exit(m->args, *e, g) == 0)
		return (1);
	if (check_if_builtin(m->args, *e, e, 0, g) == 0)
		return (1);
	return (0);
}

int	pipex_one_dup(t_maillons **maillons)
{
	int		fd_in;
	int		fd_out;

	if ((*maillons)->command != NULL)
	{
		fd_in = find_stdin(*maillons);
		fd_out = find_stdout(*maillons);
		if (fd_in != -1)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (fd_out != -1)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
	}
	return (1);
}

int	pipex_one(t_maillons *maillons, char ***env, t_garbage *garbage)
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;

	if (pipex_one_condition(maillons, env, garbage) == 1)
		return (free_garbage(garbage), 0);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	signal(SIGQUIT, signal_quit_child);
	signal(SIGINT, signal_quit_child);
	if (pid == 0 && check_input_output(&(maillons->output), garbage) != -1)
	{
		pipex_one_dup(&maillons);
		if (check_echo(maillons->args, 0, 0, 0) == 0)
			free_garbage_env_exit(garbage, 0);
		if (maillons->command != NULL
			&& execve(maillons->command, maillons->args, *env) == -1)
			perror("execve");
		free_garbage_env_exit(garbage, 1);
	}
	waitpid(-1, NULL, 0);
	free_garbage(garbage);
	return (0);
}
