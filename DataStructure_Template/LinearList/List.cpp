#include<bits/stdc++.h>

// ==================================C-Type=========================================

// 创建线性表 结构体法 长度为20 数据类型为int
#define MAXSIZE 20
typedef int ElemType;

typedef struct{
    ElemType data[MAXSIZE];
    int length;
} Sqlist;


//获得元素操作
#define OK 1
#define ERROR 0
typedef int Status;

Status GetElem(Sqlist L,int i,ElemType *e){
    if(L.length==0||i<1||i>L.length)
        return ERROR;
    *e = L.data[i - 1];
        return OK;
}

//插入元素操作
Status ListInsert(Sqlist *L,int i,ElemType e){
    int k;
    if(L->length==MAXSIZE)
        return ERROR;
    if(i<1||i>L->length+1)
        return ERROR;
    
    if(i<=L->length){
        for (int k = L->length - 1; k >= i - 1;k--){
            L->data[k + 1] = L->data[k];
        }
    }
    L->data[i - 1] = e;
    L->length++;
    return OK;
}

//删除元素操作
Status ListInsert(Sqlist *L, int i, ElemType *e)
{
    int k;
    if (L->length == 0)
        return ERROR;
    if (i < 1 || i > L->length)
        return ERROR;

    *e = L->data[i - 1];
    if (i <= L->length)
    {
        for (int k = i; k < L->length; k++)
        {
            L->data[k-1] = L->data[k];
        }
    }
    L->length--;
    return OK;
}





