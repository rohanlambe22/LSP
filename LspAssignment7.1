// Client1.c
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include<string.h>s
#include "Sharedfile1.h"

typedef int (*ArithmeticFunc)(int, int);

int main() 
{
    void *ptr = NULL;
    ArithmeticFunc additionFunc, subtractionFunc, multiplicationFunc, divisionFunc;
    int num1 = 0 , num2 = 0 , choice = 0, Result = 0;
    char operation[20];

    ptr = dlopen("libSharedfile1.so", RTLD_LAZY);
    if (ptr == NULL) 
    {
      printf("Unable to load Library: %s\n", dlerror());
     return -1;
    }


    additionFunc = (ArithmeticFunc)dlsym(ptr, "Addition");
    subtractionFunc = (ArithmeticFunc)dlsym(ptr, "Subtraction");
    multiplicationFunc = (ArithmeticFunc)dlsym(ptr, "Multiplication");
    divisionFunc = (ArithmeticFunc)dlsym(ptr, "Division");

    if (additionFunc == NULL || subtractionFunc == NULL || multiplicationFunc == NULL || divisionFunc == NULL) 
    {
        printf("Unable to open the Function\n");
        return -1;
    }

    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);

    printf("Menu:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);

    switch (choice) 
    {
        case 1:
            Result = additionFunc(num1, num2);
            strcpy(operation, "Addition");
            break;
        case 2:
            Result = subtractionFunc(num1, num2);
            strcpy(operation, "Subtraction");
            break;
        case 3:
            Result = multiplicationFunc(num1, num2);
            strcpy(operation, "Multiplication");
            break;
        case 4:
            Result = divisionFunc(num1, num2);
            strcpy(operation, "Division");
            break;
        default:
            printf("Invalid choice\n");
            return -1;
    }
    
    printf("Result of %s: %d\n", operation, Result);

    dlclose(ptr);
    return 0;
}
