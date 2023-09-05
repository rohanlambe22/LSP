#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

void countCapital(const char *filename, int *capitalCount) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) 
    {
        if (isupper(ch)) {
            (*capitalCount)++;
        }
    }

    fclose(file);
}

int main() 
{
    char file1Name[100], file2Name[100];
    printf("Enter the name of the first file: ");
    scanf("%s", file1Name);
    printf("Enter the name of the second file: ");
    scanf("%s", file2Name);

    int pid1 = fork();
    if (pid1 < 0) 
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } 
    else if (pid1 == 0) 
    {
        // Child process 1
        int capitalCount1 = 0;
        countCapital(file1Name, &capitalCount1);

        FILE *countFile = fopen("Count.txt", "w");
        if (countFile == NULL) 
        {
            perror("Error opening Count.txt");
            exit(EXIT_FAILURE);
        }
        
        fprintf(countFile, "Count from process 1: %d\n", capitalCount1);
        fclose(countFile);
        
        exit(EXIT_SUCCESS);
    } 
    else 
    {
        // Parent process
        int pid2 = fork();
        if (pid2 < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            // Child process 2
            int capitalCount2 = 0;
            countCapital(file2Name, &capitalCount2);

            FILE *countFile = fopen("Count.txt", "a");
            if (countFile == NULL) {
                perror("Error opening Count.txt");
                exit(EXIT_FAILURE);
            }
            
            fprintf(countFile, "Count from process 2: %d\n", capitalCount2);
            fclose(countFile);
            
            exit(EXIT_SUCCESS);
        } 
        else
        {
            // Parent process
            wait(NULL); // Wait for both child processes
            printf("Both child processes completed counting.\n");
        }
    }

    return 0;
}
