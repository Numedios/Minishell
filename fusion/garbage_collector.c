#include "minishell.h"

void	initialize_garbage(t_garbage *garbage)
{
	garbage-> split_pipe = NULL;
	garbage -> split_lst = NULL;
	garbage -> maillons = NULL;
	garbage -> pipes = NULL;
}

