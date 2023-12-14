#include "DList.h"

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
void InitDList(List *list)
{
    Node *s = (Node*)malloc(sizeof(Node));
    assert(s != NULL);

    list->first = list->last = s;
    list->last->next = NULL;
    list->first->prev = NULL;
    list->size = 0;
}

void show_list(List *list)
{
    Node *p = list->first->next;
    while(p != NULL)
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
    list->size++;
}

// 头插
void push_front(List *list, ElemType x)
{
    Node *s = _buyNode(x);

    if(list->first == list->last)
        list->last = s;
    else
    {
        s->next = list->first->next;
        s->next->prev = s;
    }

    s->prev = list->first;
    list->first->next = s;

    list->size++;
}

// 尾删
void pop_back(List *list)
{
    if(list->size == 0)
        return;
        
    Node *q = list->last;
    list->last = list->last->prev;
    list->last->next = NULL;
    free(q);
    list->size--;
}

// 头删
void pop_front(List *list)
{
    if(list->size == 0)
        return;
    
    Node *q = list->first->next;
    if(list->first->next == list->last)  // if(q->next->next == NULL)
    {
        list->last = list->first;
        list->last->next = NULL;
    }
    else
    {
        q->next->prev = list->first;
        list->first->next = q->next;
    }

    free(q);
    list->size--;
}

// 按值插入
void insert_val(List *list, ElemType x)
{
    
    
    Node *p = list->first->next;
    while(p != NULL && p->next->data < x)
        p = p->next;
    
    if(p == NULL)
    {
        push_back(list, x);
    }
    else
    {
        Node *s = _buyNode(x);
        s->next = p->next;
        s->prev = p;
        s->next->prev = s;
        s->prev->next = s;
    }

    list->size++;
}

// 按值删除
void delete_val(List *list, ElemType key)
{
    Node *p = find(list, key);
    
    if(p == NULL)
    {
        printf("要删除的数据不存在！\n");
        return;
    }
    else
    {
        if(p->next == NULL)
        {
            list->last = list->last->prev;
            list->last->next = NULL;
        }
        else
        {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        free(p);
        list->size--;
    }
}

// 查找
Node* find(List *list, ElemType key)
{
    Node *p = list->first->next;
    while(p != NULL && p->data != key)
        p = p->next;
    
    return p;
}

// 排序
void sort(List *list)
{
    if(list->size == 0 || list->size == 1)
        return;

    Node *s = list->first->next;
    Node *q = s->next;

    // 断开链表，此时整个链表断开为仅含一个节点的双向链表
    list->last = s;
    s->next = NULL;

    while(q != NULL)
    {
        s = q;
        q = q->next;

        Node *p = list->first->next;
        while(p != NULL && s->data > p->data)
            p = p->next;
        
        if(p == NULL)
        {
            s->prev = list->last;
            list->last->next = s;
            s->next = NULL;
            list->last = s;
        }
        else
        {
            s->next = p;
            s->prev = p->prev;
            p->prev = s;
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

    // 断开链表，此时整个链表断开为仅含一个节点的双向链表
    list->last = s;
    s->next = NULL;

    while(q != NULL)
    {
        s = q;
        q = q->next;

        s->next = list->first->next;
        s->next->prev = s;
        s->prev = list->first;
        list->first->next = s;
    }
}

void clear(List *list)
{
    Node *p = list->first->next;
    while(p != NULL)
    {
        list->first->next = p->next;
        free(p);
        p = list->first->next;
    }

    list->last = list->first;
    list->last->next = NULL;
    list->size = 0;
}

void destroy(List *list)
{
    clear(list);
    free(list->first);
    list->first = list->last = NULL;
}
