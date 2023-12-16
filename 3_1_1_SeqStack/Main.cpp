#include"SeqStack.h"

int main()
{
    SeqStack st;
    InitStack(&st);

    ElemType v;

    for(int i=1; i<=10; ++i)
    {
        Push(&st, i);
    }
    Show(&st);
    // GetTop(&st, &v);
    // printf("%d 出栈.\n", v);
    // Pop(&st);
    // Show(&st);

    Clear(&st);
    printf("清除后的栈：\n");
    Show(&st);

    Destroy(&st);
    printf("ok\n");
}