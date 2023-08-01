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
    struct Student student;

    // Get student information from the user
    printf("Enter Roll Number: ");
    scanf("%d", &student.rollNumber);

    printf("Enter Name: ");
    scanf(" %[^\n]", student.name);

    printf("Enter Age: ");
    scanf("%d", &student.age);

    // Open the file using system call open
    int fd = open("students.dat", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Write the structure to the file using system call write
    ssize_t bytesWritten = write(fd, &student, sizeof(struct Student));
    if (bytesWritten != sizeof(struct Student)) {
        printf("Error writing to the file.\n");
        close(fd);
        return 1;
    } else {
        printf("Student information written to the file successfully.\n");
    }

    // Close the file using system call close
    close(fd);

    return 0;
}
