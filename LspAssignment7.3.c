// NumberChecker.c
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "SharedFile1.h"
#include "SharedFile2.h"

typedef int (*CheckFunc)(int);

int main() 
{
    void *primeLib = dlopen("libPrimeLibrary.so", RTLD_LAZY);
    void *perfectLib = dlopen("libPerfectLibrary.so", RTLD_LAZY);

    if (!primeLib || !perfectLib) {
        printf("Unable to load libraries\n");
        return -1;
    }

    CheckFunc isPrimeFunc = (CheckFunc)dlsym(primeLib, "isPrime");
    CheckFunc isPerfectFunc = (CheckFunc)dlsym(perfectLib, "isPerfect");

    if (!isPrimeFunc || !isPerfectFunc) {
        printf("Unable to load functions\n");
        dlclose(primeLib);
        dlclose(perfectLib);
        return -1;
    }

    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (isPrimeFunc(num)) {
        printf("%d is prime.\n", num);
    } else {
        printf("%d is not prime.\n", num);
    }

    if (isPerfectFunc(num)) {
        printf("%d is a perfect number.\n", num);
    } else {
        printf("%d is not a perfect number.\n", num);
    }

    dlclose(primeLib);
    dlclose(perfectLib);
    return 0;
}
