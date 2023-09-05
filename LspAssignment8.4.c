#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid2, pid3;
    int status2, status3;

    pid2 = fork();

    if (pid2 == 0) 
    { // Child process 2
        printf("Child process2 (PID: %d)\n", getpid());
        sleep(2); // Simulate some work
        printf("Child process2 done.\n");
    } 
    else 
    { // Parent process
        pid3 = fork();

        if (pid3 == 0) 
        { // Child process 3
            printf("Child process3 (PID: %d)\n", getpid());
            sleep(3); // Simulate some work
            printf("Child process3 done.\n");
        } 
        else 
        { // Parent process
            waitpid(pid2, &status2, 0);
            waitpid(pid3, &status3, 0);
            printf("Parent process done.\n");
        }
    }

    return 0;
}
