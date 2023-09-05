#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

extern char **environ; // External variable that holds the environment

int main() 
{
    char **env = environ;

    printf("Environment variables:\n");

    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }

    return EXIT_SUCCESS;
}
