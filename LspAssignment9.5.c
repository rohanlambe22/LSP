#define _GNU_SOURCE // Required for sched_yield
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main() {
    int result;

    printf("Before yielding...\n");

    result = sched_yield();

    if (result == 0) {
        printf("Yield successful.\n");
    } else {
        perror("Yield failed");
        return EXIT_FAILURE;
    }

    printf("After yielding...\n");

    return EXIT_SUCCESS;
}
