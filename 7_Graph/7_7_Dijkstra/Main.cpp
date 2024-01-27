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

    InSertEdge(&gm, 'A', 'B', 10);
    InSertEdge(&gm, 'A', 'D', 30);
    InSertEdge(&gm, 'A', 'E', 100);
    InSertEdge(&gm, 'B', 'C', 50);
    InSertEdge(&gm, 'C', 'E', 10);
    InSertEdge(&gm, 'D', 'C', 20);
    InSertEdge(&gm, 'D', 'E', 60);

    ShowGraph(&gm);

    int n = gm.NumVertices;
    // E *dist = (E*)malloc(sizeof(E)*n);  // 记录到达各个顶点的最短路径的权值
    // int *path = (int*)malloc(sizeof(int)*n);  // 记录最短路径上的各个顶点，path[i]储存和顶点i相连的前一个顶点
    // assert(dist != NULL && path != NULL);
    E dist[5];
    int path[5];

    ShortestPath(&gm, 'A', dist, path);
}