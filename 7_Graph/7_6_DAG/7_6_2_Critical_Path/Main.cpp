#include"GraphMtx.h"

int main()
{
    GraphMtx gm;
    InitGraphMtx(&gm);
    InSertVertex(&gm, 'A');
    InSertVertex(&gm, 'B');
    InSertVertex(&gm, 'C');
    InSertVertex(&gm, 'D');
    InSertVertex(&gm, 'E');
    InSertVertex(&gm, 'F');
    InSertVertex(&gm, 'G');
    InSertVertex(&gm, 'H');
    InSertVertex(&gm, 'I');

    InSertEdge(&gm, 'A', 'B', 6);
    InSertEdge(&gm, 'A', 'C', 4);
    InSertEdge(&gm, 'A', 'D', 5);
    InSertEdge(&gm, 'B', 'E', 1);
    InSertEdge(&gm, 'C', 'E', 1);
    InSertEdge(&gm, 'D', 'F', 2);
    InSertEdge(&gm, 'E', 'G', 9);
    InSertEdge(&gm, 'E', 'H', 7);
    InSertEdge(&gm, 'F', 'H', 4);
    InSertEdge(&gm, 'G', 'I', 2);
    InSertEdge(&gm, 'H', 'I', 6);
    ShowGraph(&gm);

    CriticalPath(&gm);

    DestroyGraph(&gm);
}