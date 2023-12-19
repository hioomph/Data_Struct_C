#include "DCList.h"

//购置节点
Node* _buyNode(ElemType x)
{
    Node *s = (Node*)malloc(sizeof(Node));
    assert(s != NULL);

    s->data = x;
    s->next = NULL;
    s->prev = NULL;

    return s;
}

// 初始化
void InitDCList(List *list)
{
    Node *s = (Node *)malloc(sizeof(Node));
    assert(s != NULL);

    list->first = list->last = s;
    list->last->next = list->first;
    list->first->prev = list->last;
    list->size = 0;
}

void show_list(List *list)
{
    Node *p = list->first->next;

    while(p != list->first)
    {
        printf("%d-->", p->data);
        p = p->next;
    }

    printf("Nul.\n");
}

int length(List *list)
{
    return list->size;
}

// 尾插
void push_back(List *list, ElemType x)
{
    Node *s = _buyNode(x);

    s->prev = list->last;
    list->last->next = s;
    list->last = s;

    list->last->next = list->first;
    list->first->prev = list->last;
    list->size++;
}

// 头插
void push_front(List *list, ElemType x)
{
    Node *s = _buyNode(x);

    s->next = list->first->next;
    s->prev = list->first;
    list->first->next = s;
    s->next->prev = s;

    if(list->last == list->first)
    {
        list->last = s;
        list->last->next = list->first;
        list->first->prev = list->last;
    }

    list->size++;
}

// 尾删
void pop_back(List *list)
{
    if(list->size == 0)
        return;

    Node *q = list->last;

    list->last = q->prev;
    list->first->prev = list->last;
    list->last->next = list->first;
    free(q);
    list->size--;
}

void pop_front(List *list)
{
    if(list->size == 0)
        return;
    
    Node *q = list->first->next;
    list->first->next = q->next;

    if(q->next == list->first)
    {
        list->last = list->first;
        list->last->next = list->first;
        list->first->prev = list->last;
    }
    else
    {
        q->next->prev = list->first;
    }

    free(q);
    list->size--;
}

// 按值插入
void insert_val(List *list, ElemType x)
{
    Node *p = list->first->next;

    while(p != list->first && p->data < x)
        p = p->next;

    if(p == list->first)
    {
        push_back(list, x);
    }
    else
    {
        Node *s = _buyNode(x);
        s->next = p;
        s->prev = p->prev;
        s->next->prev= s;
        s->prev->next = s;
        list->size++;
    }
}

// 查找
Node* find(List *list, ElemType key)
{
    Node *p = list->first->next;
    while(p != list->first && p->data != key)
        p = p->next;
    
    if(p == list->first)
        return NULL;
    
    return p;
}

// 按值删除
void delete_val(List *list, ElemType key)
{
    if(list->size == 0)
        return;

    Node *p = find(list, key);
    if(p == NULL)
    {
        printf("要删除的数据不存在！\n");
        return;
    }
    else
    {
        if(p->next == list->first)
        {
            pop_back(list);
        }
        else
        {
            p->prev->next = p->next;
            p->next->prev = p->prev;
            free(p);   
            list->size--;
        }
    }
}

void sort(List *list)
{
    if(list->size == 0 || list->size == 1)
        return;

    Node *s = list->first->next;
    Node *q = s->next;

    // 断开链表，此时整个链表断开为仅含一个节点的双向循环链表
    list->last = s;
    s->next = list->first;
    list->first->prev = s;

    while(q != list->first)
    {
        s = q;
        q = q->next;

        Node *p = list->first->next;
        while(p != list->first && p->data < s->data)
            p = p->next;

        if(p == list->first)
        {
            s->prev = list->last;
            list->last->next = s;
            list->last = s;

            list->last->next = list->first;
            list->first->prev = list->last;
        }
        else
        {
            s->next = p;
            s->prev = p->prev;
            s->next->prev= s;
            s->prev->next = s;
        }
    }
}

// 逆置
void reverse(List *list)
{
    if(list->size == 0 || list->size == 1)
        return;

    Node *s = list->first->next;
    Node *q = s->next;

    // 断开链表，此时整个链表断开为仅含一个节点的双向循环链表
    list->last = s;
    s->next = list->first;
    list->first->prev = s;

    while(q != list->first)
    {
        s = q;
        q = q->next;

        s->next = list->first->next;
        s->prev = list->first;
        list->first->next = s;
        s->next->prev = s;
    }
}

void clear(List *list)
{
    Node *q = list->first->next;
    while(q != list->first)
    {
        list->first->next = q->next;
        q->next->prev = list->first;
        free(q);

        q = list->first->next;
    }

    list->last = list->first;
    list->last->next = list->first;
    list->first->prev = list->last;
    list->size = 0;
}

void destroy(List *list)
{
    clear(list);
    free(list->first);
    list->first = list->last = NULL;
}




