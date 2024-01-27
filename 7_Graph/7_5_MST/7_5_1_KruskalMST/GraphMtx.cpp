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
            if(g->Edge[i][j] == MAX_COST)
                printf("%c ", '@');
            else
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
void InSertEdge(GraphMtx *g, T v1, T v2, E cost)
{
    int p1 = GetVertexPos(g, v1);
    int p2 = GetVertexPos(g, v2);
    if(p1 == -1 || p2 == -1)
        return;
    
    // if(g->Edge[p1][p2] != MAX_COST)  // 注意这一步
    //     return;
    
    g->Edge[p1][p2] = g->Edge[p2][p1] = cost;
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

// 获取边权值
E GetWeight(GraphMtx *g, int v1, int v2)
{
    if(v1 == -1 || v2 == -1)
        return MAX_COST;
    return g->Edge[v1][v2];
}

// 最小生成树_Prim算法
void MinSpanTree_Prim(GraphMtx *g, T vertex)
{
    int n = g->NumVertices;  // 计算顶点个数
    E *lowcost = (E*)malloc(sizeof(E)*n);  // lowcost[n]，最小花费的数组
    int *mst = (int*)malloc(sizeof(int)*n);  // mst[n]，最小花费的起始顶点的数组
    assert(lowcost != NULL && mst != NULL);

    // 1、初始化lowcost
    int k = GetVertexPos(g, vertex);  // 获取vertex的位置，作为初始的起始顶点
    for(int i=0; i<n; ++i)
    {
        if(i != k)
        {
            lowcost[i] = GetWeight(g, k, i);  // 获取从k到i的边的权重，lowcost[i]中i为终点顶点
            mst[i] = k;
        }
        else
        {
            lowcost[i] = 0;  // lowcost[i]=0 ==> 顶点i属于MST的顶点集合
        }
    }

    // 2、从初始起始顶点出发，寻找最小代价的边值
    int min, min_index;
    int begin, end;
    E cost;

    // 遍历找到需要的n-1条边
    for(int i=0; i<n-1; ++i)  // n-1 ==> n个顶点最多n-1条边
    {
        min = MAX_COST;
        min_index = -1;

        // （1）经过n次遍历，找到从vertex出发的一条权值最小的路径
        for(int j=0; j<n; ++j)
        {
            if(lowcost[j] != 0 && lowcost[j]<min)  
            {
                // lowcost[j] != 0 ==> 说明顶点j还未加入MST的顶点集合
                min = lowcost[j];
                min_index = j;
            }
        }

        begin = mst[min_index];
        end = min_index;
        printf("%c-->%c : %d\n", g->VerticesList[begin], g->VerticesList[end], min);
        
        lowcost[min_index] = 0;  // 将minx_index所代表的顶点加入MST顶点集合中，后续不再进行考虑

        // （2）加入新顶点后，更新此时的lowcost和mst数组
        for(int j=0; j<n; ++j)
        {
            cost = GetWeight(g, min_index, j);
            if(cost < lowcost[j])
            {
                lowcost[j] = cost;  // 顶点j到min_index对应顶点的权值比到之前保存的权值更小，因此更新权值
                mst[j] = min_index;  // 更新此时顶点j所对应的起始顶点为min_index对应顶点
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Kruskal

int cmp(const void *a, const void *b)
{
    return ((*(Edge*)a).cost - (*(Edge*)b).cost);
}

// 判断i和j是否处于同一连通子图
bool Is_Same(int *father, int i, int j)
{
    // 从当前节点i开始层层追踪，直到找到其最后的父节点
    // father[i]==i说明i自己是一个单独的存在，没有和它连通的顶点
    while(father[i] != i)
    {
        // 否则，找到和它连通的顶点，并且层层寻找，直到找到最后一个不和其他顶点相连的顶点
        // 这样就追溯到了他的根节点
        i = father[i];
    }

    while(father[j] != j)
    {
        j = father[j];
    }

    return i==j;
}

// 将i和j标记为相同集合
void Mark_Same(int *father, int i, int j)
{
    while(father[i] != i)
    {
        i = father[i];
    }

    while(father[j] != j)
    {
        j = father[j];
    }

    father[j] = i;
}

void MinSpanTree_Kruskal(GraphMtx *g)
{
    int n = g->NumVertices;
    Edge *edge = (Edge*)malloc(sizeof(Edge) * (n*(n-1)/2));
    assert(edge != NULL);

    // 初始化edge结构
    int k = 0;
    for(int i=0; i<n; ++i)
    {
        // 查找邻接矩阵的上三角矩阵，避免重复查找
        for(int j=i; j<n; ++j)
        {
            // 顶点间的边存在时，初始化edge结构体
            if(g->Edge[i][j] != 0 && g->Edge[i][j] != MAX_COST)
            {
                edge[k].x = i;
                edge[k].y = j;
                edge[k].cost = g->Edge[i][j];
                k++;
            }
        }
    }

    int v1, v2;
    // for(int i=0; i<k; ++i)
    // {
    //     v1 = edge[i].x;
    //     v2 = edge[i].y;
    //     printf("%c-->%c : %d\n", g->VerticesList[v1], g->VerticesList[v2], edge[i].cost);
    // }

    // 将边按照权值升序排序
    qsort(edge, k, sizeof(Edge), cmp);

    // 算法核心，判断新加入的边是否可已有的边属于同一个连通子图
    int *father = (int*)malloc(sizeof(int) *n);
    assert(father != NULL);
    for(int i=0; i<n; ++i)
    {
        father[i] = i;  // 初始化i的父节点为i自己
    }

    for(int i=0; i<n; ++i)
    {
        // 当x与y的父节点不为同一个父节点时，进行连接
        if(!Is_Same(father, edge[i].x, edge[i].y))
        {
            v1 = edge[i].x;
            v2 = edge[i].y;
            printf("%c-->%c : %d\n", g->VerticesList[v1], g->VerticesList[v2], edge[i].cost);
            Mark_Same(father, edge[i].x, edge[i].y);  // 连接x和y后，将其标记为Same，合并为一个整体
        }
    }
}