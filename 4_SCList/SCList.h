#ifndef _SCLIST_H_
#define _SCLIST_H_

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
    PNode first;
    PNode last;
    int size;
}List;

Node* _buyNode(ElemType x);

void InitSCList(List *list);
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

#endif // _SCLIST_H_