#include "minishell.h"

int	dup_fd(int new_stdin, int new_stdout)
{
	if (dup2(new_stdin, STDIN_FILENO) == -1
		|| dup2(new_stdout, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}

void	create_pipe(int *pipes, int i)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
	pipes[i] = pipe_fd[0];
	pipes[i + 1] = pipe_fd[1];
}

int	*create_pipes(int len)
{
	int	*pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * (len * 2));
	while (i < len * 2)
	{
		create_pipe(pipes, i);
		if (!pipes[i] || !pipes[i + 1])
			return (NULL);
		i = i + 2;
	}
	i = 0;
	return (pipes);
}

int find_stdin(t_maillons *maillons)
{
	int res;

	res = -1;
    if (find_if_have_output(maillons -> output, "<") == 1)
    {
		dprintf(2, "entrer est %s\n",  find_name_sep(maillons -> output, "<"));
		res = open(find_name_sep(maillons -> output, "<"),  O_RDWR, O_DSYNC, !O_DIRECTORY);
		return (res);
	}
	else if (find_if_have_output(maillons -> output, "<<") == 1)
    {
		dprintf(2, "entrer est %s\n",  find_name_sep(maillons -> output, "<<"));
		res = heredoc(find_name_sep(maillons -> output, "<<"));
		return (res);
	}

	else if (!(maillons-> prev))
	{
		return res;
	}
	else if (find_if_have_output(maillons -> output -> prev, ">") || !(maillons->prev->command))
	{
		res = open("/dev/null",  O_RDWR, O_DSYNC, !O_DIRECTORY);
		return (res);
	}
	else
	{
		// return pipes[0] du maillons d'avant
	}
	return (-1);
}

int find_stdout(t_maillons *maillons)
{
	int res;

	res = -1;
    if (find_if_have_output(maillons -> output, ">"))
    {
		dprintf(2, "Sortie est %s\n",  find_name_sep(maillons -> output, ">"));
		res = open(find_name_sep(maillons -> output, ">"), O_WRONLY | O_CREAT | O_TRUNC, 0644, !O_DIRECTORY);
		return (res);
	}
	else if (find_if_have_output(maillons -> output, ">>"))
	{
		res = open(find_name_sep(maillons -> output, ">>"),  O_WRONLY | O_CREAT | O_APPEND, 0644, !O_DIRECTORY);
		return (res);
	}
	else if (!(maillons-> next))
	{
		return (res);
	}
	else
	{
		// return pipes[1] du maillons d'avant
	}
	return (res);
}


int pipex_one(t_maillons  *maillons, char **env)
{
    pid_t	pid;
	char *a[3];
    int fd_in;
    int fd_out;

    pid = fork();
    if (pid == -1)
			return (perror("fork"), 1);
	if (pid == 0)
	{
		fd_in = find_stdin(maillons);
		fd_out = find_stdout(maillons);
        if(fd_in != -1)
		{
			dup2(fd_in, STDIN_FILENO);
            close(fd_in);
		}
        if(fd_out != -1)
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
	return(0);
}



int pipex(t_maillons *maillons, char **env)
{
    int *pipes;
    int len;

    len = ft_strlen_maillons(maillons); // nombre de maillons
    if (len == 1)
	{
        pipex_one(maillons, env);
        //ajoute le cas here_doc
	}
    return (0);


}
/*
int pipex_one(t_maillons  *maillons, char **env)
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