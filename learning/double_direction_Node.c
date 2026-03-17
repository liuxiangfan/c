#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef struct node
{
    ElemType data;
    struct node* next;
    struct node* prev;
}Node;
Node* initNode()//初始化链表，返回头结点地址
{
    Node* head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    head->prev = NULL;
    head->data = 0;
    return head;
}
int insertHead(Node *L,ElemType e)
{
    Node *p=(Node*)malloc(sizeof(Node));
    p->data=e;
    p->prev=L;
    p->next=L->next;
    if(L->next!=NULL)
    {
        L->next->prev=p;
    }
    L->next=p;
    return 1;
}
Node *get_tail(Node* L)
{
    Node* p=L;
    while(p->next!=NULL)
    {
        p=p->next;
    }
    return p;
}
Node* insertTail(Node *tail,ElemType e)
{
    Node *new=(Node*)malloc(sizeof(Node));
    tail->next=new;
    new->prev=tail;
    new->next=NULL;
    new->data=e;
    return new;
}