#include<stdio.h>
#include<fcntl.h>


int main(int argc ,char* argv[])
{
    char Fname[20];
    int fd = 0;

    printf("Enter the file name that you want to open :\n");
    scanf("%s",Fname);

    fd = open(Fname ,O_RDONLY);
    if(fd == -1)
    {
        printf("Unable to open the file \n");
        return -1;
    }
    else
    {
        printf("File succesfully opend with fd %d \n",fd);
    }
    
    return 0;




}