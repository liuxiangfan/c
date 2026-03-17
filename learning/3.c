#include <stdio.h>
int main()
{
    FILE*file=fopen("C:\\Users\\32988\\aaa.txt","r");
    char arr[1024];
    int n=fread(arr,1,1024,file);
    printf("%d",n);
    printf("%s",arr);
    fclose(file);
    return 0;
}