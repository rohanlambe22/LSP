#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    char fileName[256];
    int fd;
    off_t offset;
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

    // Get the offset from the user
    printf("Enter the offset from where data should be removed: ");
    scanf("%jd", &offset);

    // Get information about the file using system call stat
    if (fstat(fd, &st) == -1) {
        printf("Error getting file information.\n");
        close(fd);
        return 1;
    }

    // Check if the offset is within the file size
    if (offset < 0 || offset >= st.st_size) {
        printf("Invalid offset.\n");
        close(fd);
        return 1;
    }

    // Set the new file size to the offset using system call ftruncate
    if (ftruncate(fd, offset) == -1) {
        printf("Error removing data from the file.\n");
        close(fd);
        return 1;
    }

    printf("Data from offset %jd to the end of the file has been removed.\n", offset);

    // Close the file
    close(fd);

    return 0;
}
