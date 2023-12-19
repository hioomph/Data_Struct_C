#include"SeqQueue.h"

int main()
{
    Queue Q;
    InitQueue(&Q);

    ElemType v;

    for(int i=1; i<=8; ++i)
    {
        EnQueue(&Q, i);
    }
    ShowQueue(&Q);
    // DeQueue(&Q);
    // ShowQueue(&Q);
    // printf("Len=%d\n", Length(&Q));
    // GetHead(&Q, &v);
    // printf("队列头：%d\n", v);

    // Clear(&Q);
    // ShowQueue(&Q);
    // printf("Len=%d\n", Length(&Q));

    // Destroy(&Q);

    DeQueue(&Q);
    EnQueue(&Q, 10); 
    ShowQueue(&Q);  // Front:>2 3 4 5 6 7 10 <:Tail. 实际内存中： 2 3 4 5 6 7 10
    DeQueue(&Q);
    EnQueue(&Q, 20);
    ShowQueue(&Q);  // Front:>3 4 5 6 7 10 20 <:Tail. 实际内存中： 20 3 4 5 6 7 10
}