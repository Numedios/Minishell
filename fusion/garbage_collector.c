#include "minishell.h"

void	initialize_garbage(t_garbage *garbage)
{
	garbage = malloc(sizeof(t_garbage));
	garbage->split = NULL;
	garbage->split__lst = NULL;
	garbage->output = NULL;
	garbage->maillons = NULL;
}


