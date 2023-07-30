#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 10

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory_name>\n", argv[0]);
        return 1;
    }

    char *directoryName = argv[1];
    DIR *dir = opendir(directoryName);

    if (dir == NULL) {
        perror("Unable to open the directory");
        return 1;
    }

    // Open the new file "demo.txt"
    int newFile = open("demo.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (newFile == -1) {
        perror("Error creating or opening demo.txt");
        closedir(dir);
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Ignore directories and special files
        if (entry->d_type == DT_REG) {
            char filePath[512]; // Assuming the maximum file path length is 512 characters

            // Create the complete path of the file
            snprintf(filePath, sizeof(filePath), "%s/%s", directoryName, entry->d_name);

            // Open the regular file in read-only mode
            int file = open(filePath, O_RDONLY);
            if (file == -1) {
                perror("Error opening file");
                continue;
            }

            // Read the first 10 bytes
            char buffer[MAX_BUFFER_SIZE];
            ssize_t bytesRead = read(file, buffer, sizeof(buffer));

            if (bytesRead > 0) {
                // Write the first 10 bytes to the new file "demo.txt"
                write(newFile, buffer, bytesRead);
            }

            // Close the file
            close(file);
        }
    }

    // Close the new file "demo.txt" and the directory
    close(newFile);
    closedir(dir);

    printf("Successfully copied the first 10 bytes of all regular files to demo.txt.\n");
    return 0;
}
