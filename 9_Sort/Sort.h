#ifndef _SORT_H_
#define _SORT_H_

#include<malloc.h>
#include<assert.h>
#include"SList.h"

#define T int
#define MAXSIZE 20

typedef T SqList[MAXSIZE];

///////////////////////////////////////////////////////////
// 直接插入排序 O(n^2)
void Swap(T *a, T*b)
{
    T tmp = *a;
    *a = *b;
    *b = tmp;
}
/*
void InsertSort(SqList &L, int n)
{
    for(int i=1; i<n; ++i)
    {
        if(L[i] < L[i-1])
        {
            Swap(&L[i], &L[i-1]);
            for(int j=i-1; j>0 && L[j]<L[j-1]; --j)  // important
                Swap(&L[j], &L[j-1]);
        }
    }
}
*/
// 改进
void InsertSort(SqList &L, int n)
{
    for(int i=2; i<n; ++i)
    {
        if(L[i] < L[i-1])
        {
            L[0] = L[i];
            L[i] = L[i-1];

            int j = i-2;            
            while(L[0]<L[j])
            {
                L[j+1] = L[j];
                --j;
            }            
            L[j+1] = L[0];
        }
    }
}

///////////////////////////////////////////////////////////
// 折半插入排序 O(n^2)  -- 减少直接插入排序的关键字比较次数
void BInsertSort(SqList &L, int n)
{
    for(int i=2; i<n; ++i)
    {
        L[0] = L[i];
        int low = 1;
        int high = i-1;
        while(low <= high)  // 折半插入，通过移动low/high找到该插入的位置
        {
            int mid = (low + high)/2;
            if(L[0] >= L[mid])
                low = mid+1;
            else
                high = mid-1;
        }

        for(int j=i; j>high+1; --j)  // high+1是要插入L[0]的数值的位置，因此把high+1到i的值全部往后挪动一位
        {
            L[j] = L[j-1];
        }
        L[high+1] = L[0];

    }
}

///////////////////////////////////////////////////////////
// 2路插入排序  -- 减少折半插入排序的数据移动次数
void TWayInsertSort(SqList &L, int n)
{
    SqList tmp;
    tmp[0] = L[0];
    int head, tail;
    head = tail = 0;

    for(int i=1; i<n; ++i)  // L[i]是当前要插入tmp的值
    {
        if(L[i] < tmp[head])  // 若当前遍历到的L[i]小于head所指元素，则将L[i]插入到head的前一个位置
        {
            head = (head-1+n) % n;  // 取模操作实现循环操作
            tmp[head] = L[i];
        }
        else if(L[i] > tmp[tail])  // 同理，若当前遍历到的L[i]大于head所指元素，则将L[i]插入到head的后一个位置
        {
            tail++;
            tmp[tail] = L[i];
        }
        else  // 若tmp[head]<L[i]<tmp[tail]，则需要移动数据
        {
            tail++;
            tmp[tail] = tmp[tail-1];  // 将tmp[tail]向后移动一个，并将tail本身的值加1
            int j = tail-1;
            while(L[i] < tmp[(j-1+n)%n])  // L[i]<tmp[(j-1+n)%n]，找到L[i]应该插入的地方，即tmp[j]
                                          // 由于这里的j的指向是循环的，所以(j-1+n)%n相当于j-1
            {
                tmp[j] = tmp[(j-1+n)%n];
                j = (j-1+n)%n;
            }
            tmp[j] = L[i];
        }
    }
    
    for(int i=0; i<n; ++i)
    {
        L[i] = tmp[head];
        head = (head+1)%n;
    }
}

///////////////////////////////////////////////////////////
// 表插入排序
#define MAXVALUE 0x7fffffff
typedef struct SLNode
{  
    T data;
    int link;
}SLNode;

typedef SLNode Table[MAXSIZE];

void TableInsertSort(Table t, int n)
{
    t[0].link = 1;
    int p, q;  // q是p的前驱
    for(int i=2; i<n; ++i)
    {
        p = t[0].link;  // p指向当前检索的值的下标，每一次都要从t[0].link指向的头开始排序
        q = 0;
        while(p!=0 && t[p].data<=t[i].data)  // p!=0说明未检索完；t[p].data<=t[i].data说明当前检索到的值小于等于要排序进来的值，所以要接着往下找更大的值
        {
            q = p;
            p = t[p].link;  // p指向下一个更大的值对应的下标
        }
        // 当退出循环时，t[p].data>t[i].data，则i在p的前驱位置插入
        t[i].link = t[q].link;
        t[q].link = i;
    }
}

