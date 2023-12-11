/*
    顺序表SeqList：
        1）有一个唯一的“第一个数据”；
        1）有一个唯一的“最后一个数据”；
        1）除此之外的其他所有数据都包含一个唯一的前驱和后继。
        
*/

#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define SEQLIST_INIT_SIZE   8
#define INC_SIZE            3  
typedef int ElemType;  // 为避免后续出现类型更改时造成的麻烦，写成这种格式，这样要更改SeqList的数据类型时，只需将int替换成想要的数据格式

typedef struct SeqList
{
    ElemType *base;      
    int       capacity;  // 容量，最大可以容纳的数量
    int       size;      // 大小，当前包含的数量
}SeqList;

bool Inc(SeqList *list);
void InitSeqList(SeqList *list);
void show_list(SeqList *list);
int length(SeqList *list);

void push_back(SeqList *list, ElemType Item);
void push_front(SeqList *list, ElemType Item);
void pop_back(SeqList *list);
void pop_front(SeqList *list);

void insert_pos(SeqList *list, int pos, ElemType val);
void delete_pos(SeqList *list, int pos);
void delete_val(SeqList *list, ElemType key);

int find(SeqList *list, ElemType key);

void sort(SeqList *list);
void reverse(SeqList *list);
void clear(SeqList *list);
void destroy(SeqList *list);

void merge(SeqList *lt, SeqList *la, SeqList *lb);

#endif