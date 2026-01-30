#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
    char a[10][10];
    int i,j;
    for( i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            a[i][j]='.';
        }
    }
    i=0;
    j=0;
    char ch='A';
    a[0][0] ='A';
    srand((unsigned)time(NULL));
    while(ch<'Z')
    {
    
        int b=rand()%4;
        if(b==0)//上
        {
            if(a[i][j+1]=='.'&&j+1<10)
            {
                j++;
                ch++;
                a[i][j]=ch;
            }
            else
            {
                continue;
            }
        }
        else if(b==1)//下
        {
            if(a[i][j-1]=='.'&&j-1>=0)
            {
                j--;
                ch++;
                a[i][j]=ch;
            }
            else
            {
                continue;
            }
        }
        else if(b==2)//左
        {
            if(a[i-1][j]=='.'&&i-1>=0)
            {
                i--;
                ch++;
                a[i][j]=ch;
            }
            else
            {
                continue;
            }
        }
        else if(b==3)     //右
        {
            if(a[i+1][j]=='.'&&i+1<10)
            {
                i++;
                ch++;
                a[i][j]=ch;
            }
            else
            {
                continue;
            }
        }
        if((a[i][j+1]!='.'||j+1>10)&&(a[i][j-1]!='.'||j-1<0)&&(a[i-1][j]!='.'||i-1<0)&&(a[i+1][j]!='.'||i+1>10))
        {
            break;
        }
    }
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            printf("%c ",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}