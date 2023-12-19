#ifndef _SPARSEMATRIX_H_
#define _SPARSEMATRIX_H_

#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>

#define ElemType int
#define MAXSIZE 100

typedef struct Triple
{
    int i;
    int j;
    ElemType e;
}Triple;

typedef struct SparseMatrix
{
    Triple data[MAXSIZE];   // 0
    int mu;                 // 行
    int nu;                 // 列
    int tu;                 // 非零元素
}SparseMatrix;

///////////////////////////////////////////
int findMatrix(SparseMatrix *M, int i, int j);

void CreateMatrix(SparseMatrix *M, const char *filename);
void PrintMatrix(SparseMatrix *M);
void CopyMatrix(SparseMatrix *M, SparseMatrix *T);
void AddMatrix(SparseMatrix *M, SparseMatrix *N, SparseMatrix *T);
void SubMatrix(SparseMatrix *M, SparseMatrix *N, SparseMatrix *T);
void MulMatrix(SparseMatrix *M, SparseMatrix *N, SparseMatrix *T);
void TransposeMatrix(SparseMatrix *M, SparseMatrix *T);
void FastTransposeMatrix(SparseMatrix *M, SparseMatrix *T);

#endif // _SPARSEMATRIX_H_