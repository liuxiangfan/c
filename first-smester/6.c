#include<stdio.h>
int main()
{
    int a,b,c,d,sum;
    printf("Enter a dollar amount:");
    scanf("%d",&sum);
    a=sum/20;
    sum%=20;
    b=sum/10;
    sum%=10;
    c=sum/5;
    sum%=5;
    d=sum;
    printf("$20 bills: %d",a);
    printf("$10 bills: %d",b);
    printf("$5 bills: %d",c);
    printf("$1 bills: %d",d);
    return 0;
    
}