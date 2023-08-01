#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char fileName[256];
    int fd;

    // Get the file name from the user
    printf("Enter the file name: ");
    scanf("%255s", fileName);

    // Open the file in write-only mode, creating if not exists, and with read-write permissions
    fd = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Set the file size to 1 KB (1024 bytes) using lseek
    if (lseek(fd, 1024, SEEK_END) == -1) {
        printf("Error creating a hole in the file.\n");
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);

    printf("A hole of 1 KB has been created at the end of the file.\n");

    return 0;
}
