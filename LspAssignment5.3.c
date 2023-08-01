#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

// Define the structure to hold file information
struct FileInfo {
    char fileName[256];
    off_t fileSize;
};

int main() {
    char dirName[256];
    struct FileInfo fileInfo;
    DIR *dir;
    struct dirent *entry;

    // Get the directory name from the user
    printf("Enter the directory name: ");
    scanf("%255s", dirName);

    // Open the directory using system call opendir
    dir = opendir(dirName);
    if (dir == NULL) {
        printf("Error opening the directory.\n");
        return 1;
    }

    // Open the output file to write file information using system call open
    int outputFile = open("file_info.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (outputFile == -1) {
        printf("Error opening the output file.\n");
        closedir(dir);
        return 1;
    }

    // Read information about all regular files in the directory
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            // Get the file name
            snprintf(fileInfo.fileName, sizeof(fileInfo.fileName), "%s/%s", dirName, entry->d_name);

            // Get the file size
            struct stat st;
            if (stat(fileInfo.fileName, &st) == 0) {
                fileInfo.fileSize = st.st_size;

                // Write the file information to the output file using system call write
                write(outputFile, &fileInfo, sizeof(struct FileInfo));
            }
        }
    }

    // Close the output file
    close(outputFile);

    // Close the directory using system call closedir
    closedir(dir);

    // Read the contents of the output file
    outputFile = open("file_info.txt", O_RDONLY);
    if (outputFile == -1) {
        printf("Error opening the output file for reading.\n");
        return 1;
    }

    // Read and display the file information from the output file
    printf("Contents of file_info.txt:\n");
    while (read(outputFile, &fileInfo, sizeof(struct FileInfo)) > 0) {
        printf("File Name: %s, File Size: %ld bytes\n", fileInfo.fileName, fileInfo.fileSize);
    }

    // Close the output file after reading
    close(outputFile);

    return 0;
}
