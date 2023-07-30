#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file_name> <position>\n", argv[0]);
        return 1;
    }

    char *fileName = argv[1];
    long position = atol(argv[2]);

    // Open the file in read-only mode
    int file = open(fileName, O_RDONLY);
    if (file == -1) {
        perror("Error opening the file");
        return 1;
    }

    // Move the file pointer to the specified position
    if (lseek(file, position, SEEK_SET) == -1) {
        perror("Error setting the file position");
        close(file);
        return 1;
    }

    // Read 20 bytes from the specified position
    char buffer[21]; // Including space for the null terminator
    ssize_t bytesRead = read(file, buffer, 20);
    if (bytesRead == -1) {
        perror("Error reading from the file");
        close(file);
        return 1;
    }

    // Add a null terminator to the buffer to treat it as a C-style string
    buffer[bytesRead] = '\0';

    printf("Read %zd bytes from position %ld: %s\n", bytesRead, position, buffer);

    // Close the file
    close(file);

    return 0;
}
