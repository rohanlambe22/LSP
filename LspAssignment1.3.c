#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    char filename[20];
    char mode[20];

    printf("Enter the file name: ");
    scanf("%s", filename);

    printf("Enter the file mode (read, write, R&W): ");
    scanf("%s", mode);

    int access_mode = 0;

    if (strcmp(mode, "read") == 0) {
        access_mode = R_OK;
    } else if (strcmp(mode, "write") == 0) {
        access_mode = W_OK;
    } else if (strcmp(mode, "R&W") == 0) {
        access_mode = R_OK | W_OK;
    }

    if (access(filename, access_mode) == 0) {
        printf("Process has access to file '%s' in mode '%s'.\n", filename, mode);
    } else {
        printf("Process does not have access to file '%s' in mode '%s'. Error: %s\n", filename, mode, strerror(errno));
    }

    return 0;
}
