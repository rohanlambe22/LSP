#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>


int main(int argc,char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s <directory_name>\n", argv[0]);
        return 1;
    }

    char *directory_name = argv[1];

    // filter for check if directory already exists
    struct stat st;

    if(stat(directory_name,&st)== 0 && S_ISDIR(st.st_mode))
    {
        printf("Directory %s already exists \n",directory_name);
        return 1;
    }

   // creat new directory using mkdir system call 
    int result = mkdir(directory_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    if(result == 0)
    {
        printf("New Directory %s is creadted successfully \n",directory_name);
    }
    else
    {
        printf("Unable to creat new director \n");
        perror("Error");
    }

    return 0;

}