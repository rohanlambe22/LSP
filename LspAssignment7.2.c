//Client2.c
#include <stdio.h>
#include<stdlib.h>
#include <dlfcn.h>
#include"Sharedfile2.h"

int main(int argc, char* argv[])
{
    void *ptr = NULL;
    int Result = 0;

    if(argc != 3)
    {
        printf("Insuficinet Argument\n");
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return -1;
    }
    
   ptr = dlopen("library.so",RTLD_LAZY);

   if(ptr == NULL)
   {
    printf("Unable to load Library\n");
    return -1;
   }
   
    int (*CompareFiles)(const char *, const char *) = dlsym(ptr, "CompareFiles");

    if (CompareFiles == NULL)
    {
        printf("Unable to open the Function\n");
        return -1;
    }

    Result = CompareFiles(argv[1],argv[2]);
    if (Result == 1)
    {
        printf("The files are identical.\n");
    }
    else
    {
        printf("The files are different.\n");
    }

    dlclose(ptr);
    return 0;
    

}


