#include"SparseMatrix.h"

// 查找矩阵中元素是否存在
int findMatrix(SparseMatrix *M, int i, int j)
{
    for(int k=0; k<M->tu; ++k)
    {
        if(M->data[k].i == i && M->data[k].j == j)
            return M->data[k].e;
    }

    return 0; // 如果没有找到匹配元素，返回零
}

// 矩阵创建
void CreateMatrix(SparseMatrix *M, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
        exit(1);
    
    fscanf(fp, "%d %d", &M->mu, &M->nu);

    int value;
    int k = 0;  // data数组的下标
    for(int i=0; i<M->mu; ++i)
    {
        for(int j=0; j<M->nu; ++j)
        {
            fscanf(fp, "%d", &value);
            if(value != 0)
            {
                M->data[k].e = value;
                M->data[k].i = i;
                M->data[k].j = j;
                k++;
            }
        }
    }

    M->tu = k;

    fclose(fp);
}

// 矩阵打印
void PrintMatrix(SparseMatrix *M)
{
    printf("row=%d, col=%d\n", M->mu, M->nu);
    for(int i=0; i<M->tu; ++i)
    {
        printf("(%d, %d, %d)\n", M->data[i].i, M->data[i].j, M->data[i].e);
    }
}

// 矩阵拷贝
void CopyMatrix(SparseMatrix *M, SparseMatrix *T)
{
    T->mu = M->mu;
    T->nu = M->nu;
    T->tu = M->tu;

    for(int k=0; k<M->tu; ++k)
    {
        T->data[k].e = M->data[k].e;
        T->data[k].i = M->data[k].i;
        T->data[k].j = M->data[k].j;
    }
}

// 矩阵加法
void AddMatrix(SparseMatrix *M, SparseMatrix *N, SparseMatrix *T)
{
    if(M->mu != N->mu || M->nu != N->nu)
    {
        printf("矩阵行列数不匹配，无法进行运算！\n");
        return;
    }

    int row = M->mu;
    int col = M->nu;

    int vt = 0;
    int vm = 0;
    int vn = 0;
    int kt = 0;

    for(int i=0; i<row; ++i)
    {
        for(int j=0; j<col; ++j)
        {
            vm = findMatrix(M, i, j);  // (i,j)在M中是否有值
            vn = findMatrix(N, i, j);  // (i,j)在N中是否有值
            vt = vm + vn;
            if(vt != 0)
            {
                T->data[kt].i = i;
                T->data[kt].j = j;
                T->data[kt].e = vt;
                kt++;
            }
        }
    }

    T->mu = row;
    T->nu = col;
    T->tu = kt;
}

// 矩阵减法
void SubMatrix(SparseMatrix *M, SparseMatrix *N, SparseMatrix *T)
{
    if(M->mu != N->mu || M->nu != N->nu)
    {
        printf("矩阵行列数不匹配，无法进行运算！\n");
        return;
    }

    int row = M->mu;
    int col = M->nu;

    int vt = 0;
    int vm = 0;
    int vn = 0;
    int kt = 0;
    
    for(int i=0; i<row; ++i)
    {
        for(int j=0; j<col; ++j)
        {
            vm = findMatrix(M, i, j);  // (i,j)在M中是否有值
            vn = findMatrix(N, i, j);  // (i,j)在N中是否有值
            vt = vm + vn;
            if(vt != 0)
            {
                T->data[kt].i = i;
                T->data[kt].j = j;
                T->data[kt].e = vt;
                kt++;
            }
        }
    }

    T->mu = row;
    T->nu = col;
    T->tu = kt;
}

// 矩阵乘法
void MulMatrix(SparseMatrix *M, SparseMatrix *N, SparseMatrix *T)
{
    if(M->nu != N->mu)
    {
        printf("矩阵行列数不匹配，无法进行运算！\n");
        return;
    }

    int row = M->mu;
    int col = N->nu;

    int vt = 0;
    int kt = 0;

    for(int i=0; i<row; ++i)
    {
        for(int j=0; j<col; ++j)
        {
            vt = 0;
            for(int l=0; l<M->nu; l++)
            {
                int vm = findMatrix(M, i, l);
                int vn = findMatrix(N, l, j);
                vt += vm * vn;
            }
            if(vt != 0)
            {
                T->data[kt].i = i;
                T->data[kt].j = j;
                T->data[kt].e = vt;
                kt++;
            }
        }
    }

    T->mu = row;
    T->nu = col;
    T->tu = kt;
}

// 矩阵转置（实现方法1）
void TransposeMatrix(SparseMatrix *M, SparseMatrix *T)
{
    T->mu = M->nu;
    T->nu = M->mu;
    T->tu = M->tu;

    int kt = 0;
    if(T->tu != 0)
    {
        // 逐列遍历，重排三元组的次序
        for(int col=0; col<M->nu; ++col)  
        {
            for(int km=0; km<M->tu; ++km)
            {
                if(M->data[km].j == col)  // 当前数据正好在第col列
                {
                    T->data[kt].i = M->data[km].j;
                    T->data[kt].j = M->data[km].i;
                    T->data[kt].e = M->data[km].e;
                    kt++;
                }
            }
        }
    }
}

// 矩阵快速转置（实现方法2）
void FastTransposeMatrix(SparseMatrix *M, SparseMatrix *T)
{
    T->mu = M->nu;
    T->nu = M->mu;
    T->tu = M->tu;

    int *num = (int *)malloc(sizeof(int) * M->nu);  // M中每一列非零元的个数
    assert(num != NULL);
    int *cpot = (int *)malloc(sizeof(int) * M->nu);  // M中每一列的第一个非零元对应三元组空间所在位置
    assert(cpot != NULL);

    if(T->tu != 0)
    { 
        // 初始化num数组
        for(int col=0; col<M->nu; ++col)
        {
            num[col] = 0;
        }
        for(int t=0; t<M->tu; ++t)
        {
            num[M->data[t].j]++;
        }

        // 初始化cpot数组
        cpot[0] = 0;
        for(int col=1; col<M->nu; ++col)
        {
            cpot[col] = cpot[col-1] + num[col-1];
        }

        // 进行转置映射
        int col = 0;
        int kt = 0;
        for(int km=0; km<M->tu; ++km)
        {
            col = M->data[km].j;
            kt = cpot[col];
            T->data[kt].i = M->data[km].j;
            T->data[kt].j = M->data[km].i;
            T->data[kt].e = M->data[km].e;
            cpot[col]++; // 重要步骤
            kt++;
        }
    }
    
    // 在C中，如果使用了动态内存分配函数如malloc、calloc或realloc来分配内存
    // 那么最终应该使用 free 函数来释放已分配的内存
    free(num);
    free(cpot);
}
