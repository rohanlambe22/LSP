#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    char inputFileName[256];
    int inputFile, bytesRead;
    char buffer[BUFFER_SIZE];

    // Get the input file name from the user
    printf("Enter the file name containing data of all files: ");
    scanf("%255s", inputFileName);

    // Open the input file for reading using system call open
    inputFile = open(inputFileName, O_RDONLY);
    if (inputFile == -1) {
        printf("Error opening the input file.\n");
        return 1;
    }

    // Read data from the input file and check file sizes
    while ((bytesRead = read(inputFile, buffer, BUFFER_SIZE)) > 0) {
        // Separate the file name and its content
        char *fileName = strtok(buffer, "\n");
        char *fileContent = strtok(NULL, "\0");

        if (fileName != NULL && fileContent != NULL) {
            // Calculate the file size
            int fileSize = bytesRead - (fileContent - buffer);

            // Check if the file size is greater than 10 bytes
            if (fileSize > 10) {
                printf("File Name: %s, File Size: %d bytes\n", fileName, fileSize);
            }
        }
    }

    // Close the input file
    close(inputFile);

    return 0;
}
