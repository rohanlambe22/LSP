#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <directory_name> <file_name>\n", argv[0]);
        return 1;
    }

    char *dirName = argv[1];
    char *fileName = argv[2];
    char filePath[512]; // Assuming the maximum file path length is 512 characters
    int fd;

    // Concatenate the directory name and file name to form the file path
    snprintf(filePath, sizeof(filePath), "%s/%s", dirName, fileName);

    // Create the file in the specified directory using system call open
    fd = open(filePath, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        printf("Error creating the file. Make sure the file doesn't exist in the specified directory.\n");
        return 1;
    }

    // Close the file
    close(fd);

    printf("File '%s' has been created in directory '%s'.\n", fileName, dirName);

    return 0;
}
