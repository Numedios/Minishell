#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    char* line;
    while ((line = readline("prompt> ")) != NULL) {
        printf("%s", line);
        free(line);  // libère la mémoire allouée par readline
    }
    return 0;
}

