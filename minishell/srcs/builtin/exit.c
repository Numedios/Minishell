#include "../../includes/minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

int exit(int statut)
{
    exit(statut);
}