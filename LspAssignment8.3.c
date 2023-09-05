#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
    pid_t pid2, pid3, pid4;
    int status2, status3, status4;

    printf("Parent process1 (PID: %d)\n", getpid());

    pid2 = fork();

    if (pid2 == 0) 
    { // Child process 2
        printf("Child process2 (PID: %d)\n", getpid());
    } 
    else 
    { // Parent process1
        pid3 = fork();

        if (pid3 == 0) 
        { // Child process 3
            printf("Child process3 (PID: %d)\n", getpid());
        } 
        else 
        { // Parent process1
            pid4 = fork();

            if (pid4 == 0) 
            { // Child process 4
                printf("Child process4 (PID: %d)\n", getpid());
            } 
            else 
            { // Parent process1
                waitpid(pid2, &status2, 0);
                waitpid(pid3, &status3, 0);
                waitpid(pid4, &status4, 0);
                printf("Parent process1 (PID: %d) done.\n", getpid());
            }
        }
    }

    return 0;
}
