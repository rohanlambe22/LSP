#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory_name>\n", argv[0]);
        return 1;
    }

    char *dirName = argv[1];
    DIR *dir;
    struct dirent *entry;
    struct stat st;

    // Open the directory using system call opendir
    dir = opendir(dirName);
    if (dir == NULL) {
        printf("Error opening the directory.\n");
        return 1;
    }

    // Read the contents of the directory and delete files greater than 100 bytes
    while ((entry = readdir(dir)) != NULL) {
        char filePath[512]; // Assuming the maximum file path length is 512 characters
        snprintf(filePath, sizeof(filePath), "%s/%s", dirName, entry->d_name);

        // Get information about the file using system call stat
        if (stat(filePath, &st) == -1) {
            printf("Error getting file information: %s\n", filePath);
            continue;
        }

        // Check if the entry is a regular file and its size is greater than 100 bytes
        if (S_ISREG(st.st_mode) && st.st_size > 100) {
            // Delete the file using system call unlink
            if (unlink(filePath) == 0) {
                printf("File %s has been deleted.\n", entry->d_name);
            } else {
                printf("Error deleting file: %s\n", entry->d_name);
            }
        }
    }

    // Close the directory using system call closedir
    closedir(dir);

    return 0;
}
