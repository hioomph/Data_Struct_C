#include"GraphLink.h"

// 初始化
void InitGraph(GraphLink *g)
{
    g->MaxVertices = Dafault_Vertex_Size;
    g->NumEdges = g->NumVertices = 0;

    g->NodeTable = (Vertex*)malloc(sizeof(Vertex)*g->MaxVertices);
    assert(g->NodeTable != NULL);
    for(int i=0; i<g->MaxVertices; ++i)
    {
        g->NodeTable[i].adj = NULL;
    }
}

// 打印图
void ShowGraph(GraphLink *g)
{
    Edge *p;
    for(int i=0; i<g->NumVertices; ++i)
    {
        printf("%d %c:>", i, g->NodeTable[i].data);
        p = g->NodeTable[i].adj;
        while(p != NULL)
        {
            printf("%d-->", p->dest);
            p = p->link;
        }
        printf("Nul.\n");
    }
    printf("\n");
}

// 找到顶点位置
int GetVertexPos(GraphLink *g, T v)
{
    for(int i=0; i<g->NumVertices; ++i)
    {
        if(g->NodeTable[i].data == v)
            return i;
    }
    return -1;
}

// 插入顶点
void InsertVertex(GraphLink *g, T v)
{
    if(g->NumVertices >= g->MaxVertices)
        return;
    
    // 表空间不满
    g->NodeTable[g->NumVertices++].data = v;
}

// 插入边
void InsertEdge(GraphLink *g, T v1, T v2)
{
    int p1 = GetVertexPos(g, v1);
    int p2 = GetVertexPos(g, v2);
    if(p1 == -1 || p2 == -1)
        return;
    
    // 申请边节点空间
    Edge *s;
    // v1->v2的边
    s = (Edge*)malloc(sizeof(Edge));
    assert(s != NULL);
    s->dest = p2;
    s->link = g->NodeTable[p1].adj;
    g->NodeTable[p1].adj = s;

    // v2->v1的边
    s = (Edge*)malloc(sizeof(Edge));
    assert(s != NULL);
    s->dest = p1;
    s->link = g->NodeTable[p2].adj;
    g->NodeTable[p2].adj = s;

    g->NumEdges++;
}

// 删除顶点
void RemoveVertex(GraphLink *g, T vertex)
{
    int v = GetVertexPos(g, vertex);
    // 顶点v不存在，直接返回
    if(v == -1)
        return;

    // 删除顶点：用最后一个顶点的值覆盖要删除的顶点
    // 删除边：直接调用函数RemoveEdge

    Edge *p = g->NodeTable[v].adj;  // p指向要删除结点v的边链表
    int k;
    Edge *t = NULL;  // s的前驱t，注意一定要先赋值为NULL
    Edge *s;
    while(p != NULL)
    {
        k = p->dest;  // 在释放边之前要先获取和这个顶点有关的顶点的位置信息
        s = g->NodeTable[k].adj;  // s指向和v相连的第一个顶点的边链表
        while(s != NULL && s->dest != v)
        {
            t = s;
            s = s->link;
        }
        if(s != NULL)
        {
            if(t == NULL) 
                g->NodeTable[k].adj = s->link;
            else
                t->link = s->link;
            free(s);
        }

        // 释放当前结点
        g->NodeTable[v].adj = p->link;
        free(p);
        // p指向下一个结点，执行下一次删除
        p = g->NodeTable[v].adj;
    }

    g->NumVertices--;
    // 用最后一个结点vl覆盖要删除的结点v
    g->NodeTable[v].data = g->NodeTable[g->NumVertices].data;
    g->NodeTable[v].adj = g->NodeTable[g->NumVertices].adj;
    // 由于此时vl的下标改变，因此遍历vl的边，对应修改和vl相连的顶点，其指向vl的边的下标位置
    s = g->NodeTable[v].adj;
    while(s != NULL)
    {
        k = s->dest;
        p = g->NodeTable[k].adj;
        while(p != NULL)
        {
            if(p->dest == g->NumVertices)  // 找到了指向vl的边
            {
                p->dest = v;
                break;
            }
            p = p->link;
        }
        s = s->link;
    }
}

// 删除边
void RemoveEdge(GraphLink *g, T vertex1, T vertex2)
{
    int v1 = GetVertexPos(g, vertex1);
    int v2 = GetVertexPos(g, vertex2);
    if(v1 == -1 || v2 == -1)
        return;

    Edge *q = NULL;
    Edge *p;
    
    // v1 --> v2
    p = g->NodeTable[v1].adj;
    while(p != NULL && p->dest != v2)
    {
        q = p;
        p = p->link;
    }

    // 没有查找到对应的边
    if(p == NULL)  
        return;
    
    // 查找到对应的边，开始删除
    if(q == NULL)  // 说明此时p == g->NodeTable[v1].adj，即p直接指向链表头，未进行while循环
    {
        g->NodeTable[v1].adj = p->link;
    }
    else
    {
        q->link = p->link;
    }

    // v2 --> v1
    p = g->NodeTable[v2].adj;
    while(p != NULL && p->dest != v1)
    {
        q = p;
        p = p->link;
    }

    // 反过来删除 v2 --> v1时，说明此时这个边一定存在，不需要再做判断
    // if(p == NULL)  
    //     return;
    
    // 查找到对应的边，开始删除
    if(q == NULL)  // 说明此时p == g->NodeTable[v1].adj，即p直接指向链表头，未进行while循环
    {
        g->NodeTable[v2].adj = p->link;
    }
    else
    {
        q->link = p->link;
    }

    g->NumEdges--;
}

// 摧毁图
void DestroyGraph(GraphLink *g)
{
    Edge *p;
    for(int i=0; i<g->NumVertices; ++i)
    {
        p = g->NodeTable[i].adj;
        while(p != NULL)
        {
            g->NodeTable[i].adj = p->link;
            free(p);
            p = g->NodeTable[i].adj;
        }
    }
    free(g->NodeTable);
    g->NodeTable = NULL;
    g->NumEdges = g->NumVertices = 0;
}

// 获取v的第一个邻居结点
int GetFirstNeighbor(GraphLink *g, T v)
{
    int pos = GetVertexPos(g, v);
    if(pos == -1)
        return -1;
    Edge *p = g->NodeTable[pos].adj;
    if(p != NULL)
    {
        return p->dest;
    }

    return -1;
}

// 获取v1的第一个邻居结点v2的下一个邻居结点
int GetNextNeighbor(GraphLink *g, T v1, T v2)
{
    int pos1 = GetVertexPos(g, v1);
    int pos2 = GetVertexPos(g, v2);
    if(pos1 == -1 || pos2 == -1)
        return -1;
    Edge *p = g->NodeTable[pos1].adj;
    while(p != NULL && p->dest != pos2)
    {
        p = p->link;
    }
    if(p != NULL && p->link != NULL)  // p指向和v2相连的边
    {
        return p->link->dest;
    }

    return -1;
}