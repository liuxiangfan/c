#include <stdio.h>
void swap(void *p1,void *p2,int len); 
int main()
{
    int a=10;
    int b=20;
    printf("Before swap:a=%d,b=%d\n",a,b);
    swap(&a,&b,sizeof(int));
    printf("After swap:a=%d,b=%d\n",a,b);
}
void swap(void *p1,void *p2,int len)
{
    char *a=(char *)p1;
    char *b=(char *)p2;
    for(int i=0;i<len;i++)
    {
        char temp=*(a+i);
        *(a+i)=*(b+i);
        *(b+i)=temp;
    }
}