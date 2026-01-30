#include <stdio.h>
int main()
{
    double num = 123.456;
    char str[50];
    sprintf(str, "Formatted number: %.2f", num);
    printf("%s\n", str);
}