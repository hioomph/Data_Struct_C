#include"SeqStack.h"

// 栈空间增加
bool Inc(SeqStack *s)
{
    ElemType *newbase = (ElemType *)realloc(s->base, sizeof(ElemType)*(s->capacity +STACK_INC_SIZE));
    if(newbase == NULL)
    {
        printf("内存不足，无法申请空间！\n");
        return false;
    }

    s->base = newbase;
    s->capacity += STACK_INC_SIZE;
    return true;
}

// 初始化
void InitStack(SeqStack *s)
{
    s->base = (ElemType *)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
    assert(s->base != NULL);
    s->capacity = STACK_INIT_SIZE;
    s->top = 0;
}

// 遍历栈
void Show(SeqStack *s)
{
    for(int i =s->top-1; i>=0; --i)
    {
        printf("%d", s->base[i]);
    }

    printf("\n");
}

// 判满
bool IsFull(SeqStack *s)
{
    return s->top >= s->capacity;
}

// 判空
bool IsEmpty(SeqStack *s)
{
    return s->top == 0;
}

// 栈长度
int Length(SeqStack *s)
{
    return s->top;
}

// 入栈
void Push(SeqStack *s, ElemType x)
{
    // 由于为顺序栈，因此一定要对栈是否满做出判断
    if(IsFull(s) && !Inc(s))
    {
        printf("栈空间已满，%d不能入栈！\n", x);
        return;
    }
    
    // 顺序栈：1）先存值；2）top++；
    s->base[s->top++] = x;
}

// 出栈
void Pop(SeqStack *s)
{
    // 判空
    if(IsEmpty(s))
    {
        printf("栈空间已空，不能出栈！\n");
        return;
    }
    s->top--;
}

// 获取栈顶元素
bool GetTop(SeqStack *s, ElemType *v)
{
    if(IsEmpty(s))
    {
        printf("栈空间已空，不能取栈顶元素！\n");
        return false;
    }

    *v = s->base[s->top-1]; 
    // 错误写法： *v = s->base[--s->top]; 
    // 错误原因：此处仅考虑获取栈顶元素，若--s->top,则对其进行了出栈操作
    return true;
}

// 清除栈
void Clear(SeqStack *s)
{
    s->top = 0;
}

// 摧毁栈
void Destroy(SeqStack *s)
{
    free(s->base);
    s->base = NULL;
    s->capacity = s->top = 0;
}

// 逆序打印栈
void Print(SeqStack *s)
{
    for(int i=0; i<s->top; ++i)
    {
        printf("%c", s->base[i]);
    }
    printf("\n");
}