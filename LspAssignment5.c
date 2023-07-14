#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc,char * argv[]) {
    char filename[20];
    int numBytes;

    printf("Enter the file name: ");
    scanf("%s", filename);

    printf("Enter the number of bytes to read: ");
    scanf("%d", &numBytes);

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Unable to open the file.\n");
        return -1;
    }

    char buffer[BUFFER_SIZE];
    int bytesRead = read(fd, buffer, numBytes);
    if (bytesRead == -1) {
        printf("Error while reading the file.\n");
        close(fd);
        return -1;
    }

    printf("Read %d bytes from the file:\n", bytesRead);
    write(STDOUT_FILENO, buffer, bytesRead);

    close(fd);
    return 0;
}
