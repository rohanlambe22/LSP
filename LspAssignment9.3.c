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

    int priority = getpriority(PRIO_PROCESS, pid);

    if (priority == -1) 
    {
        perror("getpriority");
        return 1;
    }

    printf("Priority of process with PID %d is %d\n", pid, priority);

    return 0;
}
