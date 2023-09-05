#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

void deleteEmptyFiles(const char *dirPath) {
    DIR *dir;
    struct dirent *entry;
    struct stat filestat;
    char filePath[PATH_MAX];

    dir = opendir(dirPath);
    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, entry->d_name);

        if (lstat(filePath, &filestat) == -1) {
            perror("lstat");
            continue;
        }

        if (S_ISREG(filestat.st_mode) && filestat.st_size == 0) {
            if (unlink(filePath) == -1) {
                perror("unlink");
            } else {
                printf("Deleted empty file: %s\n", filePath);
            }
        }
    }

    closedir(dir);
}

int main() {
    char dirName[PATH_MAX];

    printf("Enter the directory path: ");
    fgets(dirName, sizeof(dirName), stdin);
    dirName[strcspn(dirName, "\n")] = '\0';

    deleteEmptyFiles(dirName);

    return 0;
}
