#include "SCList.h"

Node* _buyNode(ElemType x)
{
    Node *s = (Node *)malloc(sizeof(Node));
    assert(s != NULL);
    s->data = x;
    s->next = NULL;

    return s;
}

void InitSCList(List *list)
{
    Node *s = (Node *)malloc(sizeof(Node));
    assert(s != NULL);

    list->first = list->last = s;
    list->last->next = list->first;
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

// 链表长度
int length(List *list)
{
    return list->size;
}

// 尾插
void push_back(List *list, ElemType x)
{
    Node *s = _buyNode(x);
    list->last->next = s;
    list->last = s;
    list->last->next = list->first;
    list->size++;
}

// 头插
void push_front(List *list, ElemType x)
{
    Node *s = _buyNode(x);
    s->next = list->first->next;
    list->first->next = s;
    if(s->next == list->first) // if(list->first == list->last)
        list->last = s;
    list->size++;
}

// 尾删
void pop_back(List *list)
{
    if(list->size == 0)
        return;

    Node *p = list->first;
    while(p->next != list->last)
        p = p->next;

    free(list->last);
    list->last = p;
    list->last->next = list->first;
    list->size--;
}

// 头删
void pop_front(List *list)
{
    if(list->size == 0)
        return;
    
    Node *p = list->first->next;
    list->first->next = p->next;
    free(p);
    if(list->first->next == list->first)
        list->last = list->first;
    list->size--;
}

// 按值插入
void insert_val(List *list, ElemType x)
{
    Node *s = _buyNode(x);

    Node *p = list->first;
    while(p->next != list->first && x > p->next->data)
        p = p->next;
    
    if(p->next == list->first)
        list->last = s;
    s->next = p->next;
    p->next = s;
    list->size++;
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
    
    if(p == list->last)
        pop_back(list);
    else
    {
        Node *q = p->next;
        p->data = q->data;
        p->next = q->next;
        free(q);
        list->size--;
    }
}

// 查找
Node* find(List *list, ElemType key)
{
    if(list->size == 0)
        return NULL;

    Node *p = list->first;
    while(p->next != list->first && p->next->data != key)
        p = p->next;

    if(p->next == list->first)
        return NULL;
    else
        return p;
}

// 排序
void sort(List *list)
{
    if(list->size == 0 || list->size == 1)
        return;
    
    Node *s = list->first->next;
    Node *q = s->next;

    // 断开链表，此时整个链表断开为仅含一个节点的单循环链表
    list->last->next = NULL;  // 去除原尾节点的循环
    list->last = s;     // 更改原last指针
    list->last->next = list->first;  // 实现新的循环

    while(q != NULL)
    {
        s = q;
        q = q->next;

        Node *p = list->first;
        while(p->next != list->first && s->data > p->next->data)
            p = p->next;
        
        if(p->next == list->first)
            list->last = s;

        s->next = p->next;
        p->next = s;
    }
}

// 逆置
void reverse(List *list)
{
    if(list->size == 0 || list->size == 1)
        return;
    
    Node *p = list->first->next;
    Node *q = p->next;

    // 断开链表，此时整个链表断开为仅含一个节点的单循环链表
    list->last->next = NULL;  // 去除原尾节点的循环
    list->last = p;     // 更改原last指针
    list->last->next = list->first;  // 实现新的循环

    while(q != NULL)
    {
        p = q;
        q = q->next;

        p->next = list->first->next;
        list->first->next = p;
    }
}

void clear(List *list)
{
    // 依次头部删除
    Node *p = list->first->next;
    while(p != list->first)
    {
        list->first->next = p->next;
        free(p);
        p = list->first->next;
    }

    list->last = list->first;
    list->last->next = list->first;
    list->size = 0;
}

void destroy(List *list)
{
    clear(list);
    free(list->first);
    list->first = list->last = NULL;
}
