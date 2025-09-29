#include <bits/stdc++.h>
#define ElemType int
#define Status int
// 单链表Linklist

// 创建单链表动态
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;
typedef struct Node *LinkList;

// 获得元素

#define OK 1
#define ERROR 0

Status GetElem(LinkList L, int i, ElemType *e)
{
    int j;
    LinkList p;
    p = L->next;
    j = 1;
    while (p && j < i)
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR;
    *e = p->data;
    return OK;
}

// 插入元素
Status ListInsert(LinkList *L, int i, ElemType e)
{
    int j = 1;
    LinkList p, s;
    p = *L;
    while (p && j < i)
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR;

    s = (LinkList)malloc(sizeof(Node));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

// 删除元素
Status ListDelete(LinkList *L, int i, ElemType *e)
{
    int j = 1;
    LinkList p, q;
    p = *L;
    while (p->next && j < i)
    {
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i)
    {
        return ERROR;
    }
    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}

// 整表创建
void CreateListHead(LinkList *L, int n)
{
    LinkList p;
    int i;
    srand(time(0));
    // HeadNode
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    for (i = 0; i < n; i++)
    {
        p = (LinkList)malloc(sizeof(Node));
        p->data = rand() % 100 + 1;
        p->next = (*L)->next;
        (*L)->next = p;
    }
}

void CreateListTail(LinkList *L, int n)
{
    LinkList p, r;
    int i;
    srand(time(0));
    *L = (LinkList)malloc(sizeof(Node));
    r = *L;
    for (int i = 0; i < n; i++)
    {
        p = (Node *)malloc(sizeof(Node));
        p->data = rand() % 100 + 1;
        r->next = p;
        r = p;
    }
    r->next = NULL;
}

Status ClearList(LinkList *L)
{
    LinkList p, q;
    p = (*L)->next;
    while (p)
    {
        q = p->next;
        free(q);
        p = q;
    }
    (*L)->next = NULL;
    return OK;
}