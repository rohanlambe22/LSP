#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>

int main(int argc,char * argv[]) 
{
    char filename[20];
    char mode[20];

    printf("Enter the file name: ");
    scanf("%s", filename);

    printf("Enter the file mode (read, write, R&W): ");
    scanf("%s", mode);

    int fd = open(filename, O_RDONLY);
    if (strcmp(mode,"write")== 0)
    {
        fd = open(filename, O_WRONLY, 0777);
    }
    else if(strcmp(mode,"R&W")== 0)
    {
        fd = open(filename, O_RDWR, 0777);
    }

    if (fd == -1) {
        printf("Unable to open the file.\n");
        return -1;
    } else {
        printf("File '%s' opened in mode '%s' with file descriptor %d.\n", filename, mode, fd);
    }

    close(fd);

    return 0;
}