///////////////////////////////////////////////////////////
// 希尔排序
void ShellInsert(SqList &L, int n, int dk)
{
    for(int i=dk+1; i<n; ++i)
    {
        if(L[i] < L[i-dk])  // 间隔两端的两个数
        {
            L[0] = L[i];
            int j = i - dk;
            while(j>0 && L[0] < L[j])
            {
                L[j+dk] = L[j];  // 在间隔上取的几个数之间进行直接插入排序，需要注意这里数之间的间隔是dk
                j -= dk;
            }
            L[j+dk] = L[0];
        }
    }
}
void ShellSort(SqList &L, int n, int dlta[], int t)
{
    for(int k=0; k<t; ++k)
    {
        ShellInsert(L, n, dlta[k]);
    }
}

///////////////////////////////////////////////////////////
// 冒泡排序
void BubbleSort(SqList &L, int n)
{
    for(int i=0; i<n-1; ++i)
    {
        for(int j=0; j<n-1-i; ++j)
        {
            if(L[j] > L[j+1])
            {
                Swap(&L[j], &L[j+1]);
            }
        }
    }
}

///////////////////////////////////////////////////////////
// 快速排序
int Partition(SqList &L, int low, int high)
{
    T pk = L[low];  // 先指定L[low]为关键字
    while(low < high)
    {
        while(low<high && L[high]>=pk)  // 循环使得high指向小于枢轴的值
            high--;
        L[low] = L[high];  // 将这个较小的L[high]值赋值给low所处的位置
        while(low<high && L[low]<pk)  // 循环使得low指向大于枢轴的值
            low++;
        L[high] = L[low];  // 将这个较大的L[low]值赋值给high所处的位置
    }
    L[low] = pk;

    return low;
}
void QuickSort(SqList &L, int low, int high)
{
    if(low < high)  // 未排序完成
    {
        int pkloc = Partition(L, low, high);  // 求枢轴关键字的位置
        QuickSort(L, low, pkloc-1);
        QuickSort(L, pkloc+1, high);
    }
}

///////////////////////////////////////////////////////////
// 简单选择排序
int SelectMinKey(SqList &L, int i, int n)
{
    T minval = L[i];  // 首先将当前的首位置作为minval与后续进行比较，从而找到真正的minval
    int pos = i;  // 记录minval对应的key

    for(int m=i+1; m<n; ++m)
    {
        if(L[m] < minval)
        {
            minval = L[m];
            pos = m;
        }
    }

    return pos;
}
void SelectSort(SqList &L, int n)
{
    for(int i=0; i<n-1; ++i)
    {
        int j = SelectMinKey(L, i, n);  // 找到最小值对应的下标位置
        if(j != i)
        {
            Swap(&L[j], &L[i]);
        }
    }
}

///////////////////////////////////////////////////////////
// 树形选择排序，相较于简单选择排序减少了比较次数（锦标赛排序）
#define MAXVALUE 0x7fffffff

T GetValue(T e[], int n, int p)
{
    if(p >= n)
        return MAXVALUE;
    
    T value;
    if(p < n/2)  // 得到的是下标位置
        value = e[e[p]];
    else  // 否则为叶子节点，直接返回e[p]
        value = e[p];

    return value;
}
void Play(T e[], int n, int p)
{
    int left, right;  // 左右下标
    T lval, rval;  // 左右值
    while(p >= 0)
    {
        left = 2*p+1;
        right = 2*p+2;
        lval = GetValue(e, n, left);
        rval = GetValue(e, n, right);
        if(lval <= rval)
        {
            if(left < n/2)
                e[p] = e[left];  // important
            else
                e[p] = left;
        }
        else
        {
            if(right < n/2)
                e[p] = e[right];  // important
            else
                e[p] = right;
        }
        
        --p;
    }
}
void Select(T e[], int n, int p)
{
    int i = p;  // 父节点
    int j = 2*p+1;  // 左子树
    T lval, rval;

    int flag = 1;
    while(i >= 0 && flag)
    {
        lval = GetValue(e, n, j);
        rval = GetValue(e, n, j+1);
        if(lval <= rval)
        {
            if(j < n/2)
                e[i] = e[j];  // j<n/2说明j的位置在非叶子节点的位置，所以对于j的父节点，需要的是位置j上存储的内容即e[j]
            else
                e[i] = j;  // j>=n/2说明j的位置在叶子节点的位置，所以对于j的父节点，需要的是就是位置j本身
        }
        else
        {
            if((j+1) < n/2)
                e[i] = e[j+1];  // 同上
            else
                e[i] = j+1;
        }

        if(i == 0)
            flag--;
        // 向上递归，找到新的父节点和对应的左孩子
        i = (i-1)/2;
        j = 2*i+1;
    }
}
void TreeSelectSort(SqList &L, int n)
{
    int size = 2*n-1;
    T *e = (T*)malloc(sizeof(T) * size);
    assert(e != NULL);

    int k = size / 2;
    for(int i=0; i<n; ++i)
    {
        e[k++] = L[i];
    }

    int curpos = size/2-1;  // 树最后一个叶子分支的父节点，相当于要打的第一场比赛
    Play(e, size, curpos);
    int i = 0;
    L[i] = e[e[0]];

    // 将已经选出来的最小值的节点A，将其赋值为最大值，使其不参与后续的比较
    e[e[0]] = MAXVALUE;  
    // 从A的父节点开始一路向上比较，直到到达根节点，比较完毕
    for(int i=1; i<n; ++i)
    {
        curpos = (e[0]-1)/2;  // A的父节点
        Select(e, size, curpos);
        L[i] = e[e[0]];
        e[e[0]] = MAXVALUE;
    }

    free(e);
    e = NULL;
}

