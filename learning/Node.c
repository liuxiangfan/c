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
Node *initNodeWithElem(ElemType e)//初始化链表，返回头结点地址
{
    Node *head=(Node*)malloc(sizeof(Node));
    head->next=NULL;
    head->data=e;
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
//快慢指针，快指针先走k步，然后快慢指针一起走，直到快指针走到链表末尾，此时慢指针所在位置就是倒数第k个节点
int findNodeFS(Node *L,int k)//查找倒数第k个节点
{
    Node *Fast=L->next;
    Node *Slow=L->next;
    if(k>listLength(L))
    {
        printf("查找超出范围\n");
    }
    for(int i=1;i<=k;i++)
    {
        Fast=Fast->next;
    }
    while(Fast!=NULL)
    {
        Fast=Fast->next;
        Slow=Slow->next;
    }
    printf("倒数第%d个节点值为:%d\n",k,Slow->data);
    return 1;
}
//int main()
//{
//    Node *L=initNode();
//    Node *tail=get_tail(L);
//    tail=insertTail(tail,1);
//    tail=insertTail(tail,2);
//    tail=insertTail(tail,3);
//    tail=insertTail(tail,4);
//    tail=insertTail(tail,5);
//    findNodeFS(L,3);
//    return 0;
//}
/*--------------example2--------------*/
int findSameNode(Node*L1,Node*L2)//查找两个来链表的第一个公共节点
{
    int m=listLength(L1);
    int n=listLength(L2);
    if(m>n)
    {
        for(int i=1;i<=m-n;i++)
        {
            L1=L1->next;
        }
    }
    else
    {
        for(int i=1;i<=n-m;i++)
        {
            L2=L2->next;
        }
    }
    while(L1!=NULL&&L2!=NULL)
    {
        if(L1==L2)
        {
            printf("第一个公共节点值为:%d\n",L1->data);
            return 1;
        }
        L1=L1->next;
        L2=L2->next;
    }
    printf("两个链表没有公共节点\n");
    return 0;
}
//int main()
//{
//    Node*L1=initNode();
//    Node*L2=initNode();
//    Node*tail1=get_tail(L1);
//    Node*tail2=get_tail(L2);
//    tail1=insertTail(tail1,1);
//    tail1=insertTail(tail1,2);
//    tail1=insertTail(tail1,3);
//    tail1=insertTail(tail1,4);
//    tail2=insertTail(tail2,8);
//    tail2=insertTail(tail2,9);    
//    Node *temp=initNodeWithElem(5);
//    tail1->next=temp;
//    tail2->next=temp;
//    findSameNode(L1,L2);
//    return 0;
//}
/*--------------example3--------------*/
void deleteMidNode1(Node *L)//删除链表中间节点,偶数个时删除靠后的一个
{
    Node *fast=L->next;
    Node *slow=L;
    while(fast!=NULL&&fast->next!=NULL)
    {
        fast=fast->next->next;
        slow=slow->next;
    }
    Node *temp=slow->next;
    slow->next=temp->next;
    free(temp);
}
void deleteMidNode2(Node *L)//删除链表中间节点，偶数个时删除靠前的一个
{
    Node *fast=L->next->next;
    Node *slow=L;
    while(fast!=NULL&&fast->next!=NULL)
    {
        fast=fast->next->next;
        slow=slow->next;
    }
    Node *temp=slow->next;
    slow->next=temp->next;
    free(temp);
}
//int main()
//{
//    Node *L=initNode();
//    Node *tail=get_tail(L);
//    tail=insertTail(tail,1);
//    tail=insertTail(tail,2);
//    tail=insertTail(tail,3);
//    tail=insertTail(tail,4);
//    tail=insertTail(tail,5);
//    tail=insertTail(tail,6);
//    tail=insertTail(tail,7);
//    deleteMidNode2(L);
//    listNode(L);
//    return 0;
//}
/*--------------example4--------------*/
//判断链表是否有环，快慢指针，快指针每次走两步，慢指针每次走一步，
//如果有环，快慢指针一定会相遇，如果没有环，快指针会先走到链表末尾
int is_Cycle(Node *L)
{
    Node *fast=L;
    Node *slow=L;
    while(fast!=NULL&&fast->next!=NULL)
    {
        fast=fast->next->next;
        slow=slow->next;
        if(fast==slow)
        {
            printf("链表有环\n");
            return 1;
        }
    }
    printf("链表无环\n");
    return 0;
}
//判断环的入口节点，快慢指针，快指针每次走两步，慢指针每次走一步，
//如果有环，快慢指针一定会相遇，此时快指针走了2k步，慢指针走了k步，快指针比慢指针多走了k步
//当快慢指针相遇时，让快指针回到链表头部，慢指针继续在原地不动，快慢指针每次都走一步，
//当快慢指针再次相遇时，相遇节点就是环的入口节点
Node *findMeetNode(Node*L)
{
    if(is_Cycle(L))
    {
        Node *fast=L;
        Node *slow=L;
        while(fast!=NULL&&fast->next!=NULL)
        {
            fast=fast->next->next;
            slow=slow->next;
            if(fast==slow)
            {
                fast=L;
                while(fast!=slow)
                {
                    fast=fast->next;
                    slow=slow->next;
                }
                printf("环的入口节点值为:%d\n",fast->data);
                return fast;
            }
        }
    }
    else
    {
        return NULL;
    }
}
/*--------------反转链表--------------*/
Node *reverseList(Node *L)
{
    Node *first=NULL;
    Node *second=L->next;
    Node *third;
    while(second!=NULL)
    {        
        third=second->next;
        second->next=first;
        first=second;
        second=third;
    }
    Node *head=initNode();
    head->next=first;
    return head;
}
int main()
{
    Node *L=initNode();
    Node *tail=get_tail(L);
    tail=insertTail(tail,1);
    tail=insertTail(tail,2);
    tail=insertTail(tail,3);
    tail=insertTail(tail,4);
    tail=insertTail(tail,5);
    Node* p=reverseList(L);
    listNode(p);

    return 0;
}