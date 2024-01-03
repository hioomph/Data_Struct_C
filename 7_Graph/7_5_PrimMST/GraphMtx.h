#ifndef _GRAPHMTX_H_
#define _GRAPHMTX_H_

#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include<stdlib.h>
#include<search.h>

#define Default_Vertex_Size 10  // 默认顶点数大小
#define T char
#define E int  // 权值类型
#define MAX_COST 0X7FFFFFF

typedef struct GraphMtx
{
    int   MaxVertices;    // 最大顶点数，即容量
    int   NumVertices;    // 当前顶点数，即真实大小
    int   NumEdges;       // 当前边数

    T    *VerticesList;   // 顶点列表
    int **Edge;           // 指向邻接矩阵，二维数组
    // 一维数组：指向每一行，即每个顶点和其他顶点的边的连接
    // 二维数组：指向每一列，即当前图包含的所有顶点

}GraphMtx;

void InitGraphMtx(GraphMtx *g);
void ShowGraph(GraphMtx *g);

int GetVertexPos(GraphMtx *g, T v);
void InSertVertex(GraphMtx *g, T v);
void InSertEdge(GraphMtx *g, T v1, T v2, E cost);
void RemoveVertex(GraphMtx *g, T v);
void RemoveEdge(GraphMtx *g, T v1, T v2);

int GetFirstNeighbor(GraphMtx *g, T v);
int GetNextNeighbor(GraphMtx *g, T v, T w);

void DestroyGraph(GraphMtx *g);

E GetWeight(GraphMtx *g, int v1, int v2);
void MinSpanTree_Prim(GraphMtx *g, T vertex);

///////////////////////////////////////////////////
// Kruskal

typedef struct Edge
{
    int x;  // start 
    int y;  // end
    E   cost;
}Edge;

int cmp(const void *a, const void *b);
bool Is_Same(int *father, int i, int j);
void Mark_Same(int *father, int i, int j);
void MinSpanTree_Kruskal(GraphMtx *g);

#endif // _GRAPHMTX_H_