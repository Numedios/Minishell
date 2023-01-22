#include "minishell.h"

int	dup_fd(int new_stdin, int new_stdout)
{
	if (dup2(new_stdin, STDIN_FILENO) == -1
		|| dup2(new_stdout, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}

int	find_stdin(t_maillons *maillons)
{
	int	res;

	res = -1;
	if (find_if_have_output(maillons -> output, "<") == 1)
	{
		//dprintf(2, "entrer est %s\n", find_name_sep(maillons -> output, "<"));
		res = open(find_name_sep(maillons -> output, "<"), O_RDWR, O_DSYNC, !O_DIRECTORY);
		return (res);
	}
	else if (find_if_have_output(maillons -> output, "<<") == 1)
	{
		//dprintf(2, "entrer est %s\n", find_name_sep(maillons -> output, "<<"));
		res = maillons -> heredoc;
		return (res);
	}

	else if (!(maillons-> prev))
	{
		return res;
	}
	else if (find_if_have_output(maillons -> output -> prev, ">") || !(maillons->prev->command))
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
		//dprintf(2, "Sortie est %s\n", find_name_sep(maillons -> output, ">"));
		res = open(find_name_sep(maillons -> output, ">"), O_WRONLY | O_CREAT | O_TRUNC, 0644, !O_DIRECTORY);
		return (res);
	}
	else if (find_if_have_output(maillons -> output, ">>"))
	{
		res = open(find_name_sep(maillons -> output, ">>"), O_WRONLY | O_CREAT | O_APPEND, 0644, !O_DIRECTORY);
		return (res);
	}
	else if (!(maillons-> next))
	{
		return (res);
	}
	return (res);
}


int	pipex_one(t_maillons *maillons, char **env, t_garbage *garbage)
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;


	pid = fork();
	if (pid == -1)
			return (perror("fork"), 1);
	if (pid == 0)
	{
		fd_in = find_stdin(maillons);
		fd_out = find_stdout(maillons);
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
		if (execve(maillons ->command, maillons -> args , env) == -1)
		{
			perror("execve");
			exit (1);
		}
		return (1);
	}
	waitpid(-1 , NULL, 0);
	return (0);
}



int	pipex(t_maillons *maillons, char **env, t_garbage *garbage)
{
	int	*pipes;
	int	len;

	//ft_print_garbage(garbage);
	len = ft_strlen_maillons(maillons); // nombre de maillons
	if (len == 0)
		return(0);

	if (len == 1)
	{
		pipex_one(maillons, env, garbage);
	}
	if (len != 1)
	{
		pipex_multiple(maillons, env, len, garbage);
	}
	return (0);
}

/*
int pipex_one(t_maillons *maillons, char **env)
{
	pid_t	pid;
	char *a[2];
	int fd_in;
	int fd_out;

	fd_in = -3;
	fd_out = -3;
	a[0] = ft_strdup("cat");
	a[1] = 0;
	pid = fork();
	if (pid == -1)
			return (perror("fork"), 1);
	if (pid == 0)
	{

		dup_fd(find_stdin(maillons, &fd_in), find_stdout(maillons, &fd_out));
		if(fd_in != -3)
			close(fd_in);
		if(fd_out != -3)
			close(fd_out);
		if (execve("/usr/bin/cat", a , env) == -1)
		{
			perror("execve");
			exit (1);
		}
		return (1);
	}
	waitpid(-1 , NULL, 0);
	free(a[0]);
	return(0);
}
*/
