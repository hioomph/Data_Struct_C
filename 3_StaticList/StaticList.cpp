#include "StaticList.h"

int Malloc_SL(StaticList &space)
{
    int i = space[1].cur;
    if(space[1].cur != 0)
        space[1].cur = space[i].cur;  // pool所指向的备用空间A不为空，说明A还指向下一个备用空间B，因此将B分配给A
    return i;
}

void Free_SL(StaticList &space, int k)
{
    // 将删除后的节点空间回收到备用空间中
    space[k].cur = space[1].cur;
    space[1].cur = k;
}

void InitSList(StaticList &space)
{
    // 在新建StaticList后，就已经申请了MAX_SIZE大小的备用空间
    // 后续操作如插入时，按照单链表的思想，需要先申请空间，然后进行插入
    // 但由于已经有了相应的备用空间，直接使用即可
    for(int i=1; i<MAX_SIZE-1; ++i)
        space[i].cur = i+1;
    space[MAX_SIZE-1].cur = 0;

    space[0].cur = -1;
}

void Insert(StaticList &space, ElemType x)
{
    int i = Malloc_SL(space);
    if(i == 0)
    {
        // 说明当前不存在新的备用空间
        printf("申请节点空间失败！");
        return;
    }

    space[i].data = x;
    if(space[0].cur == -1)  // 说明现在插入的是第一个节点
        space[i].cur = -1;
    else  // 否则直接进行头插
        space[i].cur = space[0].cur;
    space[0].cur = i;
}

void Delete(StaticList &space)
{
    int i = space[0].cur;
    space[0].cur = space[i].cur;

    // // 合并备用空间
    // space[i].cur = space[1].cur;
    // space[1].cur = i;
    Free_SL(space, i);
}

void ShowSList(StaticList &space)
{
    int i = space[0].cur;
    while(i != -1)
    {
        printf("%c-->", space[i].data);
        i = space[i].cur;  // 形如：p = p->next;
    }
    printf("Nul.\n");
}