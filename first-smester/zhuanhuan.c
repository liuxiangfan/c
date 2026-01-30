#include <stdio.h>
int main()
{
    int num1,num2,sum;
    long long int result=0;
    long long int x=1;
    printf("Enter two numbers(十位数):");
    scanf("%d%d",&num1,&num2);
    sum=num1+num2;
    while(sum!=0)
    {
        result+=(sum%2)*x;
        sum=sum/2;
        x*=10;
    }
    printf("二进制数：%lld",result);
    return 0;
}