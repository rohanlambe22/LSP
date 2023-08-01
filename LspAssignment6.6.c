#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define KB 1024

int main() {
    char fileName[256];
    int fd;
    struct stat st;

    // Get the file name from the user
    printf("Enter the file name: ");
    scanf("%255s", fileName);

    // Open the file for reading and writing using system call open
    fd = open(fileName, O_RDWR);
    if (fd == -1) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Get information about the file using system call stat
    if (fstat(fd, &st) == -1) {
        printf("Error getting file information.\n");
        close(fd);
        return 1;
    }

    // Check if the file size is less than 1 KB
    if (st.st_size < KB) {
        // Create a hole in the file by setting the file size to 1 KB using system call ftruncate
        if (ftruncate(fd, KB) == -1) {
            printf("Error creating a hole in the file.\n");
            close(fd);
            return 1;
        }
    } else if (st.st_size > KB) {
        // Truncate the remaining data beyond 1 KB using system call ftruncate
        if (ftruncate(fd, KB) == -1) {
            printf("Error truncating the file.\n");
            close(fd);
            return 1;
        }
    }

    printf("File operation completed successfully.\n");

    // Close the file
    close(fd);

    return 0;
}
