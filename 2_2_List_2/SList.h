#ifndef _SLIST_H_
#define _SLIST_H_

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType int

typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node, *PNode;

typedef struct List
{
    PNode  first;   // List的头结点
    PNode  last;    // List的真实数据的最后一个结点
    size_t size;    // List的长度
}List;

void InitList(List *list);
void show_list(List *list);
int length(List *list);

void push_back(List *list, ElemType x);
void push_front(List *list, ElemType x);
void pop_back(List *list);
void pop_front(List *list);

void insert_val(List *list, ElemType x);
void delete_val(List *list, ElemType key);
Node* find(List *list, ElemType key);

void sort(List *list);
void reverse(List *list);
void clear(List *list);
void destroy(List *list);

///////////////////////////////////////////
typedef Node* It;
Node* _buynode(ElemType x);
It begin(List *list);
It end(List *list);
void insert(List *list, It pos, ElemType x);

#endif // _SLIST_H_