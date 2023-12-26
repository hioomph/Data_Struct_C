#include"GraphLink.h"

int main()
{
    GraphLink gl;
    InitGraph(&gl);

    InsertVertex(&gl, 'A');
    InsertVertex(&gl, 'B');
    InsertVertex(&gl, 'C');
    InsertVertex(&gl, 'D');
    InsertVertex(&gl, 'E');

    InsertEdge(&gl, 'A', 'B');
    InsertEdge(&gl, 'A', 'D');
    InsertEdge(&gl, 'B', 'C');
    InsertEdge(&gl, 'B', 'E');
    InsertEdge(&gl, 'C', 'D');
    InsertEdge(&gl, 'C', 'E');
    ShowGraph(&gl);

    // RemoveEdge(&gl, 'B', 'C');
    // RemoveVertex(&gl, 'C');
    // ShowGraph(&gl);

    int p = GetFirstNeighbor(&gl, 'A');
    printf("A的第一个邻接点为：%c\n", gl.NodeTable[p].data);

    int m = GetNextNeighbor(&gl, 'B', 'E');
    printf("B的第一个邻接点E的下一个邻接点为：%c\n", gl.NodeTable[m].data);

    DestroyGraph(&gl);

}