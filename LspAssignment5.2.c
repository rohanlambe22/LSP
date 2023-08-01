#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// Define the structure to hold student information
struct Student {
    int rollNumber;
    char name[50];
    int age;
};

int main() {
    char fileName[100];
    int fd, bytesRead;
    struct Student student;

    // Get the file name from the user
    printf("Enter the file name: ");
    scanf("%99s", fileName);

    // Open the file using system call open
    fd = open(fileName, O_RDONLY);
    if (fd == -1) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Read the contents of the file using system call read
    while ((bytesRead = read(fd, &student, sizeof(struct Student))) > 0) {
        // Display the student information
        printf("Roll Number: %d\n", student.rollNumber);
        printf("Name: %s\n", student.name);
        printf("Age: %d\n\n", student.age);
    }

    // Check for read errors
    if (bytesRead == -1) {
        printf("Error reading from the file.\n");
    }

    // Close the file using system call close
    close(fd);

    return 0;
}
