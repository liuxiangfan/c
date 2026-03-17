#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *file1=fopen("C:\\Users\\32988\\Desktop\\system.png","rb");
    FILE *file2=fopen("C:\\Users\\32988\\Desktop\\1.png","wb");
    int n;
    char buffer[1024];
    while((n=fread(buffer,1,1024,file1))!=0)
    {
        fwrite(buffer,1,n,file2);
    }
    fclose(file1);
    fclose(file2);
    return 0;
}
