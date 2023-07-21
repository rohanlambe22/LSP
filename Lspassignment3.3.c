#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/dir.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <source_directory>\n", argv[0]);
        return -1;
    }

    DIR* dp = opendir(argv[1]);
    if (dp == NULL) {
        perror("Unable to open directory");
        return -1;
    }

    struct dirent* entry;
    struct stat filestat;
    char oldname[PATH_MAX];
    char newname[PATH_MAX];
    int iCnt = 1;

    while ((entry = readdir(dp)) != NULL) {
        snprintf(oldname, PATH_MAX, "%s/%s", argv[1], entry->d_name);

        if (lstat(oldname, &filestat) == -1) {
            perror("Error accessing file");
            closedir(dp);
            return -1;
        }

        if (S_ISREG(filestat.st_mode)) { // Check if it's a regular file
            snprintf(newname, PATH_MAX, "%s/%d.txt", argv[1], iCnt);

            if (rename(oldname, newname) != 0) {
                perror("Error moving file");
                closedir(dp);
                return -1;
            }

            iCnt++;
        }
    }

    closedir(dp);
    printf("All files moved successfully from '%s'\n", argv[1]);
    return 0;
}
