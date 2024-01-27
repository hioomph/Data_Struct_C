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
            if(i == j)
                g->Edge[i][j] = 0;
            else
                g->Edge[i][j] = MAX_COST;
        }
    }
}

// 打印图
void ShowGraph(GraphMtx *g)
{
    printf("   ");
    for(int i=0; i<g->NumVertices; ++i)
    {
        printf("%2c ", g->VerticesList[i]);

    }
    printf("\n");
    for(int i=0; i<g->NumVertices; ++i)
    {
        printf("%2c ", g->VerticesList[i]);
        for(int j=0; j<g->NumVertices; ++j)
        {
            if(g->Edge[i][j] == MAX_COST)
                printf("%2c ", '@');
            else
                printf("%2d ", g->Edge[i][j]);
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
void InSertEdge(GraphMtx *g, T v1, T v2, E cost)
{
    int p1 = GetVertexPos(g, v1);
    int p2 = GetVertexPos(g, v2);
    if(p1 == -1 || p2 == -1)
        return;
    
    // if(g->Edge[p1][p2] != MAX_COST)  // 注意这一步
    //     return;
    
    // g->Edge[p1][p2] = g->Edge[p2][p1] = cost;
    g->Edge[p1][p2] = cost;
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

// 获取边权值
E GetWeight(GraphMtx *g, int v1, int v2)
{
    if(v1 == -1 || v2 == -1)
        return MAX_COST;
    return g->Edge[v1][v2];
}

// diskstra算法
void ShortestPath(GraphMtx *g, T vertex, E dist[], int path[])
{
    int n = g->NumVertices;  // 记录顶点个数
    bool *S = (bool*)malloc(sizeof(bool)*n);  // 已找到从vertex出发的最短路径的终点的集合
    assert(S != NULL);

    int v = GetVertexPos(g, vertex);  // 得到vertex的下标位置
    for(int i=0; i<n; ++i)
    {
        dist[i] = GetWeight(g, v, i);  // 获取顶点vertex到其余各顶点对应的权值，初始化dist
        S[i] = false;
        if(i != v && dist[i] < MAX_COST)
        {
            path[i] = v;  // 若vertex和顶点i有边（方向为vertex->i），则初始化其起始点为vertex
        }
        else
        {
            path[i] = -1;  // 否则初始化其起始点为-1
        }
    }
    
    S[v] = true;  // 代表顶点vertex已经加入集合
    int min, w;

    for(int i=0; i<n-1; ++i)  // n-1是因为起始点已经定为vertex了
    {
        min = MAX_COST;  // 初始化最小花费为最大代价

        // 在本次循环中找到花费最小的路径<i, j>，并用顶点u记录这个顶点j方便后续处理
        int u = v;
        for(int j=0; j<n; ++j)
        {
            if(!S[j] && dist[j] < min)  // !S[j] --> 未加入集合
            {
                u = j;  // 记录当前顶点
                min = dist[j];
            }
        }

        S[u] = true;  // 加入顶点u

        // 从顶点u出发，更新从u出发到达其他顶点的dist对应的权重
        // 相当于更新dist数组，以便进入下一次循环
        for(int k=0; k<n; ++k)
        {
            w = GetWeight(g, u, k);  // 顶点u到其余顶点的权值
            if(!S[k] && w < MAX_COST && (dist[u]+w)<dist[k])
            {
                dist[k] = dist[u] + w;
                path[k] = u;
            }
        }
    }

    for(int i=0; i<n; ++i)
        printf("%d-->", path[i]);
    printf("Nul.\n");
    for(int i=0; i<n; ++i)
        printf("%d-->", dist[i]);
    printf("Nul.\n");
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