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
    ShowGraph(&gm);
    /*
        插入五个顶点后，得到：
          A B C D E 
        A 0 0 0 0 0 
        B 0 0 0 0 0 
        C 0 0 0 0 0 
        D 0 0 0 0 0 
        E 0 0 0 0 0 
        此时未给出各顶点之间的邻接关系，因此打印出的图全为0
    */

    InSertEdge(&gm, 'A', 'B');
    InSertEdge(&gm, 'A', 'D');
    InSertEdge(&gm, 'B', 'C');
    InSertEdge(&gm, 'B', 'E');
    InSertEdge(&gm, 'C', 'D');
    InSertEdge(&gm, 'C', 'E');
    ShowGraph(&gm);
    /*
        插入顶点间的边后，得到：
          A B C D E 
        A 0 1 0 1 0 
        B 1 0 1 0 1 
        C 0 1 0 1 1 
        D 1 0 1 0 0 
        E 0 1 1 0 0  
    */

    // RemoveEdge(&gm, 'B', 'C');
    // ShowGraph(&gm);

    // RemoveVertex(&gm, 'C');
    // ShowGraph(&gm);

    int p = GetFirstNeighbor(&gm, 'A');
    printf("A的第一个邻接点为：%c\n", gm.VerticesList[p]);

    int m = GetNextNeighbor(&gm, 'C', 'B');
    printf("C的第一个邻接点B的下一个邻接点为：%c\n", gm.VerticesList[m]);

    DestroyGraph(&gm);
    ShowGraph(&gm);
}