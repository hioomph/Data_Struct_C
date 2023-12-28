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
    InsertVertex(&gl, 'F');
    InsertVertex(&gl, 'G');
    InsertVertex(&gl, 'H');

    InsertEdge(&gl, 'A', 'B');
    InsertEdge(&gl, 'A', 'C');
    InsertEdge(&gl, 'B', 'D');
    InsertEdge(&gl, 'B', 'E');
    InsertEdge(&gl, 'C', 'F');
    InsertEdge(&gl, 'C', 'G');
    InsertEdge(&gl, 'D', 'H');
    InsertEdge(&gl, 'E', 'H');
    InsertEdge(&gl, 'F', 'G');
    ShowGraph(&gl);

    DFS(&gl, 'A');
    printf("Nul.\n");

    BFS(&gl, 'A');
    printf("Nul.\n");
    
    DestroyGraph(&gl);
}
