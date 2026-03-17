#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef struct node
{
    ElemType data;
    struct node *next;
}Node;
Node *initNode()//初始化链表，返回头结点地址
{
    Node *head=(Node*)malloc(sizeof(Node));
    head->next=NULL;
    head->data=0;
    return head;
}
int insertHead(Node *L,ElemType e)//头插法
{
    Node *p=(Node*)malloc(sizeof(Node));
    p->data=e;
    p->next=L->next;
    L->next=p;
    return 1;
}
Node *get_tail(Node *L)//获取链表尾节点
{
    Node *p=L;
    while(p->next!=NULL)
    {
        p=p->next;
    }
    return p;
}
Node *insertTail(Node *tail,ElemType e)//尾插法
{
    Node *p=(Node*)malloc(sizeof(Node));
    p->data=e;
    tail->next=p;
    p->next=NULL;
    return p;
}
int insertNode(Node*L,int pos,ElemType e)//指定位置插入
{
    Node *p=L;
    for(int i=1;i<pos;i++)
    {
        p=p->next;
        if(p==NULL)
        {
            printf("插入位置不合法\n");
            return 0;
        }
    }
    Node *new=(Node*)malloc(sizeof(Node));
    new->data=e;
    new->next=p->next;
    p->next=new;
    return 1;
}
int deleteNode(Node*L,int pos,ElemType *e)//删除指定位置节点
{
    Node *p=L;
    for(int i=1;i<pos;i++)
    {
        p=p->next;
        if(p==NULL)
        {
            printf("删除位置不合法\n");
            return 0;
        }
    }
    *e=p->next->data;
    Node *temp=p->next;
    p->next=temp->next;
    free(temp);
    return 1;
}
void listNode(Node *L)//遍历链表
{
    Node *p=L->next;
    while(p!=NULL)//不能是p->next!=NULL，因为最后一个节点的next是NULL，不能访问到最后一个节点   
    {
        printf("%d\n",p->data);
        p=p->next;
    }
}
int listLength(Node *L)//获取链表长度
{
    Node *p=L->next;
    int len=0;
    while(p!=NULL)
    {
        len++;
        p=p->next;
    }
    return len;
}
void freeList(Node *L)//释放链表
{
    Node *p=L->next;
    Node *q;
    while(p!=NULL)
    {
        q=p->next;
        free(p);
        p=q;
    }
    free(L); 
}
/*--------------example1--------------*/
