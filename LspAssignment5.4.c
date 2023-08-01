#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    char dirName[256];
    DIR *dir;
    struct dirent *entry;
    char buffer[BUFFER_SIZE];
    int outputFile, bytesRead, inputFile;

    // Get the directory name from the user
    printf("Enter the directory name: ");
    scanf("%255s", dirName);

    // Open the directory using system call opendir
    dir = opendir(dirName);
    if (dir == NULL) {
        printf("Error opening the directory.\n");
        return 1;
    }

    // Open the output file to combine all files using system call open
    outputFile = open("AllCombine", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (outputFile == -1) {
        printf("Error opening the output file.\n");
        closedir(dir);
        return 1;
    }

    // Read the contents of all files in the directory
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Check if it's a regular file
            char filePath[512]; // Assuming the maximum file path length is 512 characters
            snprintf(filePath, sizeof(filePath), "%s/%s", dirName, entry->d_name);

            // Open the file for reading
            inputFile = open(filePath, O_RDONLY);
            if (inputFile == -1) {
                printf("Error opening file: %s\n", filePath);
                continue;
            }

            // Read from the input file and write to the output file
            while ((bytesRead = read(inputFile, buffer, BUFFER_SIZE)) > 0) {
                write(outputFile, buffer, bytesRead);
            }

            // Close the input file
            close(inputFile);
        }
    }

    // Close the output file
    close(outputFile);

    // Close the directory using system call closedir
    closedir(dir);

    printf("Contents of files in the directory have been combined into AllCombine.\n");

    return 0;
}
