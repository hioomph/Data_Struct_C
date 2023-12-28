#ifndef _GRAPHLINK_H_
#define _GRAPHLINK_H_

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define Dafault_Vertex_Size 10
#define T char

// 边结构。1）保存顶点的位置信息；2）指向下一个顶点的位置信息
typedef struct Edge
{
    int dest;
    struct Edge *link;
}Edge;

// 顶点结构。包含1）顶点的信息；2）指向的边的信息。
typedef struct Vertex
{
    T data;
    Edge *adj;
}Vertex;

typedef struct GraphLink
{
    int MaxVertices;
    int NumVertices;
    int NumEdges;

    Vertex *NodeTable;  // 存放顶点的“List”
}GraphLink;

void InitGraph(GraphLink *g);
void ShowGraph(GraphLink *g);

int GetVertexPos(GraphLink *g, T v);
T   GetVertexValue(GraphLink *g, int v);

void InsertVertex(GraphLink *g, T v);
void InsertEdge(GraphLink *g, T vertex1, T vertex2);
void RemoveVertex(GraphLink *g, T v);
void RemoveEdge(GraphLink *g, T vertex1, T vertex2);
void DestroyGraph(GraphLink *g);

int GetFirstNeighbor(GraphLink *g, T v);
int GetNextNeighbor(GraphLink *g, T vertex1, T vertex2);

/////////////////////////////////////////////////////////////

void DFS(GraphLink *g, T vertex);
void DFS(GraphLink *g, int v, bool visited[]);
void BFS(GraphLink *g, T vertex);

#endif // _GRAPHLINK_H_