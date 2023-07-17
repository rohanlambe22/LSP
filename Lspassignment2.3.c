#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void printFilesInDirectory(const char *dirname) {
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        printf("Unable to open the directory '%s'\n", dirname);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        struct stat statbuf;
        char filepath[256];

        snprintf(filepath, sizeof(filepath), "%s/%s", dirname, entry->d_name);
        if (stat(filepath, &statbuf) == 0 && S_ISREG(statbuf.st_mode)) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main() {
    char dirname[100];

    printf("Enter the directory name: ");
    scanf("%s", dirname);

    printf("Files in directory '%s':\n", dirname);
    printFilesInDirectory(dirname);

    return 0;
}
