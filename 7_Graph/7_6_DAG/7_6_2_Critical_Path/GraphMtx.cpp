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
void InSertEdge(GraphMtx *g, T v1, T v2, E cost)
{
    int p1 = GetVertexPos(g, v1);
    int p2 = GetVertexPos(g, v2);
    if(p1 == -1 || p2 == -1)
        return;
    
    if(g->Edge[p1][p2] != 0)  // 注意这一步
        return;
    
    // g->Edge[p1][p2] = g->Edge[p2][p1] = 1;
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
        if(g->Edge[p][i] != 0)
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
        if(g->Edge[pv][i] != 0)
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

// 获取权值
E GetWeight(GraphMtx *g, int v1, int v2)
{
    if(v1 == -1 || v2 == -1)
        return 0;
    
    return g->Edge[v1][v2];
}


// 求解关键路径
void CriticalPath(GraphMtx *g)
{
    int n = g->NumVertices;
    int *ve = (int*)malloc(sizeof(int) * n);
    int *vl = (int*)malloc(sizeof(int) * n);
    assert(ve != NULL && vl != NULL);

    for(int i=0; i<n; ++i)
    {
        ve[i] = 0;
        vl[i] = MAX_COST;  // 此处不能初始化为0，否则求解vl时会出现负数
    }

    // 正向求解每个顶点的最早开始时间，ve
    // 实际上这个步骤相当于在初始化最早开始时间
    /*
        对最早开始时间的理解：
            假设此时有一条边从v指向w，
            v的最早开始时间为t1，w的最早开始时间为t2，边v->w的权值为cost，
            若t1+cost>t2，则更新t2
    */
    int j, w;
    for(int i=0; i<n; ++i)
    {
        j = GetFirstNeighbor(g, g->VerticesList[i]);  // 指向i的第一个邻接顶点
        while(j != -1)
        {
            w = GetWeight(g, i, j);  // 获取边i->j的权值
            if((ve[i] + w) > ve[j])
            {
                ve[j] = ve[i] + w;
            }
            j = GetNextNeighbor(g, g->VerticesList[i], g->VerticesList[j]);  // 获取下一个邻接顶点
        }
    }

    // for(int i=0; i<n; ++i)
    //     printf("%d\t", ve[i]);
    // printf("\n");

    // 反向求解每个顶点的最晚开始时间，vl
    // 实际上这个步骤相当于在初始化最晚开始时间
    // 最晚开始时间：如果从顶点i到顶点j存在多条路径，则最长时间的那条路径A为关键路径，而小于最长时间的其他路径可以在A开始后一段时间再进行
    vl[n-1] = ve[n-1];
    for(int i=n-2; i>0; --i)  // 从倒数第二个顶点开始往前遍历
    {
        j = GetFirstNeighbor(g, g->VerticesList[i]);  // 指向i的第一个邻接顶点
        while(j != -1)
        {
            w = GetWeight(g, i, j);
            // 若步骤j的最晚开始时间（vl[j]）减去活动(i, j)的时间（w）小于步骤i的最晚开始时间（vl[i]），更新vl[i]
            // 因为说明此时活动(i, j)的持续时间要长于原先走的那条路径，所以要进行更新
            // 也就是说，应该选择更小的时间
            if((vl[j] - w) < vl[i])  
            {
                vl[i] = vl[j] - w;
            }
            j = GetNextNeighbor(g, g->VerticesList[i], g->VerticesList[j]);  // 获取下一个邻接顶点
        }
    }

    // for(int i=0; i<n; ++i)
    //     printf("%d\t", vl[i]);
    // printf("\n");

    int Ae, Al;  // 活动的最早开始时间和最晚开始时间，这里的A代表边
    for(int i=0; i<n; ++i)
    {
        j = GetFirstNeighbor(g, g->VerticesList[i]);  // 指向i的第一个邻接顶点
        while(j != -1)
        {
            Ae = ve[i];  // 活动的最早开始时间
            Al = vl[j] - GetWeight(g, i, j);  // 有点没太理解这一行
            // vl[j]是顶点j代表该步骤的最晚开始时间，边ij的权重是从完成步骤i所需的时间
            // vl[j] - GetWeight(g, i, j)即代表活动j的最晚开始时间
            if(Ae == Al)
            {
                // 说明i和j是关键路径上的两个顶点
                printf("<%c, %c>是关键路径.\n", g->VerticesList[i], g->VerticesList[j]);
            }
            j = GetNextNeighbor(g, g->VerticesList[i], g->VerticesList[j]);
        }
    }

    free(ve);
    free(vl);
}
