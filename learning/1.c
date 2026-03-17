#include <stdio.h>
void method1();
int method2(int num1,int num2);
int main()
{
	//定义指针指向两个函数
	void (*p1)()=method1;
	int (*p2)(int num1,int num2)=method2;
	//利用函数指针去调用函数
	p1();
	int num=p2(10,20);
	printf("%d\n",num);
}
void method1()
{
	printf("method1\n");
}
int method2(int num1,int num2)
{
	printf("method2\n");
	return num1+num2;
}