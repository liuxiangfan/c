#include <stdio.h>
int main()
{
    FILE*file=fopen("C:\\Users\\32988\\aaa.txt","r");
    char arr[1024];
    char* c=fgets(arr,1024,file);
    printf("%s",arr);
    fclose(file);
    return 0;
}