///////////////////////////////////////////////////////////
// 堆排序，相较于树形选择排序辅助空间大幅减少，只需要1个辅助空间
void siftDown(T heap[], int n, int p)
{
    int i = p;  // 父节点
    int j = 2*i+1;  // 左孩子
    while(j < n)  // 说明p有左孩子
    {
        if(j<n-1 && heap[j]>heap[j+1])  // j<n-1说明有右孩子，heap[j]>heap[j+1]说明左孩子大于右孩子
            j++;  // j指向右孩子，也即是保证j指向左右孩子中较小的那个值

        if(heap[i] <= heap[j])
        {
            break;
        }
        else
        {
            Swap(&heap[i], &heap[j]);
            // 继续递归，使得该函数从位置p一直遍历到叶子结点
            i = j;
            j = 2*i+1;
        }
    }
}
T RemoveMinKey(T heap[], int n)
{
    T key = heap[0];
    heap[0] = heap[n];
    siftDown(heap, n, 0);

    return key;
}
void HeapSort(SqList &L, int n)
{
    T *heap = (T*)malloc(sizeof(T) * n);
    assert(heap != NULL);

    for(int i=0; i<n; ++i)
    {
        heap[i] = L[i];  // 将原始数据拷贝到heap空间中
    }

    // 将heap调整为小堆
    // 1、找到最后一个分支节点，调用函数SiftDown后，目前的堆顶元素即为当前序列的最小值
    int curpos = n/2-1;
    while(curpos >= 0)
    {
        siftDown(heap, n, curpos);
        curpos--;
    }

    // 2、取走堆顶元素后，依次用最后一个节点补上根节点（最小值），重新进行小堆排序并取堆顶元素
    for(int i=0; i<n; ++i)
    {
        L[i] = RemoveMinKey(heap, n-i-1);
    }

}

///////////////////////////////////////////////////////////
// 归并排序
void Merge(SqList &L, SqList &TP, int left, int mid, int right)
{
    for(int i=left; i<=right; ++i)
    {
        TP[i] = L[i];
    }

    int s1 = left;
    int s2 = mid+1;
    int k = left;
    while(s1<=mid && s2<=right)
    {
        if(TP[s1] <= TP[s2])
            L[k++] = TP[s1++];
        else
            L[k++] = TP[s2++];
    }
    while(s1 <= mid)
        L[k++] = TP[s1++];

    while(s2<=right)
        L[k++] = TP[s2++];
}
void MergeSort(SqList &L, SqList &TP, int left, int right)
{
    if(left >= right)
        return;
    
    int mid = (left + right) / 2;
    MergeSort(L, TP, left, mid);
    MergeSort(L, TP, mid+1, right);
    Merge(L, TP, left, mid, right);
}

///////////////////////////////////////////////////////////
// 基数排序
int getkey(T value, int k)
{
    int key;
    while(k >= 0)
    {
        key = value % 10;
        value /= 10;
        k--;
    }

    return key;
}
void Distribute(SqList &L, int n, List (&lt)[10], int k)
{
    for(int i=0; i<10; ++i)
    {
        clear(&lt[i]);
    }
    int key;
    for(int i=0; i<n; ++i)
    {
        key = getkey(L[i], k);  // 取得需要比对的位置上的值
        push_back(&lt[key], L[i]);
    }
}
void Collect(SqList &L, List (&lt)[10])
{
    int k=0;
    for(int i=0; i<10; ++i)
    {
        Node *p = lt[i].first->next;
        while(p != NULL)
        {
            L[k++] = p->data;
            p = p->next;
        }
    }
}
void RadixSort(SqList &L, int n)
{
    List list[10];
    for(int i=0; i<10; ++i)
    {
        InitList(&list[i]);
    }

    for(int i=0; i<3; ++i)
    {
        
        Distribute(L, n, list, i);
        Collect(L, list);
    }
}


#endif // _SORT_H_