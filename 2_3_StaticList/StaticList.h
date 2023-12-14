#ifndef _STATICLIST_H_
#define _STATICLIST_H_

#include<stdio.h>

#define MAX_SIZE 20
#define ElemType char

typedef struct ListNode
{
    ElemType data;
    int      cur;  // 模拟next指针
}ListNode;

typedef ListNode StaticList[MAX_SIZE];

int Malloc_SL(StaticList &space);
void Free_SL(StaticList &space, int k);

void InitSList(StaticList &space);  // 通过引用传递
void Insert(StaticList &space, ElemType x);
void Delete(StaticList &space);
void ShowSList(StaticList &space);
 

#endif // _STATICLIST_H_