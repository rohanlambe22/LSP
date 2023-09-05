#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

int main() 
{
    pid_t pid1 = 0, pid2 = 0, pid3 = 0;

    // Process 1
    pid1 = fork();
    if (pid1 == 0) 
    {
        // Child process 1
        printf("Process 1 (PID: %d) is creating Process 2.\n", getpid());

        // Process 2
        pid2 = fork();
        if (pid2 == 0) 
        {
            // Child process 2
            printf("Process 2 (PID: %d) is creating Process 3.\n", getpid());

            // Process 3
            pid3 = fork();
            if (pid3 == 0) 
            {
                // Child process 3
                printf("Process 3 (PID: %d) is the leaf process.\n", getpid());
            }
        }
    }

    // Wait for all child processes to finish
    if (pid1 > 0) {
        wait(NULL);
    }
    
    return 0;
}
