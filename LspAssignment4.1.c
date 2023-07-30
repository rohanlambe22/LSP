#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Open a file for writing
    int fileDescriptor = open("Output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fileDescriptor < 0) {
        perror("Error opening file");
        return 1;
    }

    // Redirect stdout to the file
    int savedStdout = dup(STDOUT_FILENO);
    if (dup2(fileDescriptor, STDOUT_FILENO) == -1) {
        perror("Error redirecting stdout");
        return 1;
    }

    // Print something to stdout, but it will be redirected to the file
    printf("This will be redirected to output.txt\n");

    // Close the file
    close(fileDescriptor);

    // Restore stdout to the original file descriptor
    dup2(savedStdout, STDOUT_FILENO);

    // Print something to stdout, which will be displayed on the terminal
    printf("This will be displayed on the terminal\n");

    return 0;
}
