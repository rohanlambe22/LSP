#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<string.h>

int main(int argc, char* argv[]) 
{
    char filename[20];
    char str[100];

    printf("Enter the file name: ");
    scanf("%s", filename);

    printf("Enter the string to write: ");
    scanf("%s", str);

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd == -1) 
    {
        printf("Unable to open the file\n");
        return -1;
    }

    if (write(fd, str, strlen(str)) == -1) 
    {
        printf("Error while writing to the file\n");
        close(fd);
        return -1;
    }

    close(fd);

    printf("String '%s' written to the file '%s' successfully.\n", str, filename);

    return 0;
}
