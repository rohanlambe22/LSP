#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

void createDaemon() 
{
    pid_t pid;

    // Fork off the parent process
    pid = fork();

    if (pid < 0) 
    {
        exit(EXIT_FAILURE);
    }

    // If we got a good PID, then we can exit the parent process.
    if (pid > 0) 
    {
        exit(EXIT_SUCCESS);
    }

    // Change the file mode mask
    umask(0);

    // Create a new SID for the child process
    if (setsid() < 0) 
    {
        exit(EXIT_FAILURE);
    }

    // Change the current working directory to root
    chdir("/");

    // Close the standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main() {
    // Create a daemon process
    createDaemon();

    // Now your process is running as a daemon
    // You can add your daemon logic here

    // For demonstration, let's make the daemon sleep for a while
    while (1) {
        sleep(10);
    }

    return 0;
}
