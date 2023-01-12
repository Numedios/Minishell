#include "minishell.h"
/*

int pipex(t_maillons *maillons)
{
    while (maillons)
    {
        exec_pipex()
        //next
    }
}

int exec_pipex(maillons)
{
    //si "<" Existe
        dup(filenmae, STDIN);
    else 
        //STDIN
    si ">" existe 
        dup(filename, STDOUT)
    else
        //STDOUT
    si le maillon precedent a un > ou na pas de commande
        dup("/dev/null", STDIN)

    on lance pipex
    

}

*/


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

int find_stdin(t_maillons *maillons, int * fd_in)
{
	dprintf(2, "res = %d\n", find_if_have_output(maillons, '<'));
    if (find_if_have_output(maillons, '<') == 1)
    {
		(*fd_in) = open(find_name_sep(maillons, '<'),  O_RDWR, O_DSYNC, !O_DIRECTORY);
		return ((*fd_in));
	}
	else if (!(maillons-> prev))
	{
		return (STDIN_FILENO);
	}
	else if (find_if_have_output(maillons -> prev, '>') || !(maillons->prev->command))
	{
		(*fd_in) = open("/dev/null",  O_RDWR, O_DSYNC, !O_DIRECTORY);
		return ((*fd_in));
	}
	else
	{
		// return pipes[0] du maillons d'avant
	}
	return (-1);
}

int find_stdout(t_maillons *maillons, int *fd_out)
{
    if (find_if_have_output(maillons, '>'))
    {
		(*fd_out) = open(find_name_sep(maillons, '>'),  O_RDWR, O_DSYNC, !O_DIRECTORY);
		return ((*fd_out));
	}
	else if (!(maillons-> next))
	{
		return (STDOUT_FILENO);
	}
	else
	{
		printf("adsadsa\n");
		// return pipes[1] du maillons d'avant
	}
	return (-1);
}


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
		find_stdin(maillons, &fd_in);
		find_stdout(maillons, &fd_out);
		dup_fd(fd_in, fd_out);
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
    else 
    {
        
        //pipex_2(maillons, env);
        //2 possibilie pour pipe normal
            //on envoie a pipe la somme des pipes dont on connait le debut est la fin : infile cm1 cm cm cm cm outfile  Des qu'un infile ou un outfile interfere on arrete et on execute
            
            
            /*
            on envoie pipe par pipe : infile cm1  cm2 outfile
            exexmple : < a cat > b | < c ls > d
            on envoie a pipe : < a cat > b
            */



        //cas here_doc
    }
    //pipes = create_pipes(len); // crer (len -1) pipe
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