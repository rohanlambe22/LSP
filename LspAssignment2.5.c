#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void findLargestFile(const char *dirname) {
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        printf("Unable to open the directory '%s'\n", dirname);
        return;
    }

    struct dirent *entry;
    struct stat statbuf;
    off_t largestSize = 0;
    char largestFile[256] = "";

    while ((entry = readdir(dir)) != NULL) {
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s", dirname, entry->d_name);

        int fd = open(filepath, O_RDONLY);
        if (fd == -1)
            continue;

        if (fstat(fd, &statbuf) == 0 && S_ISREG(statbuf.st_mode)) {
            if (statbuf.st_size > largestSize) {
                largestSize = statbuf.st_size;
                strncpy(largestFile, entry->d_name, sizeof(largestFile) - 1);
            }
        }

        close(fd);
    }

    closedir(dir);

    if (largestSize > 0) {
        printf("Largest file: %s\n", largestFile);
    } else {
        printf("No files found in directory '%s'\n", dirname);
    }
}

int main() {
    char dirname[100];

    printf("Enter the directory name: ");
    scanf("%s", dirname);

    findLargestFile(dirname);

    return 0;
}
