#include"LinkStack.h"

// 初始化
void InitStack(LinkStack *s)
{
    *s = NULL;
}

// 遍历
void Show(LinkStack *s)
{
    StackNode *p = *s;
    while(p != NULL)
    {
        printf("%d\n", p->data);
        p = p->next;
    }

    printf("\n");
}

// 入栈：申请一个节点，进行头插
void Push(LinkStack *s, ElemType x)
{
    // 申请一个节点
    StackNode *t = (StackNode*)malloc(sizeof(StackNode));
    assert(t != NULL);
    t->data = x;

    // 头插
    if(*s == NULL)  // 若栈为空，则直接让头指针指向新节点
    {
        *s = t;
        t->next = NULL;
    }
    else  // 若栈非空，则在原头节点前插入t，使得t成为新的头节点
    {
        t->next = *s;
        *s = t;
    }
}

// 出栈
void Pop(LinkStack *s)
{
    StackNode *p = *s;
    *s = p->next;
    free(p);
    p = NULL;
}

// 获取栈顶元素
bool GetTop(LinkStack *s, ElemType *v)
{
    if(*s == NULL)
    {
        printf("栈空间已空，不能取栈顶元素！\n");
        return false;
    }

    *v = (*s)->data;
    return true;
}

// 清空栈
void Clear(LinkStack *s)
{
    StackNode *p = *s;
    /*
    LinkStack被定义为StackNode*，而s是LinkStack*类型，也就是StackNode**类型。
    因此：
        s   指向指针的指针
        *s  指向StackNode*的指针

    free(s);
        释放指向栈的指针的内存，但不会释放栈中的节点内存。
        这可能导致内存泄漏，因为栈中的节点内存并没有被释放。

    free(*s);
        这样会释放指向栈顶节点的指针的内存，并同时释放栈中的节点内存。
        这是正确的方式，因为它会释放整个栈的内存，包括节点和指向节点的指针。
    */
    while(*s != NULL)
    {
        *s = p->next;
        free(p);
        p = *s;
    }
}

// 销毁栈
void Destroy(LinkStack *s)
{
    Clear(s);
    free(*s);  // 若free(s); 错误，因为s是传值的参数
}