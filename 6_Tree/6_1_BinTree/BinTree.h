#ifndef _BINTREE_H_
#define _BINTREE_H_

#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include<string.h>

#define ElemType char

typedef struct BinTreeNode  // 二叉树结点
{
    ElemType data;                  // 数据
    struct BinTreeNode *leftChild;  // 左孩子
    struct BinTreeNode *rightChild; // 右孩子
}BinTreeNode;

typedef struct BinTree
{
    BinTreeNode *root;      // 根节点
    ElemType     refvalue;  // stop flag
}BinTree;

void InitBinTree(BinTree *bt, ElemType ref);

//////////////////////////////////////////
// 1 创建
void CreateBinTree_1(BinTree *bt);
void CreateBinTree_1(BinTree *bt, BinTreeNode **t);  // bt的root为指针类型，为了修改它，要传入指针的地址（二级指针）
void CreateBinTree_2(BinTree *bt);
void CreateBinTree_2(BinTree *bt, BinTreeNode *&t);  // 引用是针对t实现的，对应&t；而为了修改t，需要传入它的地址，对应*&t
void CreateBinTree_3(BinTree *bt);
BinTreeNode* CreateBinTree_3_(BinTree *bt);
void CreateBinTree_4(BinTree *bt, char *str);
void CreateBinTree_4(BinTree *bt, BinTreeNode *&t, char *&str);

//////////////////////////////////////////
// 2 递归遍历
void PreOrder(BinTree *bt);
void PreOrder(BinTreeNode *t);
void InOrder(BinTree *bt);
void InOrder(BinTreeNode *t);
void PostOrder(BinTree *bt);
void PostOrder(BinTreeNode *t);
void LevelOrder(BinTree *bt);
void LevelOrder(BinTreeNode *t);

//////////////////////////////////////////
// 3 方法实现
int Size(BinTree *bt);
int Size(BinTreeNode *t);
int Height(BinTree *bt);
int Height(BinTreeNode *t);
BinTreeNode* Search(BinTree *bt, ElemType key);
BinTreeNode* Search(BinTreeNode *t, ElemType key);
BinTreeNode* Parent(BinTree *bt, BinTreeNode *p);
BinTreeNode* Parent(BinTreeNode *t, BinTreeNode *p);
BinTreeNode* LeftChild(BinTreeNode *p);
BinTreeNode* RightChild(BinTreeNode *p);
bool BinTreeIsEmpty(BinTree *bt);
void Copy(BinTree *bt1, BinTree *bt2);  // 拷贝bt2给bt1
void Copy(BinTreeNode *&t1, BinTreeNode *t2);
void BinTreeClear(BinTree *bt);
void BinTreeClear(BinTreeNode *&t);

//////////////////////////////////////////
// 4 非递归遍历
void PreOrder_1(BinTree *bt);
void PreOrder_1(BinTreeNode *t);
void InOrder_1(BinTree *bt);
void InOrder_1(BinTreeNode *t);
// void PostOrder_1(BinTree *bt);
// void PostOrder_1(BinTreeNode *t);

//////////////////////////////////////////
// 5 恢复
void CreateBinTree_5(BinTree *bt, char *VLR, char*LVR, int n);
void CreateBinTree_5(BinTreeNode *&t, char *VLR, char*LVR, int n);
void CreateBinTree_6(BinTree *bt, char *LVR, char*LRV, int n);
void CreateBinTree_6(BinTreeNode *&t, char *LVR, char*LRV, int n);

#endif // _BINTREE_H_