#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    int pid = atoi(argv[1]); // Convert the PID argument to an integer

    int currentPriority = getpriority(PRIO_PROCESS, pid);
    if (currentPriority == -1) 
    {
        perror("getpriority");
        return 1;
    }

    int newPriority = currentPriority - 5; // Increase the priority by 5
    
    if (setpriority(PRIO_PROCESS, pid, newPriority) == -1) 
    {
        perror("setpriority");
        return 1;
    }

    printf("Increased priority of process with PID %d by 5.\n", pid);

    return 0;
}
