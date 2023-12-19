#include"LinkQueue.h"

int main()
{
    LinkQueue Q;
    InitQueue(&Q);

    for(int i=1; i<=10; ++i)
    {
        EnQueue(&Q, i);
    }
    ShowQueue(&Q);
    DeQueue(&Q);
    ShowQueue(&Q);
    printf("Len=%d\n", Length(&Q));

    Clear(&Q);
    ShowQueue(&Q);
    printf("Len=%d\n", Length(&Q));

    Destroy(&Q);
}