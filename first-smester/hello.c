#include <stdio.h>
int repeat_char(char*s,char c)
{
    int count=0;
    for(int i=0;s[i]!='\0';i++)
    {
        if(s[i]==c)
        {
            count++;
        }
    }
    return count;
}
char S[1000];
int main()
{
    char c;
    c= getchar();
    scanf("%s",S);
    printf("%d\n",repeat_char(S,c));
    return 0;
}