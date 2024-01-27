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

    InSertEdge(&gm, 'A', 'B', 6);
    InSertEdge(&gm, 'A', 'C', 1);
    InSertEdge(&gm, 'A', 'D', 5);
    InSertEdge(&gm, 'B', 'C', 5);
    InSertEdge(&gm, 'B', 'E', 3);
    InSertEdge(&gm, 'C', 'D', 5);
    InSertEdge(&gm, 'C', 'E', 6);
    InSertEdge(&gm, 'C', 'F', 4);
    InSertEdge(&gm, 'D', 'F', 2);
    InSertEdge(&gm, 'E', 'F', 6);
    ShowGraph(&gm);
    /*
        插入顶点间的边后，得到：
          A B C D E F 
        A 0 6 1 5 @ @ 
        B 6 0 5 @ 3 @ 
        C 1 5 0 5 6 4 
        D 5 @ 5 0 @ 2 
        E @ 3 6 @ 0 6 
        F @ @ 4 2 6 0  
    */

    MinSpanTree_Prim(&gm, 'A');
    /*
        A-->C : 1
        C-->F : 4
        F-->D : 2
        C-->B : 5
        B-->E : 3
    */
}