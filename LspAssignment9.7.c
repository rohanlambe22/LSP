#include <stdio.h>
#include <stdlib.h>

int main() 
{
    char *home_dir = getenv("HOME");      // getenv c Library function 
    char *login_name = getenv("LOGNAME");

    if (home_dir != NULL) 
    {
        printf("Home Directory: %s\n", home_dir);
    } 
    else 
    {
        printf("Home Directory not found in environment variables.\n");
    }

    if (login_name != NULL) 
    {
        printf("Login Username: %s\n", login_name);
    } 
    else 
    {
        printf("Login Username not found in environment variables.\n");
    }

    return EXIT_SUCCESS;
}
