#include <stdio.h>
typedef struct 
{
    char category[20];//类别
    float price;//价格
    char producer[20];//生产厂商
    char materials[100];//原料
}Item;

int main()
{
    Item item;
    int n;
    printf("Catagory=");
    scanf("%s",&item.category);
    printf("Price=");
    scanf("%f",&item.price);
    printf("Producer=");
    scanf("%s",&item.producer);
    printf("Number of materials=");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        printf("Material %d=",i+1);
        scanf("%s",&item.materials[i]);
    }
    return 0;
}