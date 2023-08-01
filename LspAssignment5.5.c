#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    char inputFileName[256];
    int inputFile, outputFile, bytesRead;
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

    // Read data from the input file and create each file
    while ((bytesRead = read(inputFile, buffer, BUFFER_SIZE)) > 0) {
        // Separate the file name and its content
        char *fileName = strtok(buffer, "\n");
        char *fileContent = strtok(NULL, "\0");

        if (fileName != NULL && fileContent != NULL) {
            // Create and open the output file for writing using system call open
            outputFile = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            if (outputFile == -1) {
                printf("Error creating file: %s\n", fileName);
                continue;
            }

            // Write the file content to the output file using system call write
            write(outputFile, fileContent, bytesRead - (fileContent - buffer));

            // Close the output file
            close(outputFile);

            printf("File %s has been created.\n", fileName);
        }
    }

    // Close the input file
    close(inputFile);

    return 0;
}
