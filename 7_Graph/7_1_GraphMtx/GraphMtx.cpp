#include"GraphMtx.h"

// 初始化
void InitGraphMtx(GraphMtx *g)
{
    g->MaxVertices = Default_Vertex_Size;
    g->NumVertices = 0;
    g->NumEdges = 0;

    g->VerticesList = (T*)malloc(sizeof(T) * (g->MaxVertices));

    // 二维数组开辟空间，每一行都是一个单独的数组，而g->Edge则是指向这些行的指针数组
    // g->Edge => (10, 10)的二维矩阵
    g->Edge = (int**)malloc(sizeof(int *) * g->MaxVertices);
    assert(g->Edge != NULL);
    for(int i=0; i<g->MaxVertices; ++i)
    {
        g->Edge[i] = (int*)malloc(sizeof(int) * g->MaxVertices);
    }
    for(int i=0; i<g->MaxVertices; ++i)
    {
        for(int j=0; j<g->MaxVertices; ++j)
        {
            g->Edge[i][j] = 0;
        }
    }
}

// 打印图
void ShowGraph(GraphMtx *g)
{
    printf("  ");
    for(int i=0; i<g->NumVertices; ++i)
    {
        printf("%c ", g->VerticesList[i]);

    }
    printf("\n");
    for(int i=0; i<g->NumVertices; ++i)
    {
        printf("%c ", g->VerticesList[i]);
        for(int j=0; j<g->NumVertices; ++j)
        {
            printf("%d ", g->Edge[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 获取顶点位置
int GetVertexPos(GraphMtx *g, T v)
{
    for(int i=0; i<g->NumVertices; ++i)
    {
        if(g->VerticesList[i] == v)
            return i;
    }
    return -1;
}

// 插入顶点
void InSertVertex(GraphMtx *g, T v)
{
    // 首先判断图是否已满
    if(g->NumVertices >= g->MaxVertices)
        return;
    
    g->VerticesList[g->NumVertices++] = v;
}

// 插入边
void InSertEdge(GraphMtx *g, T v1, T v2)
{
    int p1 = GetVertexPos(g, v1);
    int p2 = GetVertexPos(g, v2);
    if(p1 == -1 || p2 == -1)
        return;
    
    if(g->Edge[p1][p2] != 0)  // 注意这一步
        return;
    
    g->Edge[p1][p2] = g->Edge[p2][p1] = 1;
    g->NumEdges++;
}

// 删除顶点（包括删除顶点和删除顶点关联的边两步）
void RemoveVertex(GraphMtx *g, T v)
{
    int p = GetVertexPos(g, v);
    if(p == -1)
        return;

    int numEdges = 0;
    
    // 删除顶点
    for(int i=p; i<g->NumVertices-1; ++i)
    {
        g->VerticesList[i] = g->VerticesList[i+1];
    }

    for(int i=0; i<g->NumVertices; ++i)
    {
        if(g->Edge[p][i] != 0)
        {
            numEdges++;
        }
    }
    // 删除顶点关联的边（删除Edge矩阵中和该顶点相关的行和列）
    // 对行重新赋值
    for(int i=p; i<g->NumVertices-1; ++i)
    {
        for(int j=0; j<g->NumVertices; ++j)
        {
            g->Edge[i][j] = g->Edge[i+1][j];
        }
    }

    // 对列重新赋值
    for(int i=p; i<g->NumVertices-1; ++i)
    {
        for(int j=0; j<g->NumVertices; ++j)
        {
            g->Edge[j][i] = g->Edge[j][i+1];
        }
    }

    g->NumVertices--;
    g->NumEdges -= numEdges;
}

// 删除边
void RemoveEdge(GraphMtx *g, T v1, T v2)
{
    int p1 = GetVertexPos(g, v1);
    int p2 = GetVertexPos(g, v2);
    if(p1 == -1 || p2 == -1)
        return;
    
    if(g->Edge[p1][p2] == 0)  // 注意这一步
        return;
    
    g->Edge[p1][p2] = g->Edge[p2][p1] = 0;
    g->NumEdges--;
}

// 获取第一个邻接点
int GetFirstNeighbor(GraphMtx *g, T v)
{
    int p = GetVertexPos(g, v);
    if(p == -1)
        return -1;
    
    for(int i=0; i<g->NumVertices; ++i)
    {
        if(g->Edge[p][i] == 1)
            return i;
    }
    return -1;
}

// 获取下一个邻接点（在图g中查找v的邻接点w的下一个邻接点）
int GetNextNeighbor(GraphMtx *g, T v, T w)
{
    int pv = GetVertexPos(g, v);
    int pw = GetVertexPos(g, w);
    if(pv == -1 || pw == -1)
        return -1;
    
    for(int i=pw+1; i<g->NumVertices; ++i)
    {
        if(g->Edge[pv][i] == 1)
            return i;
    }
    return -1;
}

// 释放图
void DestroyGraph(GraphMtx *g)
{
    free(g->VerticesList);
    g->VerticesList = NULL;

    // 先释放一级指针，再释放二级指针
    for(int i=0; i<g->NumVertices; ++i)
    {
        free(g->Edge[i]);
    }
    free(g->Edge);
    g->Edge = NULL;

    g->MaxVertices = g->NumVertices = g->NumEdges = 0;
}