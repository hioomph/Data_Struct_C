#include "SList.h"

// 新建单链表List
void InitList(List *list)
{
    list->first = list->last = (Node*)malloc(sizeof(Node)); // 初始化时没有其余节点，因此first和last均指向头结点
    assert(list->first != NULL && list->last != NULL);

    list->first->next = NULL;
    list->size = 0;
}

// 显示List
void show_list(List *list)
{
    Node *p = list->first->next;  // 指向List的第一个有效节点
    while(p != NULL)
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

// 尾部插入
/*
void push_back(List *list, ElemType x)
{
    // Node *s = (Node *)malloc(sizeof(Node));
    // assert(s != NULL);
    // s->data = x;
    // s->next = NULL;    
    Node *s = _buynode(x);

    list->last->next = s;
    list->last = s;
    list->size++;
}
*/
void push_back(List *list, ElemType x)
{
    insert(list, end(list), x);
}

// 头部插入
/*
void push_front(List *list, ElemType x)
{
    // Node *s = (Node *)malloc(sizeof(Node));
    // assert(s != NULL);
    // s->data = x;
    // s->next = NULL;    
    Node *s = _buynode(x);

    list->first->next = s;
    // 这里要注意：当list中本身就存在数据时，不用管list->last，因为它仍然指向最后一个结点；
    // 但是当list本身为空时，first与last实际上都指向头结点，那么插入一个数据后，需要对last进行修改。
    if(list->size == 0)
        list->last = s; // 当list为空时，对last进行移动
    list->size++;
}
*/
void push_front(List *list, ElemType x)
{
    insert(list, begin(list), x);
}

// 尾部删除
void pop_back(List *list)
{
    if(list->size == 0)
        return;
    Node *p = list->first;
    while(p->next != list->last) // 如果p->next指向last，说明p当前指向倒数第二个结点
        p = p->next;

    free(list->last);
    list->last = p;
    list->last->next = NULL;
    list->size--;
}

// 头部删除
void pop_front(List *list)
{
    if(list->size == 0)
        return;

    Node *p = list->first->next;
    list->first->next = list->first->next->next;
    free(p);
    if(list->size == 1)
        list->last = list->first;
    list->size--;
}

// 升序按值插入
void insert_val(List *list, ElemType x)
{
    // Node *s = (Node *)malloc(sizeof(Node));
    // assert(s != NULL);
    // s->data = x;
    // s->next = NULL;
    Node *s = _buynode(x);

    Node *p = list->first;
    while(p->next !=  NULL && p->next->data < x)
        p = p->next;
    
    s->next = p->next;
    p->next = s;
    if(s->next == NULL)
        list->last = s;
    list->size++;
}

// 按值删除
void delete_val(List *list, ElemType key)
{
    // 先查找是否存在该值
    if(list->size == 0)
        return;
    Node *p = find(list, key);
    if(p == NULL)
    {
        printf("要删除的数据不存在！\n");
        return;
    }

    // 方法1：遍历list，找到要删除节点p的前驱节点
    // Node *s = list->first;
    // while(s->next != NULL && s->next != p)
    //     s = s->next;
    // if(s->next == NULL)
    //     list->last = p->next;
    // s->next = p->next;
    // free(p);

    // 方法2：将要删除节点p的下一个节点q的值拷贝给p，然后让p指向q的下一个节点并释放q
    Node *q = p->next;
    p->data = q->data;
    p->next = q->next;
    if(q->next == NULL)
        list->last = p;
    free(q);
    list->size--;
}
 
// 查找数据
Node* find(List *list, ElemType key)
{
    Node *p = list->first->next;
    // while(p->data != key && p != NULL)  这两者的顺序不能颠倒
    while(p != NULL && p->data != key)
        p = p->next;
    
    return p;
}

// 排序
// 方法：将单链表按第一个节点和剩余的节点断开为list1和list2，然后从剩余的节点中依次取节点，按值插入list1中
void sort(List *list)
{
    if(list->size == 0 || list->size == 1)
        return;
    
    Node *s = list->first->next;
    Node *q = s->next;

    // 将链表断开
    list->last = s;
    list->last->next = NULL;

    while(q != NULL)
    {
        // 获取q的第一个节点，并使其与q的后续节点断开，可以插入回list中
        s = q;
        q = q->next;

        Node *p = list->first;
        while(p->next !=  NULL && p->next->data < s->data)
            p = p->next;
        
        s->next = p->next;
        p->next = s;
        if(s->next ==NULL)
            list->last = s;
        list->size++;
    }
}

// 逆置
void reverse(List *list)
{
    if(list->size == 0 || list->size == 1)
        return;  

    Node *s = list->first->next;
    Node *q = s->next;

    // 将链表断开
    list->last = s;
    list->last->next = NULL;

    while(q != NULL)
    {
        // 获取q的第一个节点，并使其与q的后续节点断开，并依次头插
        s = q;
        q = q->next;

        s->next = list->first->next;
        list->first->next = s;        
    }
}

// 清除链表（保留头节点）
void clear(List *list)
{
    if(list->size == 0)
        return;  

    Node *p = list->first->next;
    while(p != NULL)
    {
        // 进行头部删除
        list->first->next = p->next;
        free(p);
        p = list->first->next;
    }

    list->last = list->first;
    list->size = 0;
}

// 删除链表
void destroy(List *list)
{
    clear(list);
    free(list->first);
    list->first = list->last = NULL;
}

//////////////////////////////////
Node* _buynode(ElemType x)
{
    Node *s = (Node *)malloc(sizeof(Node));
    assert(s != NULL);
    s->data = x;
    s->next = NULL;
    
    return s;
}

It begin(List *list)
{
    return list->first->next;
}

It end(List *list)
{
    return list->last->next;
}

void insert(List *list, It pos, ElemType x)
{
    Node *p = list->first;
    while(p->next != pos)
        p = p->next;
    
    Node *s = _buynode(x);
    s->next = p->next;
    p->next = s;
    if(pos == NULL)
        list->last = s;

    list->size++;
}