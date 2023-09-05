#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

void writeDesktopFiles() 
{
    DIR *desktopDir = opendir("/home/codebind/Desktop");  // Change "username" to your actual username

    if (desktopDir == NULL) 
    {
        perror("Error opening desktop directory");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    FILE *file = fopen("demo.txt", "w");
    
    if (file == NULL) 
    {
        perror("Error opening demo.txt");
        closedir(desktopDir);
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(desktopDir)) != NULL) 
    {
        fprintf(file, "%s\n", entry->d_name);
    }

    closedir(desktopDir);
    fclose(file);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) 
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) 
    {
        // Child process
        writeDesktopFiles();
        exit(EXIT_SUCCESS);
    } 
    else 
    {
        // Parent process
        wait(NULL);  // Wait for the child to finish
        printf("Child process completed writing desktop files.\n");
    }

    return 0;
}
