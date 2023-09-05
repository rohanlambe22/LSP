#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void performWork() {
    for (int i = 0; i < 10; i++) {
        printf("%d ", i); // Adding a space for spacing
    }
    printf("\n"); // Adding a newline at the end of the work
}

int main() {
    int Ret = 0;
    int cpid = 0;
    int Exit_status = 0;

    Ret = fork();

    if (Ret == 0)  // Child
    {
        printf("Child process is running with PID: %d\n", getpid());
        performWork(); // Simulate some work in the child process
    }
    else  // Parent
    {
        printf("Parent is running with PID: %d\n", getpid());
        cpid = wait(&Exit_status); // Wait for child to terminate

        if (WIFEXITED(Exit_status)) {
            printf("Parent: Child process with PID %d terminated normally.\n", cpid);
        } else if (WIFSIGNALED(Exit_status)) {
            printf("Parent: Child process with PID %d terminated due to a signal.\n", cpid);
        }

        printf("Parent process terminated with PID %d\n", getpid());
    }

    return 0;
}
