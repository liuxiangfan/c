#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int ElemType;
/*顺序表的动态内存地址初始化
typpedef struct
{
    ElemType *data;
    int length;
}Seqlist;
Seqlist* initList()
{
    Seqlist *L = (Seqlist*)malloc(sizeof(Seqlist));
    L->data = (ElemType*)malloc(MAXSIZE * sizeof(ElemType));
    L->length = 0;
    return L;
}
*/
typedef struct
{
    ElemType data[MAXSIZE];
    int length;
}Seqlist;
void initList(Seqlist *L)//初始化顺序表
{
    L->length = 0;
}
int addElem(Seqlist *L,ElemType e)//尾部添加元素
{
    if(L->length>=MAXSIZE)
    {
        printf("顺序表已满，无法添加元素");
        return 0;
    }
    L->data[L->length]=e;
    L->length++;
    return 1;    
}
void listElem(Seqlist *L)//遍历
{
    for(int i=0;i<L->length;i++)
    {
        printf("%d\n",L->data[i]);
    }
}
int insertElem(Seqlist *L,int pos,ElemType e)//插入元素
{
    if(pos<1||pos>L->length)
    {
        printf("位置不合法，无法插入元素");
        return 0;
    }
    if(L->length>=MAXSIZE)
    {
        printf("顺序表已满，无法插入元素");
        return 0;
    }
    for(int i=L->length-1;i>=pos-1;i--)
    {
        L->data[i+1]=L->data[i];
    }
    L->data[pos-1]=e;
    L->length++;
    return 1;
}
int deleteElem(Seqlist *L,int pos,ElemType *e)//删除元素，用指针e返回被删除的元素值
{
    if(pos<1||pos>L->length)
    {
        printf("位置不合法，无法删除元素");
        return 0;
    }
    *e=L->data[pos-1];
    for(int i=pos;i<L->length;i++)
    {
        L->data[i-1]=L->data[i];
    }
    L->length--;
    return 1;
}
int findElem(Seqlist *L,ElemType e)//查找元素，返回位置
{
    for(int i=0;i<L->length;i++)
    {
        if(L->data[i]==e)
        {
            return i+1;
        }
    }
    return 0;
}
int main()
{
    Seqlist L;
    initList(&L);
    addElem(&L,1);
    addElem(&L,2);
    addElem(&L,3);
    listElem(&L);
    int e;
    deleteElem(&L,2,&e);
    printf("删除的元素是：%d\n",e);
    listElem(&L);
    insertElem(&L,2,4);
    listElem(&L);
    return 0;
}