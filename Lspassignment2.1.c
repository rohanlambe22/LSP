#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    char filename[20];

    printf("Enter the file name: ");
    scanf("%s", filename);

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Unable to open the file.\n");
        return -1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    if (bytesRead == -1) {
        printf("Error while reading the file.\n");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}
