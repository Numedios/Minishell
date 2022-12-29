#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <readline/readline.h>

int main(int argc, char** argv) {
    char* line;

    line = readline(NULL);
        printf("%s", line);
        free(line);  // libère la mémoire allouée par readline
    return 0;
}

