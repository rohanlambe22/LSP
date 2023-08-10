#include<stdio.h>
#include "Sharedfile1.h"

int Addition(int no1, int no2)
{
    int iAns = 0;
    iAns = no1 + no2;
    return iAns;
}

int Subtraction(int no1, int no2)
{
    int iAns = 0;
    iAns = no1 - no2;
    return iAns;
}

int Multiplication(int no1, int no2)
{
    int iAns = 0;
    iAns = no1 * no2;
    return iAns;
}

int Division(int no1, int no2)
{
    int iAns = 0;
    iAns = no1/no2;
    return iAns;
}